#include "bits/stdc++.h"
using namespace std;


class shipBody{
public:
    virtual string getBody()=0;
    //不加就是销毁的父类资源，加了析构函数就是子类资源
    virtual ~shipBody(){}
};

class woodBody: public shipBody{
public:
    string getBody() override{
        return string("using wood to build ship!");
    }
};

class ironBody: public shipBody{
public:
    string getBody() override{
        return string("using iron to build ship!");
    }
};

class metalBody: public shipBody{
public:
    string getBody() override{
        return string("using metalBody to build ship!");
    }
};

class engine{
public:
    virtual string getEngine()=0;
    virtual ~engine(){}
};

class human: public engine{
public:
    string getEngine() override{
        return string("using human to ship!");
    }
};

class diesel: public engine{
public:
    string getEngine() override{
        return string("using diesel to ship!");
    }
};

class nuclear: public engine{
public:
    string getEngine() override{
        return string("using nuclear to ship!");
    }
};

class weapon{
public:
    virtual string getweapon()=0;
    virtual ~weapon(){}
};

class gun: public weapon{
public:
    string getweapon() override{
        return string("using gun to fight!");
    }
};

class cannon: public weapon{
public:
    string getweapon() override{
        return string("using cannon to fight!");
    }
};

class laser: public weapon{
public:
    string getweapon() override{
        return string("using laser to fight!");
    }
};

class ship{
    shipBody* m_body;
    engine* m_engine;
    weapon* m_weapon;
public:
    ship(shipBody* body, engine* engine, weapon* weapon): m_body(body),m_engine(engine),m_weapon(weapon){}
    ~ship(){
        delete m_body;
        delete m_engine;
        delete m_weapon;
    }
    string getProperty(){
        string info=m_body->getBody()+" "+m_engine->getEngine()+" "+m_weapon->getweapon();
        return info;
    }
};

class abstractFactory{
public:
    virtual ship* createShip()=0;
    virtual ~abstractFactory(){}
};

class basicFactory: public abstractFactory{
public:
    ship* createShip() override{
        cout<<"building a basic ship"<<endl;
        return new ship(new woodBody,new human, new gun);
    }
};

class standardFactory: public abstractFactory{
public:
    ship* createShip() override{
        cout<<"building a standard ship"<<endl;
        return new ship(new ironBody,new diesel, new cannon);
    }
};

class ultimateFactory: public abstractFactory{
public:
    ship* createShip() override{
        cout<<"building a ultimate ship"<<endl;
        return new ship(new metalBody,new nuclear, new laser);
    }
};

int main(){

    abstractFactory* factory=new ultimateFactory;
    ship* ship=factory->createShip();
    cout<<ship->getProperty()<<endl;
    return 0;
}