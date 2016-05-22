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

int n, m, a[333], d[333], T, x;
bool ok[333][333];
int f[333][333];

int dp(int l, int r){
	if(l > r) return 0;
	if(f[l][r] != -1) return f[l][r];
	if(l == r) return f[l][r] = 1;
	if(ok[l][r] && !dp(l + 1, r - 1)) return f[l][r] = 0;
	for(int i = l + 1; i < r; ++i)
		if(ok[l][i] && ok[i][r] && a[i] - a[l] == a[r] - a[i] && !dp(l + 1, i - 1) && !dp(i + 1, r - 1)) return f[l][r] = 0;
	f[l][r] = r - l + 1;
	for(int i = l; i < r; ++i)
		f[l][r] = min(dp(l, i) + dp(i + 1, r), f[l][r]);
	return f[l][r];
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("d.in", "r", stdin);
	freopen("d.out", "w", stdout);
#endif
	cin >> T;
	while(T--){
		scanf("%d%d", &n, &m);
		memset(f, -1, sizeof(f));
		for(int i = 1; i <= n; ++i) scanf("%d", a + i);
		for(int j = 1; j <= m; ++j) scanf("%d", d + j);
		sort(d + 1, d + m + 1);
		for(int i = 1; i < n; ++i)
			for(int j = i + 1; j <= n; ++j){
				int t = lower_bound(d + 1, d + m + 1, a[j] - a[i]) - d;
				if(t >= 1 && t <= m && d[t] == a[j] - a[i]) ok[i][j] = 1;
				else ok[i][j] = 0;
			}
		printf("%d\n", n - dp(1, n));
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
