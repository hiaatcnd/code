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

int n, x0, x1, y;
ll ans;

struct Line{
	int x0, x1, y;
	Line() {}
	Line(int x0_, int x1_, int y_) : x0(x0_), x1(x1_), y(y_) {}
}l[2016];

ll ck(pair<int, int> a, pair<int, int> b){
	return (ll)a.fi * b.se - (ll)a.se * b.fi;
}

bool cmp(pair<pair<int, int>, int> a, pair<pair<int, int>, int> b){
	ll t = ck(a.fi, b.fi);
	return t == 0 ? a.se > b.se : t > 0;
}

vector<pair<pair<int, int>, int> > q;
void add(int x0, int x1, int y, int len){
	if(y < 0) x0 = -x0, x1 = -x1, y = -y;
	auto a0 = mkp(x0, y);
	auto a1 = mkp(x1, y);
	if(ck(a1, a0) > 0) swap(a0, a1);
	q.pb(mkp(a0, len));
	q.pb(mkp(a1, -len));
}

void work(int xx, int yy, int i){
	q.clear();
	for(int j = 1; j <= n; ++j)
		if(l[j].y != yy)
			add(l[j].x0 - xx, l[j].x1 - xx, l[j].y - yy, l[j].x1 - l[j].x0);
	sort(all(q), cmp);
	int m = q.size();
	ll now = l[i].x1 - l[i].x0;
	ans = max(ans, now);
	for(int j = 0; j < m; ++j){
		now += q[j].se;
		ans = max(now, ans);
	}
}

int main(){
	cin >> n;
	for(int i = 1; i <= n; ++i){
		cin >> x0 >> x1 >> y;
		if(x0 > x1) swap(x0, x1);
		l[i] = Line(x0, x1, y);
	}
	for(int i = 1; i <= n; ++i){
		work(l[i].x0, l[i].y, i);
		work(l[i].x1, l[i].y, i);
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
