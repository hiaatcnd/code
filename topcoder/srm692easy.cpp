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

class HardProof{
public:
	int n;
	int d[51][51];
	bool vis[51];

	void dfs(int t, int l, int r){
		vis[t] = 1;
		for(int j = 0; j < n; ++j)
			if(!vis[j] && d[t][j] >= l && d[t][j] <= r) dfs(j, l, r);
	}

	bool ok(int l, int r){
		for(int i = 0; i < n; ++i){
			memset(vis, 0, sizeof(vis));
			dfs(i, l, r);
			for(int j = 0; j < n; ++j) if(!vis[j]) return 0;
		}
		return 1;
	}

	int minimumCost(vector<int> D) {
		n = sqrt(D.size() + 0.5);
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < n; ++j)
				d[i][j] = D[i * n + j];
		sort(all(D));
		int ans = D[n * n - 1] - D[0], r = 0;
		for(auto v : D){
			while(!ok(v, D[r]) && r < n * n) ++r;
			if(r < n * n) ans = min(ans, D[r] - v);
		}
		return ans;
	}
};
