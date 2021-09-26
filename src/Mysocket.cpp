#include "../include/Mysocket.h"


socketBase::socketBase(Persion perso):result(true),persion(perso)
{
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(9999);
    servaddr.sin_family = AF_INET;

    socketFd = socket(AF_INET,SOCK_STREAM,0);
    if (socketFd < -1)
    {
        perror("create socket error");   
        result = false;     
    }
    printf("创建套接字成功\n");
    int i = 0;
    for ( ;i<MAXSIZE;i++ )
    {
        fd[i] = -1;
    }
    
}

socketBase::~socketBase()
{

}

bool socketBase::bindAddr()
{
    bool res = true;

    int flags = 1;
    setsockopt(socketFd,SOL_SOCKET,SO_REUSEADDR,&flags,sizeof(flags));
    if (bind(socketFd,(struct sockaddr*)&servaddr,sizeof(servaddr)) < 0){
        perror("bind err");
        res = false;
    }
    printf("地址绑定成功\n");
    return res;
}

bool socketBase::connectServer()
{
    bool res = true;
    printf("开始链接服务器\n");
    if (connect(socketFd,(sockaddr*)&servaddr,sizeof(struct sockaddr)) < 0)
    {
        perror("connect is error");
        res = false;
    }
    writeMsg(persion.user_name,socketFd);   //链接成功就发送用户名
    std::cout<<"服务器发来的信息为："<<readMsg(persion.user_name,socketFd) <<std::endl; //服务器欢迎语
    return res;
}

void socketBase::newConnect()
{
    socklen_t len = sizeof(servaddr);
    int cfd = accept(socketFd,(struct sockaddr*)&servaddr,&len);
    printf("客户端已经链接\n");
    std::string msg = "欢迎你 加入群聊";
    writeMsg(msg,cfd);
    int i = 0;
    for (i = 1; i < MAXSIZE; i++)//监视connfd是否可读、可写
    {
        if (fd[i] < 0) 
        {
            fd[i] = cfd;  /* save descriptor */
            break;
        }
    }
               
    if (i == MAXSIZE){ printf("too many clients\n");}
    // return cfd;
 
}

std::string socketBase::readMsg(std::string &msg,int fd)      //发送消息
{
    printf("读取数据\n");
    char buf[64] = {0};
    int sizeNum = read(fd,buf,sizeof(buf));

    if(sizeNum == 0) //对方关闭
    {
        printf("客户端关闭");
    }
    printf("收到的信息为 %s \n",buf);
    return std::string(buf);
    
}

void socketBase::writeMsg(std::string msg,int fd)   //发送消息
{
    if(msg.c_str() == NULL)
    {
        printf("msg is error \n");
        return;
    }
    write(fd,msg.c_str(),sizeof(msg.length()));
}
