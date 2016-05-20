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

ll y, l, ans;

void check(int m){
	for(int l = m; l < 1000; ++l){
		if(l < 100){
			int a = l / 10, b = l % 10;
			if((y - b) % a == 0) ans = max(ans, (y - b) / a);
		}else{
			ll a = l / 100, b = l / 10 % 10, c = l % 10;
			ll lt = 0, rt = 1000000001;
			while(lt + 1 < rt){
				ll d = (lt + rt) / 2;
				if(d * d * a + d * b + c <= y) lt = d;
				else rt = d;
			}
			if(lt * lt * a + lt * b + c == y) ans = max(ans, lt);
		}
	}
}

int main(){
	cin >> y >> l;
	if(l < 1000) check(l);
	for(int i = 1000000; i >= 10; i--){
		ll t = y, num = 0, b = 1; bool flag = 1;
		while(t){
			if(t % i > 9) { flag = 0; break; }
			num = num + t % i * b;
			b *= 10;
			t /= i;
		}
		if(!flag) continue;
		if(num < l) continue;
		ans = max(ans, (ll)i); break;
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
