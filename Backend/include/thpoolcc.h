// +------------- DEMO -------------+
// | Author:    azusaings@gmail.com |
// | License:	  GPLv3.0             |
// +--------------------------------+ 
#ifndef __THREAD_POOL_CC_H
#define __THREAD_POOL_CC_H

#include <stdint.h>
#include <pthread.h>
#include <mutex>

namespace ThreadPoolCC {

// +------------------------------- Work Queue -------------------------------+
struct Work {
  Work* next;
  void* (*func_p)(void*);
  void* arg;
  bool  urge;
};


class WorkQueue {
public:
  volatile size_t n_works;
  volatile size_t n_msg;
  Work*           front;
  Work*           rear;

  WorkQueue();

  void push_work_rear(void* (*func_p)(void*), void* arg);

  void push_msg_front(void* (*func_p)(void*), void* arg);

  Work* pop_front();

  void destroy();
};


// +------------------------------- Thread Pool -------------------------------+
class ThreadPool;

struct WorkerInfo {
  ThreadPool* thpool;
  size_t      index;
};

struct ManagerInfo {
  ThreadPool* thpool;
  uint32_t    n_init_threads;
  time_t      secs_tick;    // seconds between each resource-check
};


static void* worker_routine(void* routine_arg);

static void* manager_routine(void* arg);

class ThreadPool {
public:
  // thpool status
  const    uint8_t  N_STEPS;        // the min unit for resizing the thpool
  const    uint32_t N_MAX_THREADS;
  volatile uint32_t n_thd_exist;
  volatile uint32_t n_thd_working;
  int8_t            n_thd_inc;      // increment of threads; could be negetive
  bool              thpool_alive;
  bool              thpool_init;

  // internal data structure
  WorkQueue         work_queue;

  // sychronization among workers
  pthread_mutex_t   access_work_queue;
  pthread_mutex_t   access_thd_num;   // mutex for thpool status
  pthread_cond_t    is_init;
  pthread_cond_t    has_works; 
  pthread_cond_t    all_idle;        // requirement for ThreadPool::wait() to return   

  // sychronization between workers and manager
  pthread_t*        worker_threads;
  pthread_t*        manager_thread;  // core thread for dynamic resizing the threadpool
  
  ThreadPool(uint32_t n_init_threads, uint32_t N_MAX_THREADS, uint32_t N_STEPS, time_t secs_tick);

  bool addWork(void* (*func_p)(void*), void* arg);

  void destroy();

  void wait(uint8_t n_max_poll_secs);

};

}; // namespace ThreadPoolCC

#endif