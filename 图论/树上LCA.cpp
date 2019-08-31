//树上LCA
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAX = 1e5+100;
struct Edge{
	int u,v,nxt,w;
}edge[MAX<<2];
typedef pair<int,int> pi;
int head[MAX<<2],tot=0,n,m,dep[MAX],cnt=0,fa[MAX];
int f[MAX][30],Gmax[MAX][30],Gmin[MAX][30];
int minn,maxx;
map<pi,int> mp;
void add(int u,int v,int w){
	edge[++tot].u=u;
	edge[tot].v=v;
	edge[tot].w=w;
	edge[tot].nxt=head[u];
	head[u]=tot;
}

//求树上每个点高度
void dfs(int u,int ff,int w){
	fa[u]=ff,dep[u]=dep[ff]+1;
	pi x=make_pair(u,ff);
	mp[x]=w;
	for(int i=head[u];i;i=edge[i].nxt){
		int v=edge[i].v;
		if(v==ff)   continue;
		dfs(v,u,edge[i].w);
	}
}

//f[j][i]:与j节点距离为2^i的节点的编号
//Gmax/Gmin 维护该路径上的最大/最小边权
void pre(){
	for(int i=1;i<=n;i++){
		f[i][0]=fa[i];
		Gmax[i][0]=mp[make_pair(i,fa[i])];
		Gmin[i][0]=Gmax[i][0];
		//cout<<i<<" "<<fa[i]<<endl;
	}
	for(int i=1;i<=20;i++){
		for(int j=1;j<=n;j++){
			if(dep[f[j][i-1]]<=0) continue;
			if(dep[f[j][i-1]]-(1<<(i-1))<=0) continue;
			f[j][i]=f[f[j][i-1]][i-1];
			Gmax[j][i]=max(Gmax[j][i-1],Gmax[f[j][i-1]][i-1]);
			Gmin[j][i]=min(Gmin[j][i-1],Gmin[f[j][i-1]][i-1]);
		}
	}
}

//求x与y节点的最近公共祖先
int LCA(int x,int y){
	if(dep[x]<dep[y]) swap(x,y);
	for(int i=20;i>=0;i--){
		if(dep[f[x][i]]>=dep[y]) x=f[x][i];
		if(x==y) return x;
	}
	for(int i=20;i>=0;i--){
		if(f[x][i]!=f[y][i]){
			x=f[x][i];
			y=f[y][i];
		}
	}
	return f[x][0];
}

void solve(int x,int y){
	for(int i=20;i>=0;i--){
		if(dep[f[x][i]]>=dep[y]){
			maxx=max(maxx,Gmax[x][i]);
			minn=min(minn,Gmin[x][i]);
			x=f[x][i];
		}
	}
}

int main() {
	//freopen("data.in","r",stdin);
	cin>>n;
	int u,v,w;
	for(int i=1;i<n;i++){
		cin>>u>>v>>w;
		add(u,v,w);
		add(v,u,w);
	}
	dfs(1,0,0);
	pre();
	int x,y;
	cin>>m;
	for(int i=1;i<=m;i++){
		minn=0x3f3f3f3f;
		maxx=0;
		cin>>x>>y;
		int r=LCA(x,y);
		solve(x,r);
		solve(y,r);
		cout<<minn<<" "<<maxx<<endl;
	}
	return 0;
}
