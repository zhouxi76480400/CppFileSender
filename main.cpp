#include <iostream>
//#include <string.h>

#include "SocketFile.h"

#include <pthread.h>

#include "SocketFileServer.h"
//#include "exception"


#include "FileSender.h"

#include <signal.h>

//const char * client_address = "127.0.0.1";
//
//const int16_t client_port = 20001;

void * share_mem_buff;

size_t buff_size;

//size_t write_data_to_buff(void * buff) {
//    size_t wrote_data_len = 0;
//
//
//
//    return wrote_data_len;
//}

void notify_new_data_buffer_read() {


}


void * child_thread(void * shared_mem_buff) {
    std::cout << "child_thread:" << share_mem_buff << std::endl;

}

SocketFileServer server;

void signal_pipe_handler(int sig) {
    std::cout << "SIGPIPE !" << std::endl;
    server.closeClientFd();
}



int main() {
    signal(SIGPIPE,signal_pipe_handler);
//    FileSenderConfig config;
//    //
//    bzero(&config.my_address, sizeof(config.my_address));
//    config.my_address.sin_family = AF_INET;
//    config.my_address.sin_addr.s_addr = htonl(INADDR_ANY);
//    config.my_address.sin_port = htons(0);
//    //
//    bzero(&config.client_address, sizeof(config.client_address));
//    config.client_address.sin_family = AF_INET;
//    config.client_address.sin_addr.s_addr = inet_addr(client_address);
//    config.client_address.sin_port = htons(client_port);
//    //
//    init_sock_fd(&config);
//    //




    FILE * fp;
    std::string file_path = "/Users/zhouxi/CLionProjects/CppFileSender/743272_0_rgb.bmp";
    fp = fopen(file_path.c_str(),"rb");
    if(fp != nullptr) {
        size_t length = 1280 * 720 * 3 * sizeof(uint8_t);

        share_mem_buff = malloc(length);
        memset(share_mem_buff,0,length);
        buff_size = length;



        void * file_p = malloc(length);
        memset(file_p,0,length);
        fread(file_p,sizeof(uint8_t), length, fp);

//        sendFileByUDP2(config,file_p,length);

//        sendMessage(config,file_path);

//        pthread_t pthread;
//
//        pthread_create(&pthread, nullptr, child_thread, share_mem_buff);
//
//        pthread_join(pthread, nullptr);
//
//        std::cout << "from_main:" << share_mem_buff << std::endl;
//
//
//        for(int i = 0 ; i < 3 ; i ++) {
//
//
//        }

        int ret = server.createService();
        if(ret >= 0) {
            while (1) {

                try {
                    if (server.accept() == -1) {
                        perror("accept error");
                        continue;
                    }
                    int write_size = 0;

                    while ((write_size = server.write(file_p,length)) > 0) {
                        std::cout << "write: " << write_size << std::endl;

                        sleep(5);
                    }

                } catch (std::exception e) {
                    std::cout << e.what() << std::endl;
                }




            }
        }




        free(file_p);
        fclose(fp);
    }



//    int l = 1024;
//    for (int i = 0 ; i < 10 ; i ++ ) {
//        auto data = malloc(l);
//        memset(data, 'a' ,l);
//        ((char *)data)[0] = 'e';
//        ((char *)data)[500] = 'b';
//        ((char *)data)[1000] = 'c';
//        sendFileByUDP(config, data, l);
//        free(data);
//    }

//    release_sock_fd(&config);


//    pthread_t t = pthread_self();
//
//    std::cout << t << std::endl;

//    init_socket_file_local();

    free(share_mem_buff);

    return 0;
}
