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
inline int ckmax(int &a, int b) { return a < b ? a = b, 1 : 0; }
inline int ckmin(int &a, int b) { return a > b ? a = b, 1 : 0; }

bool cmp(pair<int, int> a, pair<int, int> b){
	return a.fi * b.se < a.se * b.fi;
}

class Moneymanager{
public:
	pair<int, int> p[50];
	int f[26][26][251], s[51];

	int getbest(vector<int> a, vector<int> b, int X) {
		int n = a.size();
		for(int i = 0; i < n; ++i) p[i] = mkp(a[i], b[i]);
		sort(p, p + n, cmp);
		for(int i = 1; i <= n; ++i) s[i] = s[i - 1] + p[i - 1].se;

		n /= 2; int ans = 0;
		for(int bs = 0; bs <= n * 10; ++bs){
			memset(f, -1, sizeof(f));
			f[0][0][0] = 0;
			for(int i = 0; i <= n; ++i)
				for(int j = 0; j <= n; ++j){
					int x = i + j;
					for(int k = 0; k <= i * 10; ++k)
						if(f[i][j][k] >= 0){
							if(i < n) ckmax(f[i + 1][j][k + p[x].se], f[i][j][k] + p[x].fi * (k + p[x].se));
							if(j < n) ckmax(f[i][j + 1][k], f[i][j][k] + p[x].fi * (s[x + 1] - k + bs));
						}
				}
			if(f[n][n][bs] >= 0) ckmax(ans, f[n][n][bs] + X * bs);
		}
		return ans;
	}
};
