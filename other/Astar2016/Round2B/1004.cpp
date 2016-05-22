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

int n, m, l[1000100], r[1000100];

bool check(int d){
	int t1 = -1e9, t2 = -1e9, t3 = -1e9, t4 = -1e9;
	for(int i = 1; i <= m; ++i){
		if(abs(r[i] - l[i]) <= d) continue;
		if(l[i] > r[i]) swap(l[i], r[i]);
		t1 = max(t1, l[i] + r[i]);
		t2 = max(t2, l[i] - r[i]);
		t3 = max(t3, -l[i] + r[i]);
		t4 = max(t4, -l[i] - r[i]);
		if(l[i] + r[i] + t4 > 2 * d) return 0;
		if(l[i] - r[i] + t3 > 2 * d) return 0;
		if(-l[i] + r[i] + t2 > 2 * d) return 0;
		if(-l[i] - r[i] + t1 > 2 * d) return 0;
	}
	return 1;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("d.in", "r", stdin);
	freopen("d.out", "w", stdout);
#endif
	while(~scanf("%d%d", &n, &m)){
		for(int i = 1; i <= m; ++i) scanf("%d%d", l + i, r + i);
		int tl = 0, tr = n;
		while(tl + 1 < tr){
			int d = (tl + tr) >> 1;
			if(check(d)) tr = d;
			else tl = d;
		}
		if(check(0)) tr = 0;
		printf("%d\n", tr);
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
