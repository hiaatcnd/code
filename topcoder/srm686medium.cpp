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

const int maxn = 100100, maxm = 310;

class CyclesNumber{
public:
	int s[maxm][maxm], f[maxn][maxm], fac[maxm];
	int mul(int a, int b) { a = (ll)a * b % M; return a; }
	int add(int a, int b) { a = a + b; if (a >= M) a -= M; return a; }
	void init(){
		s[0][0] = 1;
		for(int i = 1; i < maxm; i++)
			for(int j = 1; j <= i; j++)
				s[i][j] = add(mul(j, s[i - 1][j]), s[i - 1][j - 1]);
		f[0][0] = 1;
		for(int i = 1; i < maxn; i++)
			for(int j = 1; j < maxm; j++)
				f[i][j] = add(mul(i - 1, f[i - 1][j]), f[i - 1][j - 1]);
		fac[0] = 1;
		for(int i = 1; i < maxm; i++) fac[i] = mul(fac[i - 1], i);
	}
	int work(int n, int m){
		int res = 0;
		for(int i = 0; i <= m; i++)
			res = add(res, mul(mul(s[m][i], fac[i]), f[n + 1][i + 1]));
		return res;
	}
	vector<int> getExpectation(vector<int> n, vector<int> m) {
		init();
		vector<int> ans;
		int l = n.size();
		for(int i = 0; i < l; i++)
			ans.pb(work(n[i], m[i]));
		return ans;
	}
};
