/*
socket
*/

#ifndef H_SOCKET_H
#define H_SOCKET_H

#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/epoll.h>

#define MAXSIZE 1024
struct Persion
{
    std::string user_name;
    int passward;
    int fd;
    Persion(std::string name = "张三",int psd = 123,int fd = -1):user_name(name),passward(psd),fd(fd){}

};

class socketBase
{
    public:
        socketBase(Persion);
        ~socketBase();
        bool bindAddr();
        void listemAdd(){listen(socketFd,12);}
        bool connectServer();
        void newConnect();
        std::string readMsg(std::string &,int);      //接受消息
        void writeMsg(std::string ,int);   //发送消息

    private:
        struct sockaddr_in servaddr;
        int fd[MAXSIZE];
        int socketFd;
        bool result;
        Persion persion;

};

#endif // !H_SOCKET_H

