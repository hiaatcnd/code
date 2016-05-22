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
#define M 2 //M为矩阵大小

int T, x, k, c, P;
ll m;

struct matrix{
	int x[M][M];
	int *operator [] (int a) { return x[a]; }
}p, a, ans;
void inc(int &a, int b) { a += b; if (a >= P) a -= P; }
matrix operator * (matrix &a, matrix &b){
	memset(p.x, 0, sizeof(p.x));
	for(int i = 0; i < M; i++)
		for(int j = 0; j < M; j++)
			for(int k = 0; k < M; k++)
				inc(p[i][j], (ll)a[i][k] * b[k][j] % P);
	return p;
}

int main(){
	cin >> T;
	for(int t = 1; t <= T; ++t){
		cin >> x >> m >> k >> c; P = k;
		a[0][0] = 10, a[0][1] = 1, a[1][0] = 0, a[1][1] = 1;
		memset(ans.x, 0, sizeof(ans.x));
		ans[0][0] = ans[1][1] = 1;
		for(; m; m >>= 1, a = a * a)
			if(m & 1) ans = ans * a;
		printf("Case #%d:\n", t);
		if(x * ans[0][1] % k == c) printf("Yes\n");
		else printf("No\n");
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
