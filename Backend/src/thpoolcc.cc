// +------------- DEMO -------------+
// | Author:    azusaings@gmail.com |
// | License:	  GPLv3.0             |
// +--------------------------------+ 
#include "thpoolcc.h"
// synchronized
#include <unistd.h>
#include <memory.h>

// test
#include <string>

#define DEBUG 1

#ifdef DEBUG
  #define THREAD_PRINT_DEBUG(msg) \
    printf("[tid-0x%lx]: %s\n", pthread_self(), msg)
#else
  #define THREAD_PRINT(msg)
#endif

namespace ThreadPoolCC {

// +------------------------------- Work Queue Implementation-------------------------------+

WorkQueue::WorkQueue(): n_works(0), n_msg(0) {
  this->front = new Work[1];
  this->rear = this->front;
}

Work* WorkQueue::pop_front() {
  if(!this->n_works && !this->n_msg) {
    return nullptr;
  }
  this->n_works--;
  Work* ret = this->front;
  this->front = this->front->next;
  return ret;
}

void WorkQueue::push_work_rear(void* (*func_p)(void*), void* arg) {
  this->rear->func_p = func_p;
  this->rear->arg = arg;
  this->rear->urge = false;
  this->rear->next = new Work [1];
  this->rear = this->rear->next;
  this->n_works++;
  return;
}

void WorkQueue::push_msg_front(void* (*func_p)(void*), void* arg) {
  Work* tmp = new Work[1];
  tmp->arg = arg;
  tmp->func_p = func_p;
  tmp->urge = true;
  tmp->next = this->front;
  this->front = tmp;
  this->n_msg++;
  return;
}

void WorkQueue::destroy() {
  while (this->n_works) {
    Work *cur = this->front;
    this->front = cur->next;
    delete cur;
    this->n_works--;
  }
  return;
}

// +------------------------------- Thread Pool Implementation -------------------------------+

// routine for created pthreads
static void* worker_routine(void* arg) {
  THREAD_PRINT_DEBUG("new thread is created");
  WorkerInfo* info = static_cast<WorkerInfo*>(arg);
  ThreadPool* thp  = info->thpool;
  while(thp->thpool_alive) { 
    // check whether the queue is not empty
    pthread_mutex_lock(&thp->access_work_queue);
    while ((!thp->work_queue.n_works) && thp->thpool_alive && (!thp->work_queue.n_msg)) {
      // automatically get mutex lock when the condition is ready  
      pthread_cond_wait(&thp->has_works, &thp->access_work_queue);
    }
    if(!thp->thpool_alive) {
      pthread_mutex_unlock(&thp->access_work_queue);
      break;
    } 

    pthread_mutex_lock(&thp->access_thd_num);
    thp->n_thd_working++;
    pthread_mutex_unlock(&thp->access_thd_num);

    // get work from queue
    Work* cur_work = thp->work_queue.pop_front();
    pthread_mutex_unlock(&thp->access_work_queue);
    
    // execute task
    if(cur_work->urge) {
      THREAD_PRINT_DEBUG("urged to exit");
      delete cur_work;
      pthread_mutex_lock(&thp->access_thd_num);
      thp->n_thd_working--;
      thp->worker_threads[info->index] = -1;
      pthread_mutex_unlock(&thp->access_thd_num);
      break;  
    } else {
      cur_work->func_p(cur_work->arg);
      delete cur_work;
    }

    pthread_mutex_lock(&thp->access_thd_num);
    thp->n_thd_working--;
    if(!thp->n_thd_working){
        pthread_cond_signal(&thp->all_idle);
      } 
    if(thp->work_queue.n_works || thp->work_queue.n_msg) {
      pthread_cond_signal(&thp->has_works); 
    }
    pthread_mutex_unlock(&thp->access_thd_num);
  } // exit: while(!thp->n_works)

  THREAD_PRINT_DEBUG("exits");
  pthread_mutex_lock(&thp->access_thd_num);
  thp->n_thd_exist--;
  pthread_mutex_unlock(&thp->access_thd_num);
  delete[] info;
  return nullptr;
}

static void* manager_routine(void* arg) {
  ManagerInfo* info = static_cast<ManagerInfo*>(arg);
  ThreadPool*  thp  = info->thpool;
  thp->n_thd_inc = info->n_init_threads;
  // main thread should wait till at least one thread is initialized
  while (thp->thpool_alive) {
    pthread_mutex_lock(&thp->access_thd_num);
    if(thp->n_thd_inc > 0){
      int real_inc = 0;
      for (size_t i = 0; i < thp->N_MAX_THREADS; i++) {
        // find available index for new thread
        if(real_inc == thp->n_thd_inc) {
          thp->n_thd_inc = 0;
          break;
        }
        if(thp->worker_threads[i] > 0) {
          continue;
        }
        // creating new thread
        WorkerInfo* wi = new WorkerInfo[1];
        wi->thpool=thp;
        wi->index=i;
        pthread_create(thp->worker_threads + i, nullptr, worker_routine, (void*)wi);
        real_inc++;
        pthread_detach(thp->worker_threads[i]); 
        thp->n_thd_exist++;
        THREAD_PRINT_DEBUG("adding thread...");

        // signal main thread if it's an initialization
        if(!thp->thpool_init && !i) {
          pthread_cond_signal(&thp->is_init);
          thp->thpool_init = true;
        } 

      }
    }
    pthread_mutex_unlock(&thp->access_thd_num);

    // periodic sleep
    sleep(info->secs_tick);
    
    // calculate next increasement
    pthread_mutex_lock(&thp->access_thd_num);
    // decreasing 
    if(thp->n_thd_working * 2 < thp->n_thd_exist) {
      if(thp->n_thd_exist - thp->N_STEPS > 0) {
        thp->n_thd_inc = -thp->N_STEPS;
      } else {
        thp->n_thd_inc = -thp->n_thd_exist + 1;          // there must be at least one thread
      }
    // increasing 
    } else if(thp->n_thd_exist < thp->work_queue.n_works) {
      if(thp->n_thd_inc + thp->n_thd_exist <= thp->N_MAX_THREADS) {
        thp->n_thd_inc = thp->N_STEPS;
      } else {
        thp->n_thd_inc = thp->N_MAX_THREADS - thp->n_thd_exist;
      }
    }
    pthread_mutex_unlock(&thp->access_thd_num);
    
    std::string s = std::string("update increment to ") + std::to_string(thp->n_thd_inc);
    THREAD_PRINT_DEBUG(s.c_str());

    pthread_mutex_lock(&thp->access_work_queue);
    if(thp->n_thd_inc < 0) {
      for (size_t i = 0; i < -thp->n_thd_inc; i++) {
        thp->work_queue.push_msg_front(nullptr, nullptr);
      } 
      thp->n_thd_inc = 0;
    }
    
    pthread_mutex_unlock(&thp->access_work_queue);
    pthread_cond_broadcast(&thp->has_works);
  } // exit: while()
  delete[] info;
  return nullptr;
}

// initialization
ThreadPool::ThreadPool(uint32_t n_init_threads, uint32_t N_MAX_THREADS=20, uint32_t N_STEPS=1, time_t secs_tick=1):
  n_thd_exist(0),
  n_thd_working(0), 
  n_thd_inc(n_init_threads), 
  access_thd_num(PTHREAD_MUTEX_INITIALIZER),
  access_work_queue(PTHREAD_MUTEX_INITIALIZER), 
  has_works(PTHREAD_COND_INITIALIZER), 
  all_idle(PTHREAD_COND_INITIALIZER),
  is_init(PTHREAD_COND_INITIALIZER),
  thpool_init(false),
  N_MAX_THREADS(N_MAX_THREADS),
  N_STEPS(N_STEPS), 
  thpool_alive(true) {
  
  // init threadpool
  this->manager_thread = new pthread_t[1];
  this->worker_threads = new pthread_t[N_MAX_THREADS];
  memset(worker_threads, 0, sizeof(pthread_t) * N_MAX_THREADS);

  ManagerInfo* mi = new ManagerInfo[1]; 

  mi->thpool=this;
  mi->n_init_threads=n_init_threads;
  mi->secs_tick=secs_tick;

  pthread_create(this->manager_thread, nullptr, manager_routine, (void*)mi);
  pthread_detach(*this->manager_thread);

  // wait till there is at least one thread 
  pthread_mutex_lock(&this->access_thd_num);
  while (!this->thpool_init) {
    pthread_cond_wait(&this->is_init, &this->access_thd_num);
  }
  pthread_mutex_unlock(&this->access_thd_num);
  THREAD_PRINT_DEBUG("thread pool initializes");
}

// add works to work queue, return false if failed
bool ThreadPool::addWork(void* (*func_p)(void*), void* arg) {
  if(!this->thpool_alive) {
    return false;
  }
  pthread_mutex_lock(&this->access_work_queue);
  this->work_queue.push_work_rear(func_p, arg);
  pthread_cond_signal(&has_works);
  pthread_mutex_unlock(&this->access_work_queue);
  return true;
}

// destroy thread pools
void ThreadPool::destroy() {
  this->thpool_alive = false;

  uint32_t n_threads_to_cleanup = this->n_thd_exist;
  time_t now = time(nullptr);
  // wake up all the idle threads ASAP
  while(this->n_thd_exist) {
    if(difftime(time(nullptr), now) >= 1) {
      break;
    }
    pthread_cond_broadcast(&this->has_works);
  }

  // then broadcast signal once a second
  while(this->n_thd_exist) {
    pthread_cond_broadcast(&this->has_works);
    sleep(1);
  }
  THREAD_PRINT_DEBUG("all threads exit... after ThreadPool::destroy()");

  // resource recycling
  delete   this->manager_thread;
  delete[] this->worker_threads;
  
  return;
}

// wait till all threads are idle and the work queue is empty
void ThreadPool::wait(uint8_t n_max_poll_secs=1) {
  uint8_t n_poll_secs = 1;
  pthread_mutex_lock(&this->access_thd_num);
  while (this->n_thd_working || this->work_queue.n_works) {
    pthread_cond_wait(&this->all_idle, &this->access_thd_num);
    sleep(n_poll_secs);
    // sleep for [1, 2, 4, ... , n_max_poll_secs] each time
    if(n_poll_secs * 2 < n_max_poll_secs) {
      n_poll_secs *= 2; 
    } else{
      n_poll_secs = n_max_poll_secs;
    }
  }
  pthread_mutex_unlock(&this->access_thd_num);
  THREAD_PRINT_DEBUG("wake up from ThreadPool::wait()");
  return;
}

} // namespace ThreadPoolCC 


// +------------------------- test --------------------------+

void* test_routine(void* arg) {
  int range = *static_cast<int*>(arg);
  int sum = 0;
  for(int i = 0; i < range; ++i) {
    sum += i;
  }
  THREAD_PRINT_DEBUG(std::to_string(sum).c_str());
  return nullptr;
}

int main(int, char**) {
  ThreadPoolCC::ThreadPool thpool(2, 2, 1, 1);
  sleep(1);
  int range = 1000;
  thpool.addWork(test_routine, &range);
  thpool.addWork(test_routine, &range);
  thpool.addWork(test_routine, &range);
  thpool.addWork(test_routine, &range);
  thpool.addWork(test_routine, &range);
  // for (int i = 0; i < 100; i++) {
  //   thpool.addWork(test_routine, &range);
  // }

  thpool.wait();
  // thpool.destroy();
  
  // while (1)
  // {
  //   /* code */
  // }
  
  
  return 0;
}

// @todo : destroy should has a option whether to wait forever...