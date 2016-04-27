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

const int maxn = 110;

class EllysTree{
public:
	int n;
	bool vis[maxn], vi[maxn];
	int p[maxn], tot, size[maxn], si[maxn];
	vector<int> g[maxn];
	void dfs(int t){
		size[t] = 1;
		for(auto v : g[t]){
			dfs(v);
			size[t] += size[v];
		}
	}
	int DFS(int t){
		if(!vi[t] && si[t] == 1) return t;
		if(!si[t]) return 0;
		int k;
		for(auto v : g[t])
			if((k = DFS(v))) return k;
		return 0;
	}
	void check(int t){
		int v = 0;
		vi[t] = 1;
		tot++;
		for(int k = t; k; k = p[k]) si[k]--;
		if(!si[t]){
			v = p[t];
			while(vi[v] && v) v = p[v];
			if(v) check(v);
		}
		v = DFS(t);
		if (v) check(v);
	}
	bool Dfs(int t, int o){
		if(t == o) return 1;
		for(auto v : g[t])
			if(Dfs(v, o)) return 1;
		return 0;
	}
	bool posi(int t, int o){
		for(int v = t; v; v = p[v]) if(v == o) return 1;
		if(Dfs(t, o)) return 1;
		return 0;
	}
	vector<int> getMoves(vector<int> parent) {
		n = parent.size();
		memset(vis, 0, sizeof(vis));
		for(int i = 1; i <= n; i++) p[i] = parent[i - 1], g[p[i]].pb(i);
		dfs(0);
		tot = 0;
		memcpy(si, size, sizeof(size));
		check(0);
		if(tot <= n) return vector<int>();
		vector<int> ans; int last = 0;
		for(int i = 1; i <= n; i++)
			for(int j = 1; j <= n; j++){
				if(!vis[j] && posi(last, j)){
					memcpy(vi, vis, sizeof(vis));
					memcpy(si, size, sizeof(size));
					tot = 0;
					check(j);
					if(tot == n - i + 1){ 
						ans.pb(j); 
						vis[j] = 1;
						for(int k = j; k; k = p[k]) size[k]--;
						last = j;
						break; 
					}else vis[j] = 0;
				}
			}
		return ans;
	}
};
