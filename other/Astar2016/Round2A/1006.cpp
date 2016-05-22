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

int T, a, b, ru[100100], n, m;
vector<int> g[100100];

int main(){
#ifndef ONLINE_JUDGE
	freopen("f.in", "r", stdin);
	freopen("f.out", "w", stdout);
#endif
	cin >> T;
	while(T--){
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= n; ++i) g[i].clear(), ru[i] = 0;
		for(int i = 1; i <= m; ++i){
			scanf("%d%d", &a, &b);
			g[a].pb(b);
			ru[b]++;
		}
		priority_queue<int> q;
		for(int i = 1; i <= n; ++i)
			if(!ru[i]) q.push(i);
		int tmin = 1e9; ll ans = 0;
		for(int i = 1; i <= n; ++i){
			int t = q.top();
			q.pop();
			tmin = min(tmin, t);
			ans += tmin;
			int l = g[t].size();
			for(int i = 0; i < l; ++i)
				if(!(--ru[g[t][i]])) q.push(g[t][i]);	
		}
		cout << ans << '\n';
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
