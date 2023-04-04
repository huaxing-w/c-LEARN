#include "bits/stdc++.h"
using namespace std;

//foreigner 
class foreigner{
public:
    virtual string confession()=0;
    void setResult(string res){
        cout<<"Panda say: "<<res<<endl;
    }
    virtual ~foreigner(){}
};

//american
class american : public foreigner{
    string confession() override{
        return "sorry";
    }
};

//french
class french :public foreigner{
    string confession() override{
        return "désolée";
    }
};



class panda{
public:
    void receiveMessage(string msg){
        cout<<msg<<endl;
    }
    string sendMessage(){
        return "不，我不原谅你";
    }
};

//adapter

class abstractAdapter{
protected:
    foreigner* _f;
    panda* _p;
public:
    abstractAdapter(foreigner* f):_f(f){};
    virtual void translateToPanda()=0;
    virtual void translateToHuman()=0;
    virtual ~abstractAdapter(){}
};

class englishTranslator:public abstractAdapter{
public:
    //继承构造函数，继承的不是一个构造函数而是多个
    using abstractAdapter::abstractAdapter;
    void translateToPanda() override{
        string msg=_f->confession();
        _p->receiveMessage(msg);
    }
    void  translateToHuman() override{
        string msg=_p->sendMessage();
        //转换成英语
        _f->setResult("美国佬： "+msg);
    }
};

class frenchTranslator:public abstractAdapter{
public:
    using abstractAdapter::abstractAdapter;
    void translateToPanda() override{
        string msg=_f->confession();
        _p->receiveMessage(msg);
    }
    void  translateToHuman() override{
        string msg=_p->sendMessage();
        //转换成英语
        _f->setResult("法国佬： "+msg);
    }
};




int main(){
    foreigner* foreigner=new american;
    abstractAdapter* adapter=new englishTranslator(foreigner);
    adapter->translateToPanda();
    adapter->translateToHuman();
    delete foreigner;
    delete adapter;
    cout<<"==============="<<endl;
    foreigner=new french;
    adapter=new frenchTranslator(foreigner);
    adapter->translateToPanda();
    adapter->translateToHuman();
    delete foreigner;
    delete adapter;

    return 0;
}