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

const int xx[4] = {0, 0, 1, -1};
const int yy[4] = {1, -1, 0, 0};

class FoxConnection3{
public:
	ll ans;
	int n, c[6], tx[6], ty[6];
	vector<int> X, Y;
	vector<pair<int, int> > q;
	void dfs(int t){
		if (t == n){
			for(int i = 0; i < n; ++i) c[i] = i;
			do{
				for(int i = 0; i < n; ++i)
					tx[i] = X[c[i]] - q[i].fi, ty[i] = Y[c[i]] - q[i].se;
				sort(tx, tx + n), sort(ty, ty + n);
				int ax = tx[n / 2], ay = ty[n / 2];
				ll res = 0;
				for(int i = 0; i < n; ++i){
					res += abs(tx[i] - ax);
					res += abs(ty[i] - ay);
				}
				ans = min(ans, res);
			}while(next_permutation(c + 1, c + n));
			return;
		}
		for(int i = 0; i < t; ++i)
			for(int j = 0; j < 4; ++j){
				int x = q[i].fi + xx[j], y = q[i].se + yy[j];
				bool flag = 1;
				for(int k = 0; k < t; ++k)
					if(q[k] == mkp(x, y)) { break; flag = 0; }
				if(!flag) continue;
				q.pb(mkp(x, y));
				dfs(t + 1);
				q.resize(t);
			}
	}
	
	long long minimalSteps(vector<int> tx, vector<int> ty) {
		X = tx, Y = ty;
		n = X.size();
		q.clear();
		q.pb(mkp(0, 0));
		ans = 1LL << 60;
		dfs(1);
		return ans;
	}
};
