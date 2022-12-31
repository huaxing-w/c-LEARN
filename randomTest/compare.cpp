#include "bits/stdc++.h"
using namespace std;

struct student{
    string name;
    int age;
    student(string n, int a){
        this->age=a;
        this->name=n;
    };
    
};

std::ostream& operator<<(std::ostream &strm, student& a) {
  return strm << "Name: "<<a.name<<" Age: "<<a.age;
}

bool byAgeFunc(student& a, student &b){
    return a.age>b.age;
}

struct byAgeStruct{
    bool operator()(student& a, student& b){
        return a.age>b.age;
    }
}obj;

int main(){
    student alice("alice",25);
    student bob("bob",18);
    student cc("cc",33);

    vector<student>temp1={alice,bob,cc};
    vector<student>temp2={alice,bob,cc};
    vector<student>temp3={alice,bob,cc};

    sort(temp1.begin(),temp1.end(),[](auto& a, auto& b){
        return a.age>b.age;
    });
    for(auto& i:temp1) cout<<i<<endl;

    sort(temp2.begin(),temp2.end(),byAgeFunc);
    for(auto& i:temp2) cout<<i<<endl;

    sort(temp3.begin(),temp3.end(),obj);
    for(auto& i:temp3) cout<<i<<endl;





    return 0;
}