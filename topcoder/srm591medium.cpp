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

int gcd(int a, int b){
	return b ? gcd(b, a % b) : a;
}

class PyramidSequences{
public:
	long long distinctPairs(int N, int M) {
		ll n = 2 * N - 2, m = 2 * M - 2;
		ll g = gcd(n, m);
		ll l1 = (n / g - 1) / 2, l2 = (m / g - 1) / 2;
		ll m1 = n / g / 2, m2 = m / g / 2;
		ll ans = n / g * m;
		ans -= l1 * (m / g) + l2 * (n / g) - l1 * l2;
		ans -= m1 * (m / g) + m2 * (n / g) - m1 * m2;
		
		//ll k1 = N - 2 - l1 - m1, k2 * M - 2 - l2 - m2;
		//ll t1 = (n / g) & 1, t2 = (m / g) & 1;
		ans -= (g - 2) / 2 * (((n / g + 1) / 2) + n / g / 2) * (((m / g + 1) / 2) + m / g / 2);
		//ans -= (g - 2) / 2 * (n / g / 2) * (m / g / 2);
		return ans;
	}
};
