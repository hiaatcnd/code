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

const int maxn = 1001000;
int fac[maxn], inv[maxn];

inline int mul(int a, int b) { return (ll)a * b % M; }

inline int pow(int a, int b){
	int ans = 1;
	for(; b; b >>= 1, a = mul(a, a))
		if(b & 1) ans = mul(ans, a);
	return ans;
}

int C(int n, int m){
	return mul(fac[n], mul(inv[m], inv[n - m]));
}

class PermutationCounts{
public:
	int countPermutations(int N, vector<int> pos) {
		fac[0] = 1;
		for(int i = 1; i <= N; ++i) fac[i] = mul(fac[i - 1], i);
		inv[N] = pow(fac[N], M - 2);
		for(int i = N - 1; i >= 0; --i) inv[i] = mul(inv[i + 1], i + 1);
		
		int K = pos.size() + 1;
		vector<int> a(K + 1);
		for(int i = 1; i < K; ++i) a[i] = pos[i - 1];
		a[K] = N;
		sort(all(a));
		vector<int> dp(K + 1);
		dp[0] = 1;
		for(int i = 1; i <= K; ++i)
			for(int j = 0; j < i; ++j){
				int tmp = mul(C(a[i], a[j]), dp[j]);
				if((i - j) & 1) (dp[i] += tmp) %= M;
				else (dp[i] += M - tmp) %= M;
			}
		return dp[K];
	}
};
