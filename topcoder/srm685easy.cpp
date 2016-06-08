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

class MultiplicationTable2{
public:
	int f[60][60];
	vector<int> dfs(vector<int> g){
		sort(all(g));
		for(auto u : g)
			for(auto v : g){
				bool flag = 0;
				for(auto t : g)
					if(f[u][v] == t) flag = 1;
				if(!flag){
					g.pb(f[u][v]);
					return dfs(g);
				}
			}
		return g;
	}
	int minimalGoodSet(vector<int> table) {
		int n = sqrt(table.size() + 0.1);
		for(int i = 0; i < n; i++)
			for(int j = 0; j < n; j++)
				f[i][j] = table[i * n + j];
		int ans = n;
		for(int i = 0; i < n; i++){
			vector<int> g;
			g.pb(i);
			auto t = dfs(g);
			ans = min(ans, (int)t.size());
		}
		return ans;
	}
};
