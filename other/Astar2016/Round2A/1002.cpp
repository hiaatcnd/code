//看看会不会爆int!
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

const int inf = 2e9;
int n, p[20], w[20], a[20], T;
int f[1 << 18][18];

int main(){
#ifndef ONLINE_JUDGE
	freopen("b.in", "r", stdin);
	freopen("b.out", "w", stdout);
#endif
	cin >> T;
	for(int t = 1; t <= T; ++t){
		memset(w, -1, sizeof(w));
		scanf("%d", &n);
		for(int i = 0; i < n; ++i){
			scanf("%d%d", a + i, p + i);
			w[p[i]] = i;
		}
		memset(f, 128, sizeof(f));
		for(int mask = 1; mask < (1 << n); ++mask){
			int cnt = 0;
			for(int i = 0; i < n; ++i) if(mask & (1 << i)) cnt++;
			if(w[cnt - 1] != -1){
				if (!(mask & (1 << w[cnt - 1]))) continue;
				if(cnt == 1) { f[mask][w[0]] = 0; continue; }
				for(int i = 0; i < n; ++i)
					if(f[mask ^ (1 << w[cnt - 1])][i] > -inf)
						f[mask][w[cnt - 1]] = max(f[mask ^ (1 << w[cnt - 1])][i] + a[i] * a[w[cnt - 1]], f[mask][w[cnt - 1]]);
			}else{
				for(int i = 0; i < n; ++i)
					if((mask & (1 << i)) && (p[i] == -1)){
						if(cnt == 1) { f[mask][i] = 0; break; }
						for(int j = 0; j < n; ++j)
							if(f[mask ^ (1 << i)][j] > -inf)
								f[mask][i] = max(f[mask ^ (1 << i)][j] + a[i] * a[j], f[mask][i]);
					}
			}
		}
		int ans = -2e9;
		for(int i = 0; i < n; ++i) ans = max(ans, f[(1 << n) - 1][i]);
		printf("Case #%d:\n", t);
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
