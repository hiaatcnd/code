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

bool isp(int num){
	int li = sqrt(num + 0.1);
	for(int i = 2; i <= li; ++i) if(num % i == 0) return 0;
	return 1;
}

int pow(int a, int b){
	int ans = 1;
	for(; b; b >>= 1, a = (ll)a * a % M)
		if(b & 1) ans = (ll)ans * a % M;
	return ans;
}

int get(string s, int p){
	if(s.size() < p) return 0;
	int res = 1e9;
	for(int i = 0; i < p; ++i){
		string r = "";
		int x = 0;
		for(int j = i; j < s.size(); j += p){
			x += s[j] - '0';
			r += s[j];
		}
		res = min(res, x + get(r, p));
	}
	return res;
}

class PolynomialGCD{
public:
	int gcd(string s) {
		int n = s.size();
		int ans = 1;
		for(int i = 2; i <= n; ++i)
			if(isp(i))
				ans = (ll)ans * pow(i, get(s, i)) % M;
		return ans;
	}
};
