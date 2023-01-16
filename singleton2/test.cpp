#include "bits/stdc++.h"
using namespace std;

class singleton{
public:
    static singleton& getInstance(){
        static singleton s;
        return s;
    }
    void print(){
        cout<<"hello, I am singleton!"<<endl;
    }
private:
    singleton(){
        cout<<"hello, I create a singleton"<<endl;
    }
    singleton(const singleton& s)=default;
    singleton& operator=(const singleton& s)=default;
};




int main(){

    singleton::getInstance().print();
    singleton::getInstance().print();

    return 0;
}