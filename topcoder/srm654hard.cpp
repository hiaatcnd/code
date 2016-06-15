#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define FOR(i, l, r) for(int i = l; i <= r; i++)
#define ROF(i, r, l) for(int i = r; i >= l; i--)
#define all(a) a.begin(), a.end()
#define M 1000000007

class TwoEntrances{
public:
	int C[3010][3010], ans[3010][3010], f[3010], size[3010], fa[3010], sum[3010][3010];
	vector<int> g[3010];
	bool in_path[3010];

	void dfs(int t){
		for(auto v : g[t])
			if(v != fa[t]){
				fa[v] = t;
				dfs(v);
			}
	}
	inline int merge(int a, int b){
		return C[a + b][a];
	}
	void DP(int t){
		f[t] = 1; size[t] = 0;
		for(auto v : g[t])
			if(!in_path[v] && v != fa[t]){
				DP(v);
				f[t] = (ll)f[t] * f[v] % M * merge(size[t], size[v]) % M;
				size[t] += size[v];
			}
		size[t]++;
	}

	int solve(int l, int r, vector<int> &p){
		if(ans[l][r] != -1) return ans[l][r];
		if(l == r) return ans[l][r] = f[p[l]];
		return ans[l][r] = ((ll)merge(size[p[l]] - 1, sum[l + 1][r]) * f[p[l]] % M * solve(l + 1, r, p) % M + (ll)merge(size[p[r]] - 1, sum[l][r - 1]) * f[p[r]] % M * solve(l, r - 1, p) % M) % M;
	}

	int count(vector<int> a, vector<int> b, int s1, int s2) {
		int n = a.size();
		for(int i = 0; i <= n; ++i) g[i].clear();
		memset(in_path, 0, sizeof(in_path));
		memset(ans, -1, sizeof(ans));
		for(int i = 0; i <= 3000; C[i++][0] = 1)
			for(int j = 1; j <= i; ++j)
				C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % M;

		for(int i = 0; i < n; ++i)
			g[a[i]].pb(b[i]), g[b[i]].pb(a[i]);

		fa[s1] = -1;
		dfs(s1);
		
		vector<int> path;
		int t = s2;
		while(t >= 0){
			path.pb(t);
			in_path[t] = 1;
			t = fa[t];
		}
		
		for(auto v : path) DP(v);
		
		for(int i = 0; i < path.size(); ++i){
			sum[i][i] = size[path[i]];
			for(int j = i + 1; j < path.size(); ++j)
				sum[i][j] = sum[i][j - 1] + size[path[j]];
		}
		solve(0, path.size() - 1, path);
		return ans[0][path.size() - 1];
	}
};
