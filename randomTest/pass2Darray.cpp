#include "bits/stdc++.h"
using namespace std;

int main(){
  const int m=10;
  const int n=20;
  int dp1[m];
  memset(dp1,0x3f3f3f3f,sizeof(dp1));
  //how to pass reference to the function
  function<void(int(&)[m])>print1D=[&](int (&dp1)[m])->void{
    for(auto& i:dp1){
      cout<<i<<" ";
    }
    cout<<endl;
  };

  print1D(dp1);

  int dp2[m][n];
  memset(dp2,-1,sizeof(dp2));


  //how to pass 2D array into ta function
  function<void(int(&)[m][n])>print2D=[&](int (&dp2)[m][n])->void{
    for(auto& i:dp2){
      for(auto& j:i){
        cout<<j<<" ";
      }
      cout<<endl;
    }
  };

  print2D(dp2);

  return 0;
}