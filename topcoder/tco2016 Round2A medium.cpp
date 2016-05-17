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

inline int add(int a, int b){
	return (a + b) % M;
}

inline int mul(int a, int b){
	return (ll)a * b % M;
}

class CliqueCuts{
public:
	int f[1 << 24];
	ll ed[45];
	int calc(ll s){
		if(!s) return 1;
		int t = 63 - __builtin_clzll(s);
		if(t < 24){
			if(f[s]) return f[s];
			else return f[s] = calc(s ^ (1LL << t)) + calc(s  & ed[t]);
		}else return calc(s ^ (1LL << t)) + calc(s & ed[t]);
	}

	int sum(int n, vector<int> a, vector<int> b, vector<int> c) {
		int m = a.size();
		ll V = (1LL << n) - 1;
		//for(int i = 0; i < n; i++) ed[i] |= 1 << i;
		for(int i = 0; i < m; ++i){
			ed[a[i]] |= 1LL << b[i];
			ed[b[i]] |= 1LL << a[i];
		}
		int ans = 0;
		for(int i = 0; i < m; ++i){
			int cnt = add(calc(ed[a[i]] & ed[b[i]]), M - calc(V ^ (1LL << a[i]) ^ (1LL << b[i])) + 1);
			ans = add(ans, mul(cnt, c[i]));
		}
		return ans;
	}
};
