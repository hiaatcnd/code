#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
#define all(x) a.begin(), a.end()

const int maxn = 400100;
int n, m;
int u[maxn], v[maxn];
int dfn[maxn], low[maxn], tim;
vector<int> g[maxn];
set<int> f[maxn];

void dfs(int t, int fa){
	dfn[t] = low[t] = ++tim;
	for(auto v : g[t])
		if(v != fa){
			if(!dfn[v]){
				dfs(v, t);
				low[t] = min(low[t], low[v]);
			}else low[t] = min(low[t], dfn[v]);
		}
}

void DFS(int t){
	for(auto v : g[t]) f[v].erase(t), DFS(v);
}

int main(){
	freopen("x.in", "r", stdin);
	freopen("x.out", "w", stdout);
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; ++i){
		scanf("%d%d", &u[i], &v[i]);
		g[u].pb(v[i]);
		g[v].pb(u[i]);
	}
	dfs(1, 0);
	for(int i = 1; i <= m; ++i){
		int x = low[u[i]], y = low[v[i]];
		f[x].insert(y);
		f[y].insert(x);
	}
	for(int i = 1; i <= n; ++i)	cnt[low[i]]++;
	int k = low[1];
	for(int i = 1; i <= n; ++i)
		if(cnt[low[i]] > cnt[k]) k = low[i];
	DFS(k);
	
	return 0;
}
