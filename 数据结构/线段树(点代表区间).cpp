#include<bits/stdc++.h>
#define mst(a,x) memset(a,x,sizeof(a))
#define debug freopen("data.txt","r",stdin)
#define INF 0x3f3f3f3f
#define lson 2*rt,l,m
#define rson 2*rt+1,m+1,r
typedef long long ll;
using namespace std;
const int MAX = 8e5 + 10;
const ll MOD = 998244353;
ll x, y, a1, a2, b1, b2, c1, c2, x_, y_, m1, m2;
ll X[MAX], Y[MAX];
ll lb[MAX], rb[MAX], dc[MAX], tot;
int n;

//离散化后用点表示区间,每个点代表左闭右开的区间
//初始为空区间,每次插入L-R这个区间,求总区间的中位数
struct SEGTREE {
	ll num[MAX * 4], lazy[MAX * 4];
	void pushdown(int rt, int l, int r) {
		if (lazy[rt]) {
			int m = (r + l) / 2;
			//注意区间长度的求法 num[rt * 2] += lazy[rt] * (dc[m + 1] - dc[l]);
			num[rt * 2 + 1] += lazy[rt] * (dc[r + 1] - dc[m + 1]);

			lazy[rt * 2] += lazy[rt];
			lazy[rt * 2 + 1] += lazy[rt];
			lazy[rt] = 0;
		}
	}

	void insert(int rt, int l, int r, int L, int R) {
		if (L <= l && r <= R) {
			num[rt] += dc[r + 1] - dc[l];
			lazy[rt] += 1;
			return;
		}
		int m = (l + r) / 2;
		pushdown(rt, l, r);
		if (L <= m) insert(lson, L, R);
		if (R > m) insert(rson, L, R);
		num[rt] = num[rt * 2] + num[rt * 2 + 1];
	}

	ll  query(int rt, int l, int r, ll k) {
		if (l == r) {
			ll tms = num[rt] / (dc[r + 1] - dc[l]);
			return dc[l] + (k - 1) / tms;
		}
		int m = (l + r) / 2;
		pushdown(rt, l, r);
		if (num[rt * 2] >= k)
			query(lson, k);
		else
			query(rson, k - num[rt * 2]);
	}


}segtree;


int main() {
	ios::sync_with_stdio(0);
	cin >> n;
	cin >> x >> x_ >> a1 >> b1 >> c1 >> m1;
	cin >> y >> y_ >> a2 >> b2 >> c2 >> m2;
	X[1] = x, X[2] = x_, Y[1] = y, Y[2] = y_;
	for (int i = 3; i <= n; i++) {
		ll x = (a1*X[i - 1] + b1 * X[i - 2] + c1) % m1;
		ll y = (a2*Y[i - 1] + b2 * Y[i - 2] + c2) % m2;
		X[i] = x, Y[i] = y;
	}
	ll maxx = 0;
	for (int i = 1; i <= n; i++) {
		lb[i] = min(X[i], Y[i]) + 1;
		rb[i] = max(X[i], Y[i]) + 1 + 1; //右区间+1
		maxx = max(maxx, rb[i]);
		dc[++tot] = lb[i], dc[++tot] = rb[i];
	}
	sort(dc + 1, dc + 1 + tot);
	tot = unique(dc + 1, dc + 1 + tot) - dc - 1;
	ll sum = 0;

	for (int i = 1; i <= n; i++) {
		int t1 = lower_bound(dc + 1, dc + 1 + tot, lb[i]) - dc;
		int t2 = lower_bound(dc + 1, dc + 1 + tot, rb[i]) - dc;
		sum += rb[i] - lb[i];
		segtree.insert(1, 1, tot, t1, t2 - 1); //插入时右区间再-1
		cout << segtree.query(1, 1, tot, (sum + 1) / 2) << endl;
	}


	return 0;
}
