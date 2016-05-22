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

int n, a[100100];
ll ans[100100];

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in", "r", stdin);
	freopen("a.out", "w", stdout);
#endif
	while(~scanf("%d", &n)){
		memset(ans, 0, sizeof(ans));
		for(int i = 1; i <= n; ++i){
			scanf("%d", a + i);
		}
		for(int i = 1; i <= n; ++i){
			int l = i, r = i;
			while(l > 1 && a[l - 1] < a[i]){
				l--;
			}
			while(r < n && a[r + 1] <= a[i]){
				r++;
			}
			int tmin = a[i];
			for(int j = i, k = i; j >= l; --j){
				tmin = min(a[j], tmin);
				while(k <= r && a[k] >= tmin) k++;
				ans[k - j] = max(ans[k - j], (ll)tmin * a[i]);
			}
			tmin = a[i];
			for(int k = i, j = i; k <= r; ++k){
				tmin = min(a[k], tmin);
				while(j >= l && a[j] >= tmin) j--;
				ans[k - j] = max(ans[k - j], (ll)tmin * a[i]);
			}
		}
		for(int i = n - 1; i >= 1; --i) ans[i] = max(ans[i], ans[i + 1]);
		for(int i = 1; i <= n; ++i) printf("%lld\n", ans[i]);
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
