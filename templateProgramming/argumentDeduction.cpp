#include "bits/stdc++.h"
using namespace std;

template<typename T1, typename T2>
auto add(T1& a, T2& b){
  return a+b;
}

template<typename T1, typename T2, typename T3>
T3 add(const T1& a, const T2& b){
  return a+b;
}

template<typename R, typename T1, typename T2>
R add(const T1& a, const T2& b){
  return a+b;
}


int main(){
  int a=1;
  double b=2.55;

  cout<<add<double>(a,b)<<endl;
  
  
  return 0;
}