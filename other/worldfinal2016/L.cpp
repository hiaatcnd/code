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

pair<int, int> p[1001000];
vector<pair<int, int> >q;
int n;

int main(){
	cin >> n;
	for(int i = 1; i <= n; ++i)
		scanf("%d%d", &p[i].fi, &p[i].se);
	sort(p + 1, p + n + 1);
	ll now = 0, ans = 0;
	for(int i = 1; i <= n; ++i){
		if(p[i].fi <= p[i].se){
			if(p[i].fi > now){
				ans += p[i].fi - now;
				now = p[i].fi;
			}
			now += p[i].se - p[i].fi;
		}else q.pb(mkp(p[i].se, p[i].fi));
	}
	int m = q.size();
	sort(all(q));
	for(int j = m - 1; j >= 0; --j){
		if(now < q[j].se){
			ans += q[j].se - now;
			now = q[j].se;
		}
		now += q[j].fi - q[j].se;
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
