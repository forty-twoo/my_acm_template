#include<bits/stdc++.h>
#include <algorithm>
#define mst(a,x) memset(a,x,sizeof(a))
#define debug freopen("data.txt","r",stdin)
#define INF 0x3f3f3f3f
typedef long long ll;
using namespace std;
const int MAX = 1e5 + 10;
const ll MOD = 998244353;
char str[MAX];

//回文自动机模板
struct PalidromTree {
#define N 26
	int nxt[MAX][N]; //nxt指针与字典树类似，指向的串为当前串两端加同一个字符构成
	int fail[MAX]; //fail指针，失配后跳转到fail指针指向的节点
	int cnt[MAX]; //节点i代表的本质不同的串的个数(建树时求出的不是完全的，最后count()函数跑一遍后才是正确的
	int num[MAX]; //以节点i代表的最长回文串的最右端点为回文结尾的回文串种类个数
	int len[MAX]; //节点i表示的回文串的长度
	int S[MAX]; //存放添加的字符
	int id[MAX]; //节点i的回文串的最后一个元素的下一个
	int last; //指向上一个字符所在节点，方便下一次add
	int n; //字符数组指针
	int p; //节点指针

	int failTree[MAX], nxtTree[MAX];
	int vis[MAX];
	ll ans = 0;

	int newnode(int l) { //新建节点
		for (int i = 0; i < N; i++) nxt[p][i] = 0;
		cnt[p] = 0;
		num[p] = 0;
		len[p] = l;
		return p++;
	}
	void init() {
		p = 0;
		newnode(0); //插入偶根
		newnode(-1); //插入奇根
		last = 0;
		n = 0;
		S[n] = -1; //开头放一个字符集中没有的字符，减少特判
		fail[0] = 1; //偶根的fail指向奇根
	}
	int get_fail(int x) {
		while (S[n - len[x] - 1] != S[n]) x = fail[x];
		return x;
	}
	void add(int c) {
		c -= 'a';
		S[++n] = c;
		int cur = get_fail(last); //通过上一个回文串找这个回文串的匹配位置
		if (!nxt[cur][c]) {  //如果这个回文串没有出现过，说明出现了一个新的本质不同的回文串
			int now = newnode(len[cur] + 2);
			fail[now] = nxt[get_fail(fail[cur])][c]; //建立fail指针，失配后跳转
			nxt[cur][c] = now;
			num[now] = num[fail[now]] + 1;
		}
		last = nxt[cur][c];
		cnt[last]++;
		id[last] = n;
	}
	void count() {
		for (int i = p - 1; i >= 0; i--) {
			cnt[fail[i]] += cnt[i]; //fail树上父亲累加儿子的个数
		}
	}
	/****************user_define*******************/
}pam;

int main() {
	ios::sync_with_stdio(false);
	int ks, cks = 0;
	scanf("%d", &ks);
	while (ks--) {
		scanf("%s", str + 1);
		int len = strlen(str + 1);
		pam.init();
		for (int i = 1; i <= len; i++) {
			pam.add(str[i]);
		}
		printf("Case #%d: %lld\n", ++cks, pam.solve());

	}
	return 0;
}
