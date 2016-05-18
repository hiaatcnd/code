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

const double pi = acos(-1);
const int N = 17;
typedef complex<double> Comp;

Comp A[1 << N];
int rev[N][1 << N];

void FFT(Comp a[], int n, int o){
	int logn = __builtin_ctz(n);
	for(int i = 0; i < n; i++) A[rev[logn][i]] = a[i];
	for(int s = 0; s <= logn; ++s){
		int m = 1 << s;
		double ang = 2 * pi / m * o;
		Comp od = Comp(cos(ang), sin(ang));
		for(int k = 0; k < n; k += m){
			Comp w = Comp(1.0, 0);
			for(int j = 0; j < m / 2; ++j){
				Comp t = w * A[k + j + m / 2];
				A[k + j + m / 2] = A[k + j] - t;
				A[k + j] = A[k + j] + t;
				w = w * od;
			}
		}
	}
	for(int i = 0; i < n; ++i) a[i] = A[i];
}

int n;
vector<int> value;
vector<Comp> cache[N][N];
double dp[1 << N][N], g[1 << N][N];

void solve(int l, int r){
	if(l + 1 == r){
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < n; ++j)
				if(i != j) g[l][i] = max(g[l][i], dp[l][j]);
		return;
	}
	int m = (l + r) >> 1;
	solve(l, m);
	int tn = r - l;
	int tv = __builtin_ctz(tn) - 1;
	for(int i = 0; i < n; ++i){
		vector<Comp> tmp(tn);
		for(int j = l; j < m; ++j) tmp[j - l] = g[j][i] + value[i];
		FFT(tmp.data(), tn, 1);
		for(int j = 0; j < tn; ++j) tmp[j] *= cache[i][tv][j];
		FFT(tmp.data(), tn, -1);
		for(int j = m; j < r; ++j)
			dp[j][i] += tmp[j - l].real() / tn;
	}
	solve(m, r);
}

class VendingMachines{
public:
	double expectedValue(int tickets, vector<int> luck, vector<int> value_) {
		value = value_;
		n = luck.size();
		int m = 0; while(1 << m <= tickets) ++m;
		for(int j = 0; j <= m; ++j)
			for(int i = 0; i < (1 << j); ++i)
				rev[j][i] = (rev[j][i >> 1] >> 1) + ((i & 1) << (j - 1));
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < m; ++j){
				vector<Comp> tmp(1 << j + 1);
				double p = 1;
				for(int k = 1; k < 1 << j + 1; ++k){
					double pp =  1. * k * k / luck[i] / luck[i];
					tmp[k] = p * pp;
					p *= 1 - pp;
				}
				FFT(tmp.data(), 1 << j + 1, 1);
				cache[i][j] = tmp;
			}
		memset(dp, 0, sizeof(dp));
		memset(g, 0, sizeof(g));
		solve(0, 1 << m);
		double ans = 0;
		for(int i = 0; i < n; ++i)
			ans = max(ans, dp[tickets][i]);
		return ans;
	}
};
