#include "../include/Mysocket.h"


int main(int argc, const char** argv) 
{
    //构造一个人
    Persion man[10];
    man[0].user_name = "服务器";
    socketBase server(man[0]);
    server.bindAddr();
    server.listemAdd();
    server.newConnect();//获取链接到的fd
    printf("结束\n");
}