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
#define M 1000000007

const int maxn = 1000100;

class WolfHockeyTeamHard{
public:
	ll fac[maxn], inv[maxn];
	
	ll mul(ll a, ll b) { return a * b % M; }
	ll add(ll a, ll b) { return (a + b) % M; }

	ll pow(ll a, ll b){
		ll ans = 1;
		for(; b; b >>= 1, a = mul(a, a))
			if(b & 1) ans = mul(ans, a);
		return ans;
	}

	void init(int n){
		fac[0] = 1;
		for(int i = 1; i <= n; i++) fac[i] = mul(fac[i - 1], i);
		inv[n] = pow(fac[n], M - 2);
		for(int i = n - 1; i >= 0; i--) inv[i] = mul(inv[i + 1], i + 1);
	}

	ll C(ll a, ll b){
		return mul(fac[a], mul(inv[b], inv[a - b]));
	}

	ll f(ll n, ll i){
		if(!i) return 1;
		return add(C(n - 1 + i, i), M - C(n - 1 + i, i - 1));
	}

	int count(int n, int k) {
		init(2 * n);
		ll ans = 0;
		for(int i = 0; i < n; i++){
			int v = i + n - 1;
			int cnt = (2 * n - 1) - max(k, v);
			ans = add(ans, mul(f(n, i), cnt));
		}
		return (int)mul(ans, mul(fac[n], 2));
	}
};
