#include    "Server.h"
#include    "CRequest.h"
#include    <fmt/core.h>


Server::Server()
    :MAX_CONNECTIONS(10), BUFFER_SIZE(1024), PORT(8080){
    
    int addrlen = sizeof(this -> address);
    this -> server_fd = socket(AF_INET, SOCK_STREAM, 0);
    this -> address.sin_family = AF_INET;
    this -> address.sin_addr.s_addr = INADDR_ANY;
    this -> address.sin_port = htons(this -> PORT);        
    
    bind(server_fd, (struct sockaddr *)&(this -> address), sizeof(this -> address));
    
    // iteration server
    while (true) {
        listen(server_fd, this -> MAX_CONNECTIONS);
        ssize_t new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        
        fmt::println("Sokcet from queue");
        
        
        service_handler(new_socket);
    }
}


void Server::service_handler(ssize_t& fd){
    char buffer[this -> BUFFER_SIZE] = {0};

    std::string res_msg = CRequest::HTTP_Response(200, {CRequest::Header_Generator::set_content_len(0)}).to_string();


    ssize_t len = 0;
    std::string msg;                        // really huge BUGGGGGGG!!!!!
    read(fd, buffer, this -> BUFFER_SIZE);  // why the hell this shit isnt working? -----+
    //                                                                                   |
    // while ((len = read(fd, buffer, this -> BUFFER_SIZE)) > 0){   <--------------------+
    //     msg.append(buffer);
    // }
    std::cout << buffer;


    send(fd, res_msg.c_str(), res_msg.length(), 0);

    close(fd);
    return;
}