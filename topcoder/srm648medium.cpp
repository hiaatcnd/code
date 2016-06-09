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

const int M = 1e9 + 7;

ll ksm(ll a, ll b){
	ll ans = 1;
	for(; b; b >>= 1, a = a * a % M)
		if(b & 1) ans = ans * a % M;
	return ans;
}

ll f(ll x, ll K){
	ll s = 0;
	while(x) s += min(x, K), x /= 2;
	return s;
}

class KitayutaMart{
public:
	int lastPrice(int N, int K) {
		int x = f(K, K), pr = 0;
		if(N >= x){
			pr = (N - x) / K;
			N -= pr * K;
		}
		int l = 0, r = 2 * K;
		while(l + 1 < r){
			int d = l + (r - l) / 2;
			if(f(d, K) >= N) r = d; else l = d;
		}
		return r * ksm(2, pr) % M;
	}
};
