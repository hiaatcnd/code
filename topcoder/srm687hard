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

const int inf = 1e9, maxn = 55;
int inx, n, c[maxn][maxn], S[maxn], T[maxn], lx[maxn], rx[maxn], match[maxn], slack[maxn];
int d[maxn][maxn];

void update(){
	int delta = inf;
	for(int i = 1; i <= n; i++)
		if(T[i] < inx) delta = min(delta, slack[i]);
	for(int i = 1; i <= n; i++){
		if(S[i] == inx) lx[i] -= delta;
		if(T[i] == inx) rx[i] += delta;
	}
}

bool hungary(int p){
	S[p] = inx;
	for(int i = 1; i <= n; i++)
		if(T[i] < inx){
			if(lx[p] + rx[i] == c[p][i]){
				T[i] = inx;
				if(!match[i] || hungary(match[i])){
					match[i] = p;
					return 1;
				}
			}else slack[i] = min(slack[i], lx[p] + rx[i] - c[p][i]);
		}
	return 0;
}

void KM(){
	for(int i = 1; i <= n; i++){
		lx[i] = -inf, rx[i] = 0;
		for(int j = 1; j <= n; j++)
			lx[i] = max(lx[i], c[i][j]);
	}
	memset(match, 0, sizeof(match));
	for(int i = 1; i <= n; i++){
		memset(slack, 127, sizeof(slack));
		while(inx++, !hungary(i)) update();
	}
}

class AlienSkiSlopes{
public:
	vector<int> raise(vector<int> h) {
		n = sqrt(h.size() + 0.5);
		for(int i = 0; i < n; i++)
			for(int j = 0; j < n; j++)
				c[i + 1][j + 1] = h[i * n + j];
		KM();
		for(int i = 1; i <= n; i++){
			int p = match[i];
			for(int j = 1; j <= n; j++)
				d[j][i] = c[p][i] - c[p][j];
		}
		for(int k = 1; k <= n; k++)
			for(int i = 1; i <= n; i++)
				for(int j = 1; j <= n; j++)
					d[i][j] = min(d[i][k] + d[k][j], d[i][j]);
		int tmin = 0;
		for(int i = 1; i <= n; i++)
			tmin = min(tmin, d[1][i]);
		vector<int> ans;
		for(int i = 1; i <= n; i++)
			if(c[match[i]][i] - d[1][i] + tmin < 0) return vector<int>(1, -1);
			else ans.pb(d[1][i] - tmin);
		return ans;
	}
};
