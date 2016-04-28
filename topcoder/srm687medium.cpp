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

class AllGraphCuts{
public:
	int n, cut[50][50];
	vector<int> ans;
	void dfs(vector<int> v){
		if(v.size() < 2) return;
		int x = -1, y = -1;
		for(auto a : v)
			for(auto b : v)
				if(x == -1 || cut[a][b] < cut[x][y]) x = a, y = b;
		ans.pb(cut[x][y] * n * n + x * n + y);
		vector<int> lh, rh; lh.pb(x), rh.pb(y);
		for(auto a : v)
			if(a != x && a != y){
				if(cut[a][x] > cut[a][y]) lh.pb(a);
				else rh.pb(a);
			}
		dfs(lh);
		dfs(rh);
	}
	vector<int> findGraph(vector<int> x) {
		n = sqrt(x.size() + 0.5);
		for(int i = 0; i < n; i++)
			for(int j = 0; j < n; j++)
				cut[i][j] = x[i * n + j];
		for(int i = 0; i < n; i++){
			if(cut[i][i] != 0) return vector<int>(1, -1); cut[i][i] = 1e6;
			for(int j = 0; j < n; j++)
				if(cut[i][j] != cut[j][i]) return vector<int>(1, -1);
		}
		for(int k = 0; k < n; k++)
			for(int i = 0; i < n; i++)
				for(int j = 0; j < n; j++)
					if(min(cut[i][k], cut[k][j]) > cut[i][j]) return vector<int>(1, -1);
		vector<int> v; for(int i = 0; i < n; i++) v.pb(i);
		dfs(v);
		return ans;
	}
};
