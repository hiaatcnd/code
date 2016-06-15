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

class SuccessiveSubtraction2{
public:
	int f[2016], ff[2016], fff[2016];
	vector<int> calc(vector<int> a, vector<int> p, vector<int> v) {
		int n = a.size(), m = p.size();
		vector<int> ans;
		for(int i = 0; i < m; ++i){
			a[p[i]] = v[i];
			int sum = a[0];
			for(int j = 1; j < n; ++j) sum -= a[j];
			int res = 0;
			for(int j = 2; j < n; ++j){
				f[j] = max(f[j - 1], 0) + a[j];
				ff[j] = max(f[j - 1], ff[j - 1]);
				fff[j] = max(ff[j - 1], fff[j - 1]) + a[j];
				res = max(res, fff[j]);
			}
			ans.pb(sum + 2 * res);
		}
		return ans;
	}
};
