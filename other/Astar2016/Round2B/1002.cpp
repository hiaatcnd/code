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

const int maxn = 1000;
int n, m, recb[maxn], recc[maxn], a[maxn], b[maxn], c[maxn], N;
ll f[maxn], ans;

void work(ll A, ll B, ll &t1, ll &t2){
	memset(f, 127, sizeof(f));
	f[0] = 0;
	for(int i = 1; i <= n; ++i){
		ll val = b[i] * A + c[i] * B;
		for(int j = N; j >= a[i]; --j)
			if(f[j - a[i]] + val < f[j]){
				f[j] = f[j - a[i]] + val;
				recb[j] = recb[j - a[i]] + b[i];
				recc[j] = recc[j - a[i]] + c[i];
			}
	}
	int t = m;
	for(int i = m; i <= N; ++i)
		if(f[i] < f[t]) t = i;
	t1 = recb[t];
	t2 = recc[t];
	ans = min(ans, t1 * t2);
}

void solve(int t1, int t2, int t3, int t4){
	ll t5, t6;
	work(abs(t4 - t2), abs(t3 - t1), t5, t6);
	if((t5 == t1) && (t6 == t2) || (t5 == t3) && (t6 == t4)) return;
	solve(t1, t2, t5, t6);
	solve(t5, t6, t3, t4);
}

int main(){
#ifdef ONLINE_JUDGE
	freopen("b.in", "r", stdin);
	freopen("b.out", "w", stdout);
#endif
	while(~scanf("%d%d", &n, &m)){
		N = 0;
		for(int i = 1; i <= n; ++i) scanf("%d%d%d", a + i, b + i, c + i), N += a[i];
		ans = 1LL << 50;
		ll t1, t2, t3, t4;
		work(1, 0, t1, t2);
		work(0, 1, t3, t4);
		solve(t1, t2, t3, t4);
		cout << ans << endl;
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
