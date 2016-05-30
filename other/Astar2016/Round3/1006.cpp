#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <set>
#include <queue>
#include <vector>
#include <iostream>
#include <map>
using namespace std;
#define ll long long
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define FOR(i, l, r) for(int i = l; i <= r; i++)
#define ROF(i, r, l) for(int i = r; i >= l; i--)
#define all(a) a.begin(), a.end()

const int maxn = 5000000;
bool nop[maxn + 10];
int pri[maxn], mu[maxn + 10], tot;
ll a, b, s[maxn];
map<ll, ll> mp;
int t, d; ll k;

void pre(){
	mu[1] = 1;
	ll ta;
	for(int i = 2; i <= maxn; ++i){
		if(!nop[i]) pri[++tot] = i, mu[i] = -1;
		for(int j = 1; j <= tot && (ta = (ll)i * pri[j]) <= maxn; ++j){
			nop[ta] = 1;
			if(i % pri[j]) mu[ta] -= mu[i]; else{
				mu[ta] = 0;
				break;
			}
		}
	}
	for(int i = 1; i <= maxn; ++i) s[i] = s[i - 1] + mu[i];
}

inline ll get_mu(ll n){
	if(n <= maxn) return s[n];
	if(mp.count(n)) return mp[n];
	ll ans = 1;
	for(ll i = 2, j; i <= n; i = j + 1){
		j = min(n, n / (n / i));
		ans -= get_mu(n / i) * (j - i + 1);
	}
	return mp[n] = ans;
}

inline ll get_mu_sqr(ll n){
	ll res = 0;
	for(ll i = 1; i * i <= n; ++ i) res += mu[i] * (n / i / i);
	return res;
}

inline ll cnt(ll n, int d){
	ll t0 = get_mu(n), t1 = get_mu_sqr(n);
	if(d == 1) return (t0 + t1) >> 1;
	if(d == -1) return (t1 - t0) >> 1;
	return n - t1;
}

int main(){
	pre();
	scanf("%d", &t);
	while(t--){
		scanf("%d%lld", &d, &k);
		ll l = 0, r = 1e10;
		ll numl = 0, numr = cnt(r, d);
		while(l + 1 < r){
			ll m = double(k - numl) / (numr - numl) * (r - l) + l;
			m = max(m, l + 1); m = min(m, r - 1);
			ll nump = cnt(m, d);
			if(nump >= k) r = m, numr = nump;
			else l = m, numl = nump;
		}
		printf("%lld\n", r);
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
