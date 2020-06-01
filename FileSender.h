#ifndef CPPFILESENDER_FILESENDER_H
#define CPPFILESENDER_FILESENDER_H

#define START_FLAG "<start>"
#define STOP_FLAG "<stop>"
#define MAX_PAYLOAD_LENGTH 500

// START_FLAG verify code , now package number : all package number ,payload length , payload STOP_FLAG
// <start>ABCD,1:2,500,payload<stop>

#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <string>


enum FileSenderEnum {
    FileSenderEnum_SUCCESSFUL,
    FileSenderEnum_FAILED
};

typedef struct FileSenderConfig {
    struct sockaddr_in my_address;
    struct sockaddr_in client_address;
    int sock_fd;
} FileSenderConfig;

void init_sock_fd(FileSenderConfig * config);

void release_sock_fd(FileSenderConfig * config);

FileSenderEnum sendFileByUDP(FileSenderConfig fileSenderConfig, void * data, unsigned int length);

FileSenderEnum sendFileByUDP2(FileSenderConfig fileSenderConfig, void * data, unsigned int length);

FileSenderEnum sendMessage(FileSenderConfig fileSenderConfig, const std::string str);

#endif //CPPFILESENDER_FILESENDER_H
