//
// Created by zhouxi on 2020/06/18.
//

#include "UnixSocketClient.h"
#include <iostream>

UnixSocketClient::UnixSocketClient() {
    client_fd = -1;
}


UnixSocketClient::~UnixSocketClient() {
    if(client_fd > 0) {
        unlink(server_sock_addr_un.sun_path);
        close(client_fd);
//        unlink(SOCKET_PATH);
    }
}

int UnixSocketClient::createService() {
    client_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (client_fd < 0) {
        perror("Cannot create socket");
        exit(-1);
    }
    //
    server_sock_addr_un.sun_family = AF_UNIX;
    strcpy(server_sock_addr_un.sun_path, SOCKET_PATH);
    return client_fd;
}

int UnixSocketClient::connect() {
    int result = -1;
    size_t server_sock_addr_un_size = sizeof(server_sock_addr_un);
    result = ::connect(client_fd, (struct sockaddr *)&server_sock_addr_un,server_sock_addr_un_size);
    std::cout << "call connect result: " << result << std::endl;
    return result;
}

int UnixSocketClient::read(void * buff, int count) {
    int read_len = 0;
    if(client_fd >= 0) {
        read_len = ::read(client_fd, buff, count);
    }
    return read_len;
}
