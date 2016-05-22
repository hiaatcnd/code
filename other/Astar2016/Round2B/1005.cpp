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

const int N = 100100;
int n, k, m, a[N], tr[N * 4], l[N], r[N];
vector<int> add[N], del[N];
ll s[N];

void modify(int t, int l, int r, int x, int v){
	if(l == r) { tr[t] += v; return; }
	int mid = (l + r) >> 1;
	if(x <= mid) modify(ls, l, mid, x, v);
	else modify(rs, mid + 1, r, x, v);
	tr[t] = tr[ls] + tr[rs];
}

int get(int t, int l, int r, int k){
	if(l == r) return l;
	int mid = (l + r) >> 1;
	if(tr[ls] >= k) return get(ls, l, mid, k);
	else return get(rs, mid + 1, r, k - tr[ls]);
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("e.in", "r", stdin);
	freopen("e.out", "w", stdout);
#endif
	while(~scanf("%d%d%d", &n, &k, &m)){
		memset(tr, 0, sizeof(tr));
		for(int i = 1; i <= n; ++i){
			scanf("%d", a + i);
			s[i] = s[i - 1] + a[i];
			add[i].clear();
			del[i].clear();
		}
		for(int i = 1; i <= m; ++i){
			scanf("%d%d", l + i, r + i);
			add[l[i]].pb(i);
			del[r[i]].pb(i);
		}
		int now = 0; ll ans = 0;
		for(int i = 1; i <= n; ++i){
			int len = add[i].size();
			for(int j = 0; j < len; ++j)
				modify(1, 1, n, i, 1), now++;
			if(now >= k){
				int t = get(1, 1, n, k);
				ans = max(ans, s[i] - s[t - 1]);
			}
			len = del[i].size();
			for(int j = 0; j < len; ++j)
				modify(1, 1, n, l[del[i][j]], -1), now--;
		}
		printf("%lld\n", ans);
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
