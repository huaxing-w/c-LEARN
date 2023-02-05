#include "bits/stdc++.h"
using namespace std;

// abstract smile class
class abstractSmile{
public:
    virtual void transform()=0;
    virtual void ability()=0;
    virtual ~abstractSmile(){}

};

class sheepSmile : public abstractSmile {
public:
    void transform() override{
        cout<<"turn into sheep!"<<endl;
    }
    void ability() override{
        cout<<"mehhhhhh!"<<endl;
    }
};

class lionSmile : public abstractSmile {
public:
    void transform() override{
        cout<<"turn into lion!"<<endl;
    }
    void ability() override{
        cout<<"wowowow!"<<endl;
    }
};

class batSmile : public abstractSmile {
public:
    void transform() override{
        cout<<"turn into bat!"<<endl;
    }
    void ability() override{
        cout<<"biu biu biu!"<<endl;
    }
};

//factory class

enum class Type:char{sheep,lion,bat};
class smileFactory{
public:
    abstractSmile* createSmile(Type type){
        abstractSmile* ptr=nullptr;
        switch (type){
            case Type::sheep:
                ptr=new sheepSmile;
                break;
            case Type::lion:
                ptr=new lionSmile;
                break;
            case Type::bat:
                ptr=new batSmile;
                break;
            default:
                break;   
        }
        return ptr;
    }
};



int main(){
    smileFactory* factory=new smileFactory;
    abstractSmile* lionObj=factory->createSmile(Type::lion);
    lionObj->transform();
    lionObj->ability();
    return 0;
}