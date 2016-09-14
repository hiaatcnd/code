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

double eps = 1e-8;
int n, m, tot;
vector<int> g[30];
int to[500], id[30][30];
bool ok[500];
double ans[500], a[500][500];

void gauss(int n){
	int lt = 1;
	for(int i = 1; i <= n; ++i){
		int k = lt;
		for(int j = lt; j <= n; ++j)
			if(fabs(a[j][i]) > fabs(a[k][i])) k = j;
		if(fabs(a[k][i]) < eps) continue;
		if(k != lt)
			for(int j = i; j <= n + 1; ++j) swap(a[lt][j], a[k][j]);
		to[lt++] = i; ok[i] = 1;
		for(int j = lt; j <= n; ++j){
			double t = a[j][i] / a[lt - 1][i];
			for(int k = i; k <= n + 1; ++k)
				a[j][k] -= a[lt - 1][k] * t;
		}
	}lt--;
	for(int i = lt; i; --i){
		for(int j = to[i] + 1; j <= n; ++j)
			if(fabs(a[i][j]) > eps){
				if(ok[j]) a[i][n + 1] -= a[i][j] * ans[j];
				else ok[to[i]] = 0;
			}
		if(ok[to[i]])
			ans[to[i]] = a[i][n + 1] / a[i][to[i]];
	}
}

int main(){
	scanf("%d%d", &n, &m);
	int u, v;
	for(int i = 1; i <= m; ++i){
		scanf("%d%d", &u, &v);
		u++, v++;
		g[u].pb(v);
		g[v].pb(u);
	}
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= n; ++j)
			if(g[i].size() && g[j].size())
				if(i != j) id[i][j] = ++tot;
	
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= n; ++j)
			if(i != j && g[i].size() && g[j].size()){
				int t = id[i][j];
				double tmp = 1. / g[i].size() / g[j].size();
				a[t][t] = 1;
				a[t][tot + 1] = 1;
				for(auto&& u : g[i])
					for(auto&& v : g[j])
						if(u != v)
							a[t][id[u][v]] -= tmp;
			}
	
	gauss(tot);
	scanf("%d%d", &u, &v); u++, v++;
	if(u == v) printf("0\n");
	else if(!id[u][v] || !ok[id[u][v]]) printf("never meet\n");
	else printf("%.6f\n", ans[id[u][v]]);
  return 0;
}
