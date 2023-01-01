#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

int main(){
    //创建监听的socket
    int fd=socket(AF_INET,SOCK_STREAM,0);
    if(fd==-1){
        perror("socket");
        return -1;
    }
    //绑定本地ip和端口
    struct sockaddr_in saddr;
    saddr.sin_family=AF_INET;
    //注意这里端口是小段->大端
    saddr.sin_port=htons(9999);
    saddr.sin_addr.s_addr=INADDR_ANY;//0.0.0.0 绑定本地实际ip地址
    int ret=bind(fd,(struct sockaddr*)&saddr,sizeof(saddr));
    if(ret==-1){
        perror("bind");
        return -1;
    }
    //设置监听
    ret=listen(fd,128);

    //阻塞并等待客户端链接
    struct sockaddr_in caddr;
    //求出传出的caddr的大小
    int addrlen=sizeof(caddr);
    //注意传的时候都是指针
    int cfd=accept(fd,(struct sockaddr_in*)&caddr,&addrlen);
    if(cfd==-1){
        perror("accept");
        return -1;
    }

    //此时链接简历成功,打印客户端的ip和端口信息
    //注意此时要转换成小端
    char ip[32];
    printf("ip of client is: %s, port is: %d\n",
    inet_ntop(AF_INET,&caddr.sin_addr.s_addr,ip,sizeof(ip)),ntohs(caddr.sin_port));

    //和建立链接的客户端进行通信
    while(1){
        //receive data
        char buff[1024];
        int len=recv(cfd,buff,sizeof(buff),0);
        if(len>0){
            printf("client says: %s\n",buff);
            send(cfd,buff,len,0);
        }
        else if(len==0){
            printf("client disconnected.\n");
            break;
        }
        else{
            perror("recv");
            break;
        }
    }

    //turn off all the fd
    close(fd);
    close(cfd);


    return 0;
}