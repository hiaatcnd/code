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

class TrySail{
public:
	int f[51][256][256];
	int get(vector<int> strength) {
		int n = strength.size();
		sort(all(strength));
		memset(f, 128, sizeof(f));
		f[0][0][0] = 0;
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < 256; ++j)
				for(int k = 0; k < 256; ++k)
					if(f[i][j][k] >= 0){
						f[i + 1][j][k] = max(f[i + 1][j][k], f[i][j][k] ^ strength[i]);
						ckmax(f[i + 1][j ^ strength[i]][k], f[i][j][k]);
						ckmax(f[i + 1][j][k ^ strength[i]], f[i][j][k]);
					}
		int ans = 0;
		for(int j = 0; j < 256; ++j)
			for(int k = 0; k < 256; ++k)
				ans = max(ans, f[n][j][k] + j + k);
		return ans;
	}
};
