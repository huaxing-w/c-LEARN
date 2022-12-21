#include "bits/stdc++.h"
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

template<typename T>
T factorial(T n){
    auto ans=n;
    while(n>1){
        ans*=--n;
    }
    return ans;
}





int main(){

    int a=5;
    cout<<"the answer for a is: "<<factorial(a)<<endl;

    ull b=12;
    cout<<"the answer for b is: "<<factorial(b)<<endl;

    ld c=1.232;
    cout<<"the answer for c is: "<<factorial(c)<<endl;
    return 0;
}