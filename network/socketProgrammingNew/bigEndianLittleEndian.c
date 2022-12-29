#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>

// u:unsigned
// 16: 16位, 32:32位
// h: host, 主机字节序
// n: net, 网络字节序
// s: short
// l: int

// 这套api主要用于 网络通信过程中 IP 和 端口 的 转换
// 将一个短整形从主机字节序 -> 网络字节序
uint16_t htons(uint16_t hostshort);	
// 将一个整形从主机字节序 -> 网络字节序
uint32_t htonl(uint32_t hostlong);	

// 将一个短整形从网络字节序 -> 主机字节序
uint16_t ntohs(uint16_t netshort);
// 将一个整形从网络字节序 -> 主机字节序
uint32_t ntohl(uint32_t netlong);


int main(){
    int a = 0x12345678;
    printf("%d\n",htons(a));
    return 0;
}