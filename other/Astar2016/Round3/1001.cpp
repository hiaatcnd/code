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

const int maxn = 40;
int T, n, m, L, R, a[maxn], b[maxn];
int dp[maxn][maxn], step[maxn][maxn], f[maxn][maxn], g[maxn][maxn];
bool ok[maxn][maxn];

void solve(int l, int r){
	memset(f, 0, sizeof(f));
	memset(g, 127, sizeof(g));
	for(int i = l + 1; i <= r; ++i)
		if(ok[l][i] && dp[l + 1][i - 1] == i - l - 1)
			f[i][2] = 1, g[i][2] = 1 + step[l + 1][i - 1];
	
	for(int i = l + 2; i <= r; ++i)
		for(int j = 3; j <= i - l + 1; ++j)
			for(int k = l + j - 2; k < i; ++k)
				if(f[k][j - 1] && dp[k + 1][i - 1] == i - k - 1 && (ll)(j - 2) * (a[i] - a[k]) == a[k] - a[l]){
					f[i][j] = 1;
					g[i][j] = min(g[i][j], g[k][j - 1] + step[k + 1][i - 1]);
				}

	for(int i = L; i <= R; ++i)
		if(f[r][i]){
			if(dp[l][r] < r - l + 1){
				dp[l][r] = r - l + 1;
				step[l][r] = g[r][i];
			}else step[l][r] = min(step[l][r], g[r][i]);
		}
}

int main(){
	scanf("%d", &T);
	for(int t = 1; t <= T; ++t){
		scanf("%d%d%d%d", &n, &m, &L, &R);
		for(int i = 1; i <= n; ++i) scanf("%d", a + i);
		for(int i = 1; i <= m; ++i) scanf("%d", b + i);
		memset(ok, 0, sizeof(ok));
		for(int i = 1; i < n; ++i)
			for(int j = i + 1; j <= n; ++j)
				for(int k = 1; k <= m; ++k)
					if(a[j] - a[i] == b[k]) ok[i][j] = 1;
		
		memset(dp, 0, sizeof(dp));
		memset(step, 0, sizeof(step));
		for(int len = 2; len <= n; ++len)
			for(int l = 1; l + len - 1 <= n; ++l){
				int r = l + len - 1;
				for(int k = l; k < r; ++k)
					if(dp[l][r] < dp[l][k] + dp[k + 1][r]){
						dp[l][r] = dp[l][k] + dp[k + 1][r];
						step[l][r] = step[l][k] + step[k + 1][r];
					}else if(dp[l][r] == dp[l][k] + dp[k + 1][r])
						step[l][r] = min(step[l][r], step[l][k] + step[k + 1][r]);
				
				solve(l, r);
			}
		printf("Case #%d:\n", t);
		printf("%d %d\n", dp[1][n], step[1][n]);
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
