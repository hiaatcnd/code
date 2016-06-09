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


double p[260][12], ex[260], pos[260];
int w[260];
bool cmp(int x, int y) { return ex[x] * pos[y] < ex[y] * pos[x]; }

class MagicalMatrix{
public:
	double MagicalInspection(int n, int m, vector<int> prob) {
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < m; ++j)
				p[j][i] = 0.01 * prob[i * m + j];
		for(int i = 0; i < m; ++i){
			sort(p[i], p[i] + n);
			pos[i] = 1; ex[i] = 0;
			for(int j = 0; j < n; ++j){
				ex[i] += pos[i];
				pos[i] = pos[i] * p[i][j];
			}
			w[i] = i;
		}
		sort(w, w + m, cmp);
		double ans = 0, po = 1;
		for(int i = 0; i < m; ++i){
			ans += ex[w[i]] * po;
			po *= (1 - pos[w[i]]);
		}
		return ans;
	}
};
