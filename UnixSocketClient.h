//
// Created by zhouxi on 2020/06/18.
//

#ifndef TEST_UNIXSOCKETCLIENT_H
#define TEST_UNIXSOCKETCLIENT_H

#define SOCKET_PATH "/tmp/sock_file_dji_osdk_camera.sock"

#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <cstdio>
#include <cstdlib>


class UnixSocketClient {
    public:
        UnixSocketClient();
        ~UnixSocketClient();
        int createService();
        int connect();
        int read(void *, int);
//        int write();

    private:
        int client_fd;
        struct sockaddr_un server_sock_addr_un;
};


#endif //TEST_UNIXSOCKETCLIENT_H
