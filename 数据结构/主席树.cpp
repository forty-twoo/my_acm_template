#include<bits/stdc++.h>
#define mst(a,x) memset(a,x,sizeof(a))
#define debug freopen("data.txt","r",stdin)
#define PI pair<int,int>
#define INF 0x3f3f3f3f
typedef long long ll;
using namespace std;
const int MAX = 2e5 + 10;
const int MAXN = MAX * 20;
const ll MOD = 998244353;
int n,m,ks,Lim,rt[MAX];
ll a[MAX],b[MAX];

//静态区间第K大
struct ChairmanTree {
	int lc[MAXN],rc[MAXN],cnt = 0,sum[MAXN];
    inline void build(int &o,int l,int r){
        o=++cnt;
        if(l==r) return;
        int mid=(l+r)>>1;
        build(lc[o],l,mid);build(rc[o],mid+1,r);
    }
    inline void insrt(int &o,int pre,int l,int r,int p){
        o=++cnt;lc[o]=lc[pre];rc[o]=rc[pre];sum[o]=sum[pre]+1;
        if(l==r) return;
        int mid=(l+r)>>1;
        if(p<=mid) insrt(lc[o],lc[pre],l,mid,p);
        else insrt(rc[o],rc[pre],mid+1,r,p);
    }
    inline int query(int o,int pre,int l,int r,int k){
        if(l==r) return l;
        int mid=(l+r)>>1;
        int x=sum[lc[o]]-sum[lc[pre]];
        if(x>=k) return query(lc[o],lc[pre],l,mid,k);
        else return query(rc[o],rc[pre],mid+1,r,k-x);
    }

}T;

int main() {
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%lld",&a[i]);
        b[i]=a[i];
    }
    //离散化
    sort(b+1,b+1+n);
    Lim=unique(b+1,b+1+n)-(b+1);

    T.build(rt[0],1,Lim);

    for(int i=1;i<=n;i++){
        int x=lower_bound(b+1,b+1+Lim,a[i])-b;
        T.insrt(rt[i],rt[i-1],1,Lim,x);
    }

    while(m--){
        int l,r,k;
        scanf("%d%d%d",&l,&r,&k);
        int x=T.query(rt[r],rt[l-1],1,Lim,k);
        printf("%lld\n",b[x]);
    }
	return 0;
}
