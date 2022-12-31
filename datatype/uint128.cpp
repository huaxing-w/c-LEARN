#include "bits/stdc++.h"
#define PB push_back
#define PF push_front
#define LB lower_bound
#define UB upper_bound
#define fr(x) freopen(x,"r",stdin)
#define fw(x) freopen(x,"w",stdout)
#define REP(i, from, to) for(ll i = from;i<to;i++)
#define RREP(i, from, to) for(ll i = from;i>=to;i--)
#define complete_unique(a) a.erase(unique(begin(a),end(a)),end(a))
#define mst(x, a) memset(x,a,sizeof(x))
#define all(a) begin(a),end(a)
#define rall(a) rbegin(a),rend(a)
#define MP make_pair
#define lowbit(x) ((x)&(-(x)))
#define bitcnt(x) (__builtin_popcountll(x))
#define lson (ind<<1)
#define rson (ind<<1|1)
#define se second
#define fi first
#define EX0 exit(0);
typedef long long ll;
using namespace std;
int main(){
    __uint128_t a=1;
    bitset<20> b=1;
    cout<<b<<endl;
    b>>=1;
    cout<<b<<endl;

    b<<=1;
    cout<<b<<endl;


    return 0;
}