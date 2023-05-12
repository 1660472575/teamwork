#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>          
#include <sys/socket.h>

#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

// socket-->bind-->listen-->accept-->read-->write;
// 

void main()
{
        unsigned int count = 0;
        // 1、这一步做了什么   主动套接字:发送请求
        // 被动套接字:只能接受请求
        // socket创建一个主动套接字sockfd
        int sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if(sockfd == -1){
            perror("func socket error\n");
            exit(0);
        }
        
        struct sockaddr_in peerAddr;
        peerAddr.sin_family = AF_INET;   // IPV4 使用这个协议类型
        peerAddr.sin_port = htons(8001); // 绑定的端口号，需要使用网络字节序
        peerAddr.sin_addr.s_addr = inet_addr("127.0.0.1") ; // 绑定的IP地址，需要使用网络字节序
        socklen_t addrlen = sizeof(peerAddr);
        // 绑定一个端口号
        if(bind(sockfd, (struct sockaddr *)&peerAddr,addrlen) < 0){
                perror("func bind error\n");
                exit(0);
        }
        // 套接字变化
        // 主动地套接字变化为被动套接字
        if(listen(sockfd, SOMAXCONN) < 0){
            perror("func listen error\n");
            exit(0);    
        }
        // 创建了新的套接字
        int conn = accept(sockfd, (struct sockaddr *)&peerAddr, (socklen_t *)&addrlen);
        if(conn < 0){
            perror("func accept error\n");
            exit(0);    
        }
        // 服务器端至少有两个套接字，主动套接字、被套接字；
        // 服务器端会创建两个套接字队列，队列的长度SOMAXCONN以前默认为128个
        // 消息队列1：已经连接上的套接字、还未连接上的套接字；
        
        char buf[1024] ={0};
        while(1)
        {
            count = read(conn,buf,sizeof(buf));    
            if(count == 0){
                printf("client disconnected...\n");
                exit(0);    
            }else if(count < 0){
                printf("read error...\n");
                exit(0);    
            }
            fputs(buf,stdout);
            
            write(conn,buf,count);
        }
        close(conn);
        close(sockfd);    
}



