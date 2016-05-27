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

int pow(int a, int b){
	int ans = 1;
	for(; b; b >>= 1, a = (ll)a * a % M)
		if(b & 1) ans = (ll)ans * a % M;
	return ans;
}

int calc(int x){
	if(x <= 0) return 0;
	return ((ll)x * x % M * x % M - x + M) % M * pow(6, M - 2) % M;
}

int cal(int a, int b, int c){
	int res = calc(c);
	res = (res - calc(c - a) + M) % M;
	res = (res - calc(c - b) + M) % M;
	res = (res + calc(c - a - b)) % M;
	return res;
}

class TriangleTriples{
public:
	int count(int A, int B, int C) {
		ll res = (ll)A * B % M * C % M;
		res = (res - cal(A, B, C) + M) % M;
		res = (res - cal(A, C, B) + M) % M;
		res = (res - cal(B, C, A) + M) % M;
		return res;
	}
};
