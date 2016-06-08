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
const int N = 105;
const int n = 20;

int g[n][n], a[n][n];
int G[2000][n][n], val[2000];

int inverse(int x){
	return x == 1 ? x : (ll)(M - M / x) * inverse(M % x) % M;
}

int cal(){
	memset(a, 0, sizeof(a));
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < i; ++j)
			if(g[i][j]){
				a[i][j] = (a[i][j] + M - 1) % M;
				a[j][i] = (a[j][i] + M - 1) % M;
				++a[i][i];
				++a[j][j];
			}
	int m = n - 1, res = 1;
	for(int i = 0; i < m; ++i){
		int inv = inverse(a[i][i]);
		res = (ll)res * a[i][i] % M;
		for(int j = 0; j < m; ++j)
			a[i][j] = (ll)a[i][j] * inv % M;
		for(int k = 0; k < m; ++k)
			if(i != k){
				int tmp = a[k][i];
				for(int j = 0; j < m; ++j)
					a[k][j] = (a[k][j] - (ll)tmp * a[i][j] % M + M) % M;
			}
	}
	return res;
}

vector<int> build(vector<int> id){
	vector<int> ans;
	int m = n * 4;
	ans.pb(m);
	for(int k = 0; k < 4; ++k){
		int x = id[k];
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < i; ++j)
				if(G[x][i][j]){
					int I = n * k + i;
					int J = n * k + j;
					ans.pb(I * m + J);
				}
	}
	ans.pb(0 * m + n);
	ans.pb(n * m + n * 2);
	ans.pb(2 * n * m + n * 3);
	return ans;
}

class InverseMatrixTree{
public:
	vector<int> constructGraph(int r) {
		if(!r) return vector<int>(1, 2);
		for(int T = 0; T < 2000; T++){
			memset(g, 0, sizeof(g));
			for(int i = 1; i < n; i++){
				int j = rand() % i;
				g[i][j] = g[j][i] = 1;
			}
			for(int i = 0; i < n; i++)
				for(int j = 0; j < i; j++)
					if(!g[i][j]){
						if(rand() % 100 < 80){
							g[i][j] = g[j][i] = 1;
						}
					}
			val[T] = cal();
			if(val[T] == 0) { --T; continue; }
			memcpy(G[T], g, sizeof(g));
		}
		unordered_map<int, pair<int, int> > Hash;
		for(int i = 0; i < 2000; ++i)
			for(int j = i; j < 2000; ++j){
				int v = (ll)val[i] * val[j] % M;
				int w = (ll)r * inverse(v) % M;
				if(Hash.count(w)) return build(vector<int>{i, j, Hash[w].fi, Hash[w].se});
				if(!Hash.count(v)) Hash[v] = mkp(i, j);
			}
		assert(0);
	}
};
