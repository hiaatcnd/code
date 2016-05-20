//看看会不会爆int!
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define FOR(i, l, r) for(int i = l; i <= r; i++)
#define ROF(i, r, l) for(int i = r; i >= l; i--)
#define all(a) a.begin(), a.end()

int ls[100][30], rs[100][30];
int a[100][30], n, k;

void work(int x){
	for(int i = 2; i <= k; i++){
		int t = 1, fa;
		while(t){
			if(a[x][i] > a[x][t]) fa = t, t = rs[x][t];
			else fa = t, t = ls[x][t];
		}
		if(a[x][i] < a[x][fa]) ls[x][fa] = i;
		else rs[x][fa] = i;	
	}
}

bool dfs(int t1, int t2, int x, int y){
	if(!t1 && !t2) return 1;
	if((t1 > 0) ^ (t2 > 0)) return 0;
	if(!dfs(ls[x][t1], ls[y][t2], x, y)) return 0;
	if(!dfs(rs[x][t1], rs[y][t2], x, y)) return 0;
	return 1;
}

bool cmp(int x, int y){
	if(dfs(1, 1, x, y)) return 1;
	else return 0;
}

int main(){
	cin >> n >> k;
	int ans = 0;
	for(int i = 1; i <= n; ++i){
		for(int j = 1; j <= k; ++j){
			cin >> a[i][j];
		}
		work(i);
		bool flag = 1;
		for(int k = 1; k < i; ++k)
			if(cmp(i, k)) { flag = 0; break; }
		ans += flag;
	}
	cout << ans;
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
