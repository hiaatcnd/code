//看看会不会爆int!
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
inline int ckmax(int &a, int b) { return a < b ? a = b, 1 : 0; }
inline int ckmin(int &a, int b) { return a > b ? a = b, 1 : 0; }
#define clean(a) memset(a, 0, sizeof(a))

const int maxn = 200100;
int n, Q, M, tot;
int p[maxn], size[maxn], bg[maxn], ed[maxn], a[25];
vector<int> g[maxn];

void dfs(int t){
	bg[t] = ++tot;
	size[t] = 1;
	for(auto v : g[t])
		dfs(v), size[t] += size[v];
	ed[t] = tot;
}

bool cmp(int x, int y){
	return bg[x] < bg[y];
}

int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i){
		scanf("%d", p + i);
		g[p[i]].pb(i);
	}
	dfs(0);

	scanf("%d", &Q);
	while(Q--){
		scanf("%d", &M);
		for(int i = 1; i <= M; ++i) scanf("%d", a + i);
		sort(a + 1, a + M + 1, cmp);
		int now = 0, ans = 0;
		for(int i = 1; i <= M; ++i)
			if(bg[a[i]] > now) ans += size[a[i]], now = ed[a[i]];
		printf("%d\n", ans);
	}
  return 0;
}
