#include "FileSender.h"

#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <sys/time.h>

#define VERIFY_CODE_POOL "1234567890abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"

void init_sock_fd(FileSenderConfig * config) {
    int fd = config->sock_fd;
    release_sock_fd(config);
    fd = socket(AF_INET, SOCK_DGRAM, 0);
    if(fd < 0) {
        perror("cannot get socket fd, program exit\n");
        exit(1);
    }
    config->sock_fd = fd;
}

void release_sock_fd(FileSenderConfig *config) {
    int fd = config->sock_fd;
    if(fd <= OPEN_MAX && fd >= 0) {
        close(fd);
    }
}

unsigned int needToSendTimes(unsigned int all, unsigned int one) {
    unsigned int times = all / one;
    unsigned int remainder = all % one;
    if(remainder > 0) {
        times ++;
    }
    return times;
}

void getVerifyCode(char * empty_char_buffer, int buffer_length) {
    memset(empty_char_buffer, 0, buffer_length);
    int pool_length = strlen(VERIFY_CODE_POOL);
    struct timeval tv;
    struct timezone tz;
    gettimeofday(&tv,&tz);
    srand((unsigned)tv.tv_usec);
    for(int i = 0 ; i < buffer_length ; i ++) {
        int pos = rand() % pool_length;
        char c = VERIFY_CODE_POOL[pos];
        memset(empty_char_buffer+i, c, 1);
    }
}

FileSenderEnum sendFileByUDP(FileSenderConfig fileSenderConfig, void * data, unsigned int length) {
    if(data != nullptr && length > 0 && fileSenderConfig.sock_fd >= 0) {
        auto waiting_send_data = malloc(length);
        memcpy(waiting_send_data,data,length);
        //
        unsigned int all_waiting_send_data_length = length;
        unsigned int need_to_send_times = needToSendTimes(all_waiting_send_data_length, MAX_PAYLOAD_LENGTH);
        //
        unsigned int stop_flag_length = strlen(STOP_FLAG);  // length of stop_flag
        //
        int verify_code_size = 4;
        char * verify_code = (char *) malloc(verify_code_size); // verify code
        getVerifyCode(verify_code,verify_code_size);
        //
        std::string all_part_str = std::to_string(need_to_send_times);
        //
        for (int i = 0 ; i < need_to_send_times ; i ++) {
            std::string now_part_str = std::to_string(i+1);
            //
            std::string part1 = START_FLAG;
            part1.append(std::string(verify_code));
            part1.append(",");
            part1.append(now_part_str);
            part1.append(":");
            part1.append(all_part_str);
            part1.append(",");
            //
            unsigned int start_offset = i * MAX_PAYLOAD_LENGTH;
            unsigned int now_part_payload_length = MAX_PAYLOAD_LENGTH; // payload length
            if(i == need_to_send_times - 1) {
                now_part_payload_length = all_waiting_send_data_length % MAX_PAYLOAD_LENGTH;
            }
            //
            unsigned int data_part_length = part1.length() + now_part_payload_length + stop_flag_length;// ******
            void * data_part = malloc(data_part_length);// *******
            memset(data_part,0,data_part_length);
            //
            memcpy(data_part,part1.c_str(),part1.length());
            //
            memcpy((char *)data_part + part1.length(),(char *)data + start_offset,now_part_payload_length);
            //
            memcpy((char *)data_part + (part1.length() + now_part_payload_length), STOP_FLAG, stop_flag_length);
            //
            sendto(fileSenderConfig.sock_fd,data_part,data_part_length,0,(sockaddr *) &fileSenderConfig.client_address,sizeof(fileSenderConfig.client_address));
            //
            free(data_part);
            now_part_str.clear();
        }
        free(verify_code);
        free(waiting_send_data);
        return FileSenderEnum_SUCCESSFUL;
    }
    return FileSenderEnum_FAILED;
}