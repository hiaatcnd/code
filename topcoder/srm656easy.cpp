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

class RandomPancakeStack{
public:
	double dp[300][300];
	double expectedDeliciousness(vector<int> d) {
		int n = d.size();
		memset(dp, 0, sizeof(dp));
		dp[n][0] = 1;
		double ans = 0;
		for(int i = n - 1; i >= 0; --i){
			for(int j = n; j > i; --j)
				for(int k = 0; k <= n - j; ++k)
					dp[i][k + j - i - 1] += dp[j][k] * (1. / (k + j));
			for(int k = 0; k <= n - i; ++k) ans += dp[i][k] * d[i];
		}
		return ans;
	}
};
