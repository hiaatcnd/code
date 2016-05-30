#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;
#define ll long long
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define FOR(i, l, r) for(int i = l; i <= r; i++)
#define ROF(i, r, l) for(int i = r; i >= l; i--)
#define all(a) a.begin(), a.end()

const int B = 1010000;
const int maxn = 10010;
int T, n, l[maxn], r[maxn], z[maxn], d[maxn];
int le[2 * B + 1], ri[2 * B + 1], letag[2 * B + 1], ritag[2 * B + 1];

int main(){
	scanf("%d", &T);
	for(int t = 1; t <= T; ++t){
		printf("Case #%d:\n", t);
		scanf("%d", &n);
		vector<int> q;
		for(int i = 1; i <= n; ++i){
			scanf("%d%d%d%d", l + i, r + i, z + i, d + i);
			l[i] += z[i], r[i] -= z[i];
			if(r[i] > l[i]) continue;
			if(d[i] == -1){
				if(letag[r[i] + B] == t) le[r[i] + B]++; else le[r[i] + B] = 1, letag[r[i] + B] = t;
				if(letag[l[i] + 1 + B] == t) le[l[i] + 1 + B]--; else le[l[i] + 1 + B] = -1, letag[l[i] + 1 + B] = t;

				if(ritag[r[i] + B] == t); else ri[r[i] + B] = 0, ritag[r[i] + B] = t;
				if(ritag[l[i] + 1 + B] == t); else ri[l[i] + 1 + B] = 0, ritag[l[i] + 1 + B] = t;
			}

			if(d[i] == 1){
				if(ritag[r[i] + B] == t) ri[r[i] + B]++; else ri[r[i] + B] = 1, ritag[r[i] + B] = t;
				if(ritag[l[i] + 1 + B] == t) ri[l[i] + 1 + B]--; else ri[l[i] + 1 + B] = -1, ritag[l[i] + 1 + B] = t;

				if(letag[r[i] + B] == t); else le[r[i] + B] = 0, letag[r[i] + B] = t;
				if(letag[l[i] + 1 + B] == t); else le[l[i] + 1 + B] = 0, letag[l[i] + 1 + B] = t;
			}
			q.pb(r[i] + B), q.pb(l[i] + 1 + B);
		}
		sort(all(q));
		q.resize(unique(all(q)) - q.begin());
		int now1 = 0, now2 = 0, tmax = 0, ans = 0;
		for(int i = 0; i < (int)q.size(); ++i){
			now1 += le[q[i]];
			now2 += ri[q[i]];
			tmax = max(tmax, now2);
			ans = max(now1 + tmax, ans);
		}
		printf("%d\n", ans);
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
