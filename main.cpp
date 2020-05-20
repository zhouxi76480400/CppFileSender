#include <iostream>
#include <string.h>


#include "FileSender.h"

const char * client_address = "127.0.0.1";

const int16_t client_port = 20001;


int main() {
    FileSenderConfig config;
    //
    bzero(&config.my_address, sizeof(config.my_address));
    config.my_address.sin_family = AF_INET;
    config.my_address.sin_addr.s_addr = htonl(INADDR_ANY);
    config.my_address.sin_port = htons(0);
    //
    bzero(&config.client_address, sizeof(config.client_address));
    config.client_address.sin_family = AF_INET;
    config.client_address.sin_addr.s_addr = inet_addr(client_address);
    config.client_address.sin_port = htons(client_port);
    //
    init_sock_fd(&config);
    //
    int l = 1024;
    for (int i = 0 ; i < 10 ; i ++ ) {
        auto data = malloc(l);
        memset(data, 'a' ,l);
        ((char *)data)[0] = 'e';
        ((char *)data)[500] = 'b';
        ((char *)data)[1000] = 'c';
        sendFileByUDP(config, data, l);
        free(data);
    }

    release_sock_fd(&config);
    return 0;
}
