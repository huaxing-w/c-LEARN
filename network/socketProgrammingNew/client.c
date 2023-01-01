#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

int main(){
    //创建通信的socket
    int fd=socket(AF_INET,SOCK_STREAM,0);
    if(fd==-1){
        perror("socket");
        return -1;
    }
    //链接服务器
    struct sockaddr_in saddr;
    saddr.sin_family=AF_INET;
    //注意这里端口是小段->大端
    saddr.sin_port=htons(9999);
    inet_pton(AF_INET,"192.168.254.18",&saddr.sin_addr.s_addr);
    int ret=connect(fd,(struct sockaddr*)&saddr,sizeof(saddr));
    if(ret==-1){
        perror("connect");
        return -1;
    }

    int number=0;
    //和建立链接的客户端进行通信
    while(1){
        //send data
        char buff[1024];
        sprintf(buff,"hello, i am Huaxing wang, %d\n",number++);
        send(fd,buff,strlen(buff)+1,0);
        //receive data
        memset(buff,0,sizeof(buff));
        int len=recv(fd,buff,sizeof(buff),0);
        if(len>0){
            printf("server says: %s\n",buff);
   
        }
        else if(len==0){
            printf("server disconnected.\n");
            break;
        }
        else{
            perror("recv");
            break;
        }
        sleep(1);
    }

    //turn off all the fd
    close(fd);



    return 0;
}