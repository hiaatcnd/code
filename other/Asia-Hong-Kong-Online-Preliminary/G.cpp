//看看会不会爆int!
#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define FOR(i, l, r) for(int i = l; i <= r; i++)
#define ROF(i, r, l) for(int i = r; i >= l; i--)
#define all(a) a.begin(), a.end()
inline int ckmax(int &a, int b) { return a < b ? a = b, 1 : 0; }
inline int ckmin(int &a, int b) { return a > b ? a = b, 1 : 0; }
#define clean(a) memset(a, 0, sizeof(a))
typedef long long ll;

const int maxn = 50010;
int n, m, k, M, col[maxn];
bool vis[maxn], mark[maxn];
vector<int> g[maxn], son[maxn], sp[maxn];
ll f[maxn][8], ans;
vector<int> order, spe;

void dfs(int t, int fa){
	order.pb(t);
	vis[t] = 1;
	for(auto v : g[t])
		if(v != fa){
			if(vis[v]){
				if(!mark[v] && !mark[t]){
					mark[t] = 1;
					spe.pb(t);
					sp[v].pb(t);
				}
			}else{
				dfs(v, t);
				son[t].pb(v);
			}
		}
}

void DFS(int t, int m){
	if(t >= spe.size()){
		if(k < m) return;

		for(auto u : order){
			memset(f[u], 0, sizeof(f[u]));
			if(mark[u]) f[u][col[u]] = 1;
			else for(int i = 0; i <= m; ++i) f[u][i] = 1;
			for(auto v : g[u])
				if(mark[v]) f[u][col[v]] = 0;
			
			for(auto v : son[u]){
				ll sum = f[v][m] * (k - m) % M;
				for(int i = 0; i < m; ++i) sum += f[v][i];
				sum %= M;
				for(int i = 0; i <= m; ++i)
					f[u][i] = f[u][i] * (sum - f[v][i] + M) % M;
			}
		}

		ll base = 1, sum = 0; int u = *order.rbegin();
		for(int i = 0; i < m; ++i) base = base * (k - i) % M;
		for(int i = 0; i < m; ++i) sum += f[u][i];
		sum = (sum + f[u][m] * (k - m)) % M;
		ans = (ans + base * sum) % M;
		return;
	}
	for(int i = 0; i <= m; ++i){
		col[spe[t]] = i;
		DFS(t + 1, max(m, col[spe[t]] + 1));
	}
}

int main(){
	scanf("%d%d%d%d", &n, &m, &k, &M);
	for(int i = 1; i <= m; ++i){
		int u, v;
		scanf("%d%d", &u, &v);
		g[u].pb(v);
		g[v].pb(u);
	}
	ll res = 1;
	for(int i = 1; i <= n; ++i)
		if(!vis[i]){
			order.clear();
			spe.clear();
			ans = 0;
			dfs(i, 0);

			reverse(all(order));
			DFS(0, 0);
			res = res * ans % M;
		}
	printf("%lld\n", res);
  return 0;
}
