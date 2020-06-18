//
// Created by zhouxi on 2020/06/17.
//

#include "SocketFile.h"
#include <iostream>
#include <unistd.h>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>

#include "SocketFileServer.h"

using namespace std;

void init_socket_file_local() {
    SocketFileServer server = SocketFileServer();
    server.createService();



}