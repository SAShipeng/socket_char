#include "../include/Mysocket.h"


int main(int argc, const char** argv) 
{
    Persion man_1;
    man_1.user_name = "李四";
    socketBase server(man_1);
    server.connectServer();
    printf("结束\n");
}