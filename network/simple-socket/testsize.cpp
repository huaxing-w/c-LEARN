#include "bits/stdc++.h"
using namespace std;

struct sockaddr{
    unsigned short sa_family;
    char sa_data[14];
};

struct in_addr{
    unsigned long s_addr;
};

struct sockaddr_in{
    short int sin_family;
    unsigned short int sin_port;
    struct in_addr sin_addr;
    unsigned char sin_zero[8];
};


int main(){

    sockaddr a;
    sockaddr_in b;
    in_addr c;
    cout<<"the size of sockaddr is: "<<sizeof(sockaddr)<<" bytes"<<endl;
    cout<<"the size of sa_family in sockaddr is "<<sizeof(a.sa_family)<<" bytes"<<endl;
    cout<<"the size of sa_data in sockaddr is "<<sizeof(a.sa_data)<<" bytes"<<endl;
    cout<<endl;

    cout<<"the size of in_addr is: "<<sizeof(in_addr)<<" bytes"<<endl;
    cout<<endl;

    cout<<"the size of sockaddr_in is: "<<sizeof(sockaddr_in)<<" bytes"<<endl;
    cout<<"the size of sin_family in sockaddr_in is: "<<sizeof(b.sin_family)<<" bytes"<<endl;
    cout<<"the size of sin_port in sockaddr_in is: "<<sizeof(b.sin_port)<<" bytes"<<endl;
    cout<<"the size of sin_addr in sockaddr_in is: "<<sizeof(b.sin_addr)<<" bytes"<<endl;
    cout<<"the size of sin_zero in sockaddr_in is: "<<sizeof(b.sin_zero)<<" bytes"<<endl;
    
    //the size of sockaddr_in is not 20 (2+2+8+8) is due to the potention padding

    return 0;
}
