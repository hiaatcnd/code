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

int T, n, m, l, tot;
bool f[10010][11];
int tr[100100 * 30][2], cnt[100100 * 30], rt[11], a[10010], s[10010];

bool find(int rt, int val, int d, int dp){
	if(!rt) return 0;
	if(dp < 0) return 1;
	if(!((d >> dp) & 1)){
		if(tr[rt][!((val >> dp) & 1)]) return 1;
		else return find(tr[rt][(val >> dp) & 1], val, d, dp - 1);
	}else{
		return find(tr[rt][!((val >> dp) & 1)], val, d, dp - 1);
	}
}

int insert(int rt, int val, int dp){
	if(!rt) rt = ++tot, tr[rt][0] = tr[rt][1] = 0, cnt[rt] = 0;
	cnt[rt]++;
	if(dp < 0) return rt;
	tr[rt][(val >> dp) & 1] = insert(tr[rt][(val >> dp) & 1], val, dp - 1);
	return rt;
}

int del(int rt, int val, int dp){
	cnt[rt]--;
	if(dp < 0) return cnt[rt] ? rt : 0;
	tr[rt][(val >> dp) & 1] = del(tr[rt][(val >> dp) & 1], val, dp - 1);
	return cnt[rt] ? rt : 0;
}

bool check(int d){
	memset(f, 0, sizeof(f));
	f[0][0] = 1;
	memset(rt, 0, sizeof(rt));
	tot = 0;
	rt[0] = insert(rt[0], 0, 29);
	for(int i = 1; i <= n; ++i){
		for(int j = m; j >= 1; --j){
			f[i][j] = find(rt[j - 1], s[i], d, 29);
			if(f[i][j]) rt[j] = insert(rt[j], s[i], 29);
		}
		if(i >= l){
			for(int j = 0; j <= m; ++j)
				if(f[i - l][j]) rt[j] = del(rt[j], s[i - l], 29);
		}
	}
	return f[n][m];
}

int main(){
	scanf("%d", &T);
	for(int t = 1; t <= T; ++t){
		printf("Case #%d:\n", t);
		scanf("%d%d%d", &n, &m, &l);
		for(int i = 1; i <= n; ++i){
			scanf("%d", a + i), s[i] = s[i - 1] ^ a[i];
		}
		int l = 0, r = (1 << 30) - 1;
		while(l + 1 < r){
			int d = (l + r) >> 1;
			if(check(d)) l = d;
			else r = d;
		}
		printf("%d\n", l);
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
