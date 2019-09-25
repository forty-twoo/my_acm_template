//基础树链剖分，求和及最大
#include<bits/stdc++.h>
#define mst(a,x) memset(a,x,sizeof(a))
#define debug freopen("data.txt","r",stdin)
#define lowbit(x) x&-x
#define prique priority_queue
#define INF 0x3f3f3f3f
#define eps 1e-8
#define pb push_back
typedef long long ll;
const int MAX=4e4+100;
const int MAXN=1e6+10;
const int MOD=1e9+7;
using namespace std;
int n,m,a[MAX],head[MAX],tot;
struct Edge{
	int u,v,nxt;
}edge[MAX<<1];
int top[MAX],son[MAX],fa[MAX],sz[MAX],dep[MAX],id[MAX],cnt,rk[MAX];
void addedge(int u,int v){
	edge[++tot].u=u;edge[tot].v=v;
	edge[tot].nxt=head[u];head[u]=tot;
}
int dfs1(int u,int ff){
	sz[u]=1;dep[u]=dep[ff]+1;fa[u]=ff;
	for(int i=head[u];i;i=edge[i].nxt){
		int v=edge[i].v;
		if(v==ff) continue;
		sz[u]+=dfs1(v,u);
		if(sz[v]>sz[son[u]]){
			son[u]=v;
		}
	}
	return sz[u];
}
void dfs2(int u,int ff){
	top[u]=ff;
	id[u]=++cnt;
	rk[cnt]=u;
	if(son[u]){
		dfs2(son[u],ff);
	}
	for(int i=head[u];i;i=edge[i].nxt){
		int v=edge[i].v;
		if(v!=son[u] && v!=fa[u])
			dfs2(v,v);
	}
}

struct SEGT{
#define lc rt<<1
#define rc rt<<1|1
#define lson lc,l,mid
#define rson rc,mid+1,r
	int sum[MAX<<2],maxv[MAX<<2];
	void pushup(int rt){
		sum[rt]=sum[lc]+sum[rc];
		maxv[rt]=max(maxv[lc],maxv[rc]);
	}
	void build(int rt,int l,int r){
		if(l==r){
			sum[rt]=maxv[rt]=a[rk[l]];
			return;
		}
		int mid=(l+r)>>1;
		build(lson);build(rson);
		pushup(rt);
	}
	void change(int rt,int l,int r,int x,int v){
		if(l==r){
			sum[rt]=maxv[rt]=v;
			return;
		}
		int mid=(l+r)>>1;
		if(x<=mid) change(lson,x,v);
		else change(rson,x,v);
		pushup(rt);
	}
	int querysum(int rt,int l,int r,int L,int R){
		int ans=0;
		if(L<=l && r<=R){
			return sum[rt];
		}
		int mid=(l+r)>>1;
		if(L<=mid)ans+=querysum(lson,L,R);
		if(R>mid)ans+=querysum(rson,L,R);
		return ans;
	}
	int querymax(int rt,int l,int r,int L,int R){
		int ans=-INF;
		if(L<=l && r<=R){
			ans=max(ans,maxv[rt]);
			return ans;
		}
		int mid=(l+r)>>1;
		if(L<=mid)ans=max(ans,querymax(lson,L,R));
		if(R>mid)ans=max(ans,querymax(rson,L,R));
		return ans;
	}

}T;
int getmax(int x,int y){
	int ans=-INF;
	int tx=top[x],ty=top[y];
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		ans=max(ans,T.querymax(1,1,n,id[top[x]],id[x]));
		x=fa[top[x]];
	}
	if(dep[x]<dep[y]) swap(x,y);
	ans=max(ans,T.querymax(1,1,n,id[y],id[x]));
	return ans;
}

int getsum(int x,int y){
	int ans=0;
	int tx=top[x],ty=top[y];
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		ans+=T.querysum(1,1,n,id[top[x]],id[x]);
		x=fa[top[x]];
	}
	if(dep[x]<dep[y]) swap(x,y);
	ans+=T.querysum(1,1,n,id[y],id[x]);
	return ans;
}

char op[10];
int main(){
#ifndef ONLINE_JUDGE
	debug;
#endif

	tot=cnt=0;
	scanf("%d",&n);
	int u,v;
	for(int i=1;i<n;i++){
		scanf("%d%d",&u,&v);
		addedge(u,v);addedge(v,u);
	}
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
	}
	fa[1]=1;
	dfs1(1,-1);dfs2(1,1);
	T.build(1,1,n);
	int x,y,c;
	scanf("%d",&m);
	for(int i=1;i<=m;i++){
		scanf("%s%d%d",op,&x,&y);
		if(op[1]=='M'){
			int ans=getmax(x,y);
			printf("%d\n",ans);
		} else if(op[1]=='S'){
			int ans=getsum(x,y);
			printf("%d\n",ans);
		} else{
			T.change(1,1,n,id[x],y);
		}
	}
	return 0;
}
