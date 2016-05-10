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

const int maxn = 100100;

class TreeWalker{
public:
	int a[maxn], ni, sum, f[maxn];
	vector<int> g[maxn];
	
	int pow(int a, int b){
		int ans = 1;
		for(; b; b >>= 1, a = (ll)a * a % M)
			if(b & 1) ans = (ll)ans * a % M;
		return ans;
	}

	void dfs(int t){
		f[t] = 1;
		for(int v : g[t]){
			dfs(v);
			(sum += (ll)f[t] * f[v] % M) %= M;
			(f[t] += (ll)f[v] * ni % M) %= M;
		}
	}
	int calc(int N, int A0, int B, int C, int MOD) {
		a[0] = A0;
		for(int i = 1; i <= N - 2; i++) a[i] = ((ll)B * a[i - 1] + C) % MOD;
		for(int i = 1; i <= N - 1; i++){
			int j = a[i - 1] % i;
			g[j].pb(i);
		}
		ni = pow(2, M - 2);
		dfs(0);
		sum = (ll)sum * pow(2, N - 1) % M;
		return sum;
	}
};
