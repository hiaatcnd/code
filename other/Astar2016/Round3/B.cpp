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

const int M = 1000000009;
int T, n, m, b, a[15][15], u, v;
int f[1 << 14][15], c[1 << 14], pow2[110];

inline int F(int x) { return x & -x; }
inline void add(int &a, int b) { a += b; if(a >= M) a -= M; }

int main(){
	scanf("%d", &T);
	pow2[0] = 1;
	for(int i = 1; i < 110; ++i) pow2[i] = pow2[i - 1] * 2 % M;

	for(int t = 1; t <= T; ++t){
		scanf("%d%d%d", &n, &m, &b);
		memset(a, 0, sizeof(a));
		for(int i = 1; i <= m; ++i){
			scanf("%d%d", &u, &v);
			u--, v--;
			a[u][v]++;
		}
		memset(f, 0, sizeof(f));
		
		for(int i = 1; i < 1 << n; ++i){
			int cnt = 0;
			for(int j = 0; j < n; ++j)
				if((i >> j) & 1)
					for(int k = 0; k < n; ++k)
						if((i >> k) & 1)
							cnt += a[j][k];
			f[i][1] = c[i] = pow2[cnt];
		}
		for(int i = 1; i < 1 << n; ++i){
			for(int j = i; j; j = (j - 1) & i)
				if(F(i) == F(j)) add(f[i][1], M - (ll)f[j][1] * c[i ^ j] % M);
		}
		
		int all = (1 << n) - 1;
		for(int j = 1; j < b; ++j)
			for(int i = 1; i < 1 << n; ++i)
				if(f[i][j]){
					int st = all ^ i;
					for(int k = st; k; k = (k - 1) & (st))
						if(F(k) < F(i))
							add(f[i | k][j + 1], (ll)f[i][j] * f[k][1] % M);
				}
		printf("Case #%d:\n%d\n", t, f[all][b]);
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
