#include<bits/stdc++.h>
#define mst(a,x) memset(a,x,sizeof(a))
#define debug freopen("data.txt","r",stdin)
#define lowbit(x) x&-x
#define prique priority_queue
#define INF 0x3f3f3f3f
#define eps 1e-8
#define pb push_back
typedef long long ll;
using namespace std;
const int MAX = 5e4+10;
const int MOD = 998244353;
int ks;
int n,k,a[MAX];

struct edge {
	int to,capacity,cost,rev;
	edge() {}
	edge(int to,int _capacity,int _cost,int _rev):to(to),capacity(_capacity),cost(_cost),rev(_rev) {}
};
struct Min_Cost_Max_Flow {
	int V,H[MAX + 5],dis[MAX + 5],PreV[MAX + 5],PreE[MAX + 5];
	vector<edge> G[MAX+ 5];

	void Init(int n) {
		V = n;
		for(int i = 0; i <= V; ++i)G[i].clear();
	}

	void Add_Edge(int from,int to,int cap,int cost) {
		G[from].push_back(edge(to,cap,cost,G[to].size()));
		G[to].push_back(edge(from,0,-cost,G[from].size() - 1));
	}

	int Min_cost_max_flow(int s,int t,int f,int& flow) {
		int res = 0; fill(H,H + 1 + V,0);
		while(f) {
			priority_queue <pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>> > q;
			fill(dis,dis + 1 + V,INF);
			dis[s] = 0; q.push(pair<int,int>(0,s));
			while(!q.empty()) {
				pair<int,int> now = q.top(); q.pop();
				int v = now.second;
				if(dis[v] < now.first)continue;
				for(int i = 0; i < G[v].size(); ++i) {
					edge& e = G[v][i];
					if(e.capacity > 0 && dis[e.to] > dis[v] + e.cost + H[v] - H[e.to]) {
						dis[e.to] = dis[v] + e.cost + H[v] - H[e.to];
						PreV[e.to] = v;
						PreE[e.to] = i;
						q.push(pair<int,int>(dis[e.to],e.to));
					}
				}
			}
			if(dis[t] == INF)break;
			for(int i = 0; i <= V; ++i)H[i] += dis[i];
			int d = f;
			for(int v = t; v != s; v = PreV[v])d = min(d,G[PreV[v]][PreE[v]].capacity);
			f -= d; flow += d; res += d*H[t];
			for(int v = t; v != s; v = PreV[v]) {
				edge& e = G[PreV[v]][PreE[v]];
				e.capacity -= d;
				G[v][e.rev].capacity += d;
			}
		}
		return res;
	}
	int Max_cost_max_flow(int s,int t,int f,int& flow) {
		int res = 0;
		fill(H,H + 1 + V,0);
		while(f) {
			priority_queue <pair<int,int>> q;
			fill(dis,dis + 1 + V,-INF);
			dis[s] = 0;
			q.push(pair<int,int>(0,s));
			while(!q.empty()) {
				pair<int,int> now = q.top(); q.pop();
				int v = now.second;
				if(dis[v] > now.first)continue;
				for(int i = 0; i < G[v].size(); ++i) {
					edge& e = G[v][i];
					if(e.capacity > 0 && dis[e.to] < dis[v] + e.cost + H[v] - H[e.to]) {
						dis[e.to] = dis[v] + e.cost + H[v] - H[e.to];
						PreV[e.to] = v;
						PreE[e.to] = i;
						q.push(pair<int,int>(dis[e.to],e.to));
					}
				}
			}
			if(dis[t] == -INF)break;
			for(int i = 0; i <= V; ++i)H[i] += dis[i];
			int d = f;
			for(int v = t; v != s; v = PreV[v])d = min(d,G[PreV[v]][PreE[v]].capacity);
			f -= d; flow += d;
			res += d*H[t];
			for(int v = t; v != s; v = PreV[v]) {
				edge& e = G[PreV[v]][PreE[v]];
				e.capacity -= d;
				G[v][e.rev].capacity += d;
			}
		}
		return res;
	}
}mcmf;

void solve(){
	//S: IN:2n+1 OUT:2n+2
	//T: 2n+3 
	mcmf.Init(2*n+3);
	for(int i=1;i<=n;i++){
		mcmf.Add_Edge(i,i+n,1,-a[i]);
		for(int j=i+1;j<=n;j++){
			if(a[j]>=a[i]){
				mcmf.Add_Edge(i+n,j,1,0);
			}
		}
	}
	mcmf.Add_Edge(2*n+1,2*n+2,k,0); 
	for(int i=1;i<=n;i++){
		mcmf.Add_Edge(2*n+2,i,1,0);
	}
	for(int i=1;i<=n;i++){
		mcmf.Add_Edge(i+n,2*n+3,1,0);
	}
	int flow=0;
	int ans=mcmf.Min_cost_max_flow(2*n+1,2*n+3,INF,flow);
	printf("%d\n",-ans);
}

int main(){
	debug;
	scanf("%d",&ks);
	while(ks--){
		scanf("%d%d",&n,&k);
		for(int i=1;i<=n;i++) scanf("%d",&a[i]);
		solve();
	}
	
	return 0;
}
