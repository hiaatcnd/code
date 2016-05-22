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

int n;
int s[10010];
double a[10010];
int cnt[20010];

int main(){
#ifndef ONLINE_JUDGE
	freopen("f.in", "r", stdin);
	freopen("f.out", "w", stdout);
#endif
	while(~scanf("%d", &n)){
		for(int i = 1; i <= n; i++) cin >> a[i];
		for(int i = 1; i <= n; ++i){
			s[i] = 0;
			memset(cnt, 0, sizeof(cnt)); cnt[n]++;
			int ans = 1;
			for(int j = i + 1; j <= n; ++j){
				s[j] = s[j - 1] + (a[j] > a[i] ? 1 : -1);
				cnt[s[j] + n]++;
				if(s[j] == 0) ans++;
			}
			for(int j = i - 1; j >= 1; --j){
				s[j] = s[j + 1] + (a[j] > a[i] ? 1 : -1);
				ans += cnt[-s[j] + n];
			}
			printf("%d", ans);
			if(i < n) printf(" ");
		}
		printf("\n");
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
