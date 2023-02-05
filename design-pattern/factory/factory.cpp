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

//
class abstractFactory{
public:
    virtual abstractSmile* createSmile()=0;
    virtual ~abstractFactory(){}
};

class sheepFactory: public abstractFactory{
public:

    abstractSmile* createSmile() override{
        return new sheepSmile;
    }
    ~sheepFactory(){
        cout<<"sheep is deleted!"<<endl;
    }
};

class lionFactory: public abstractFactory{
public:

    abstractSmile* createSmile() override{
        return new lionSmile;
    }
    ~lionFactory(){
        cout<<"lion is deleted!"<<endl;
    }
};

class batFactory: public abstractFactory{
public:

    abstractSmile* createSmile() override{
        return new batSmile;
    }
    ~batFactory(){
        cout<<"bat is deleted!"<<endl;
    }
};



int main(){
    abstractFactory* factory=new lionFactory;
    abstractSmile* lionObj=factory->createSmile();
    lionObj->ability();
    lionObj->transform();
    delete lionObj;
    delete factory;

    return 0;
}