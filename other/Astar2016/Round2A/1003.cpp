#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <set>
#include <queue>
#include <vector>
#include <iostream>
using namespace std;
#define ll long long
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define FOR(i, l, r) for(int i = l; i <= r; i++)
#define ROF(i, r, l) for(int i = r; i >= l; i--)
#define all(a) a.begin(), a.end()
#define ls (t << 1)
#define rs ((t << 1) | 1)

int T, n, m, v[100100], bg[100100], ed[100100], tot, x, y, ty;
ll w[100100], tr[400100], tag[400100];
vector<int> g[100100];

void dfs(int t, int fa, ll sum){
	bg[t] = ++tot;
	w[tot] = (sum += v[t]);
	int l = g[t].size();
	for(int i = 0; i < l; ++i)
		if(g[t][i] != fa)
			dfs(g[t][i], t, sum);
	ed[t] = tot;
}

void build(int t, int l, int r){
	if(l == r) { tr[t] = w[l]; return; }
	int mid = (l + r) >> 1;
	build(ls, l, mid);
	build(rs, mid + 1, r);
	tr[t] = max(tr[ls], tr[rs]);
}

inline void pushdown(int t){
	tr[ls] += tag[t], tr[rs] += tag[t];
	tag[ls] += tag[t], tag[rs] += tag[t];
	tag[t] = 0;
}

void modify(int t, int l, int r, int x, int y, int v){
	if(x <= l && y >= r){
		tr[t] += v;
		tag[t] += v;
		return;
	}
	pushdown(t);
	int mid = (l + r) >> 1;
	if(x <= mid) modify(ls, l, mid, x, y, v);
	if(y > mid) modify(rs, mid + 1, r, x, y, v);
	tr[t] = max(tr[ls], tr[rs]);
}

ll ask(int t, int l, int r, int x, int y){
	if(x <= l && y >= r) return tr[t];
	pushdown(t);
	int mid = (l + r) >> 1; ll ans;
	if(y <= mid) ans = ask(ls, l, mid, x, y);
	else if(x > mid) ans = ask(rs, mid + 1, r, x, y);
	else ans = max(ask(ls, l, mid, x, y), ask(rs, mid + 1, r, x, y));
	tr[t] = max(tr[ls], tr[rs]);
	return ans;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("c.in", "r", stdin);
	freopen("c.out", "w", stdout);
#endif
	cin >> T;
	for(int t = 1; t <= T; ++t){
		tot = 0;
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= n; ++i) g[i].clear();
		for(int i = 1; i < n; ++i){
			scanf("%d%d", &x, &y); ++x, ++y;
			g[x].pb(y); g[y].pb(x);
		}
		for(int i = 1; i <= n; ++i) scanf("%d", v + i);
		memset(tr, 0, sizeof(tr));
		memset(tag, 0, sizeof(tag));
		dfs(1, 0, 0);
		build(1, 1, n);
		printf("Case #%d:\n", t);
		while(m--){
			scanf("%d%d", &ty, &x); ++x;
			if(ty == 0){
				scanf("%d", &y);
				modify(1, 1, n, bg[x], ed[x], y - v[x]);
				v[x] = y;
			}else{
				printf("%lld\n", ask(1, 1, n, bg[x], ed[x]));
			}
		}
	}
  return 0;
}
/*
                   _ooOoo_
                  o8888888o
                  88" . "88
                  (| -_- |)
                  O\  =  /O
               ____/`---'\____
             .'  \\|     |//  `.
            /  \\|||  :  |||//  \
           /  _||||| -:- |||||-  \
           |   | \\\  -  /// |   |
           | \_|  ''\---/''  |   |
           \  .-\__  `-`  ___/-. /
         ___`. .'  /--.--\  `. . __
      ."" '<  `.___\_<|>_/___.'  >'"".
     | | :  `- \`.;`\ _ /`;.`/ - ` : | |
     \  \ `-.   \_ __\ /__ _/   .-` /  /
======`-.____`-.___\_____/___.-`____.-'======
                   `=---='
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
         佛祖保佑       永无BUG
*/
