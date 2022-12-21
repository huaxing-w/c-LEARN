#include "bits/stdc++.h"
using namespace std;

template<typename T>
T add(T a, T b){
    return a + b;
}

int main(){
    int a=1;
    int b=3;
    string c="hello";
    string d="world";
    cout<<"the sum of a and b is: "<<add<int>(a,b)<<endl;
    cout<<"the sum of c and d is: "<<add(c,d)<<endl;
    return 0;
}