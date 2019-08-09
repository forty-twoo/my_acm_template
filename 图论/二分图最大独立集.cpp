//二分图最大独立集=n-二分图最小点覆盖(最大匹配数)
struct BI_MAX_Inde_Set {
	int col[MAX], match[MAX], vis[MAX], cnt = 0;

	//染色
	void get_color(int x, int c) {
		col[x] = c;
		for (auto y : G[x]) {
			if (!col[y]) get_color(y, 3 - c);
		}
	}
	//匹配
	bool dfs(int x) {
		vis[x] = 1;
		for (auto y : G[x]) {
			if (vis[y]) continue;
			vis[y] = 1;
			if (!match[y] || dfs(match[y])) {
				match[y] = x;
				match[x] = y;
				return true;
			}
		}
		return false;
	}
	//找最大匹配
	void bin_match() {
		for (int i = 1; i <= n; i++) {
			mst(vis, 0);
			if (col[i] == 1 && dfs(i)) cnt++;
		}
	}
	void max_ind_set() {
		cout << n - cnt << endl;
		mst(vis, 0);
		for (int i = 1; i <= n; i++) {
			if (col[i] == 1 && !match[i])
				dfs(i);
		}

		for (int i = 1; i <= n; i++) {
			if (col[i] == 1 && vis[i]) cout << a[i] << " ";
			if (col[i] == 2 && !vis[i]) cout << a[i] << " ";
		}
		cout << endl;

	}

	void solve() {
		for (int i = 1; i <= n; i++)
			if (!col[i]) get_color(i, 1);
		bin_match();
		max_ind_set();
	}
}MIS;
