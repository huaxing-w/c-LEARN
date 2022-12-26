#include "bits/stdc++.h"
using namespace std;


//返回值后置的写法
//这里不写decltype也是可以的，auto可以自己推断
template<typename T1, typename T2>
auto add(const T1& a, const T2& b)->decltype(a+b){
  return a+b;
}


int main(){
  int a=1;
  double b=1.4;
  int c=2;
  cout<<add(a,b)<<endl;
  cout<<add(a,c)<<endl;

  return 0;
}