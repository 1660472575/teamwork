
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>          
#include <sys/socket.h>

#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

// 服务器端：socket-->bind-->listen-->accept-->read-->write;
// 客户端：socket-->connect-->read-->write

/*
int connect(int sockfd, const struct sockaddr *addr,
                   socklen_t addrlen);
*/
void main()
{
        unsigned int count = 0;
        // 1、这一步做了什么 主动套接字、被动套接字
        int sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if(sockfd == -1){
            perror("func socket error\n");
            exit(0);
        }
        struct sockaddr_in peerAddr;
        peerAddr.sin_family = AF_INET;
        peerAddr.sin_port = htons(8001);
        peerAddr.sin_addr.s_addr = inet_addr("192.168.2.120") ;
        socklen_t addrlen = sizeof(peerAddr);
        
        if( connect(sockfd, (struct sockaddr *)&peerAddr, addrlen)< 0){
            perror("func     connect .... \n");
            exit(0);
        }
        
        char buf[1024] ={0};
        char sendbuf[1024] ={0};
         char *fgets(char *s, int size, FILE *stream);
        while(fgets(sendbuf,sizeof(sendbuf),stdin) != NULL)
        {
            write(sockfd,sendbuf,sizeof(sendbuf));
            
            
            read(sockfd,buf,sizeof(buf));    
            
            fputs(buf,stdout);
            
            memset(sendbuf,0,sizeof(sendbuf));
            memset(buf,0,sizeof(buf));
        }
            
}