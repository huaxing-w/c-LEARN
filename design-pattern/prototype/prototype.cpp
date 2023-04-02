#include "bits/stdc++.h"
using namespace std;


//father
class germaSoldier{
public:
    virtual germaSoldier* clone()=0;
    virtual string whoAmI()=0;
    virtual ~germaSoldier(){}
};

//child
class soldier66:public germaSoldier{
public:
    germaSoldier* clone() override{
        return new soldier66(*this);
    }
    string whoAmI() override{
        return "I am soldier 66";
    }
};

class soldier67:public germaSoldier{
public:
    germaSoldier* clone() override{
        return new soldier67(*this);
    }
    string whoAmI() override{
        return "I am soldier 66";
    }
};


int main(){
    germaSoldier* obj=new soldier66;
    germaSoldier* soldier=obj->clone();
    cout<<soldier->whoAmI()<<endl;
    return 0;
}
