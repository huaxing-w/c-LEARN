#include "bits/stdc++.h"
using namespace std;

class singleton{
public:
    static singleton& getInstance(){
        return _instance;
    }
    void print(){
        cout<<"hello, I am singleton!"<<endl;
    }
private:
    static singleton _instance;
    singleton(){
        cout<<"hello, I create a singleton"<<endl;
    }
    singleton(const singleton& s)=default;
    singleton& operator=(const singleton& s)=default;
};

//这里需要初始化才可以用这样的写法，实际上没有任何的意义，而且会很混乱！
//就用那个懒惰生成的写法最好了！
singleton singleton::_instance;


int main(){

    singleton::getInstance().print();
    singleton::getInstance().print();

    return 0;
}