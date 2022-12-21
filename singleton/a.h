//将类的构造方法设计成私有方法
//定义一个私有的类的静态实例
//定义一个公有的静态方法，用于返回类的静态实例


#include "bits/stdc++.h"
using namespace std;
class A{
    private:
    A();
    A(const A& a);
    ~A();
    A& operator=(const A& a);
    
    private:
    static A* _pInstance;
    string _name;

    public:
    static A* getInstance();
    void print();

};