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

const ll oo = 1LL << 61;

class MaliciousPath{
public:
	ll d[1010], m[1010];
	bool vis[1010];
	vector<int> f[1010], g[1010];

	long long minPath(int N, int K, vector<int> from, vector<int> to, vector<int> cost) {
		for(int i = 0; i < N; ++i) f[i].clear(), g[i].clear();
		int M = from.size();
		for(int i = 0; i < M; ++ i){
			f[from[i]].pb(i);
			g[to[i]].pb(i);
		}
		memset(d, 128, sizeof(d));
		memset(m, 0, sizeof(m));
		for(int j = 0; j <= K; ++j){
			for(int i = 0; i < N; ++i)
				for(auto e : f[i]){
					int v = to[e], c = cost[e];
					m[i] = max(m[i], c + d[v]);
				}
			memset(d, 127, sizeof(d));
			memset(vis, 0, sizeof(vis));
			d[N - 1] = 0;
			priority_queue<pair<ll, int> > q;
			q.push(mkp(0, N - 1));
			while(!q.empty()){
				auto p = q.top(); q.pop();
				int u = p.se;
				if(vis[u]) continue;
				vis[u] = 1;
				for(auto e : g[u]){
					int v = from[e], c = cost[e];
					ll dd = max(m[v], d[u] + c);
					if(dd < d[v]){
						d[v] = dd;
						q.push(mkp(-d[v], v));
					}
				}
			}
		}
		return d[0] >= oo ? -1 : d[0];
	}
};
