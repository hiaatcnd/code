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

const int maxn = 55;

class RookGraph{
public:
	int fac[maxn], c[maxn][maxn];
	int f[60][60][60];
	int calc[60];
	int colsize[60], rowsize[60];
	pair<int, int> placed[60];
	vector<string> reGraph[60];

	void init(){
		int n = 50;
		fac[0] = 1;
		for(int i = 1; i <= n; ++i) fac[i] = (ll)fac[i - 1] * i % M;
		c[0][0] = 1;
		for(int i = 1; i <= n; c[i++][0] = 1)
			for(int j = 1; j <= i; ++j)
				c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % M;
	}
	
	int solve(int C, int R, vector<string> graph){
		int n = graph.size();
		if(C < 0 || R < 0) return 0;
		if(!n) return 1;
		if(C * R < n) return 0;
		
		if(!calc[n]){
			for(int i = 0; i < n; ++i) placed[i] = mkp(-1, -1);
			placed[0] = mkp(0, 0);

			vector<int> col_rooks, row_rooks;
			int col_used = 0, row_used = 0;

			for(int i = 1; i < n; ++i)
				if(graph[0][i] == '1'){
					for(int j = 1; j < n; ++j)
						if(graph[0][j] == '1' && graph[i][j] == '1'){
							col_rooks.pb(j);
							placed[j] = mkp(0, col_rooks.size());
						}
					break;
				}
			
			for(int i = 1; i < n; ++i)
				if(graph[0][i] == '1' && placed[i].fi == -1){
					for(int j = 1; j < n; ++j)
						if(graph[0][j] == '1' && graph[i][j] == '1'){
							row_rooks.pb(j);
							placed[j] = mkp(row_rooks.size(), 0);
						}
					break;
				}
			
			while(col_used < col_rooks.size() || row_used < row_rooks.size()){
				if(col_used < col_rooks.size()){
					int th = col_rooks[col_used];
					vector<int> newRows;
					for(int i = 0; i < n; ++i)
						if(placed[i].fi == -1 && graph[i][th] == '1'){
							bool found = 0;
							
							for(int j : row_rooks)
								if(graph[j][i] == '1'){
									found = 1;
									placed[i] = mkp(placed[j].fi, placed[th].se);
									break;
								}
							if(!found) newRows.pb(i);
						}
					for(int i : newRows){
						row_rooks.pb(i);
						placed[i] = mkp(row_rooks.size(), placed[th].se);
					}
					col_used++;
				}else{
					int th = row_rooks[row_used];
					vector<int> newRows;
					for(int i = 0; i < n; ++i)
						if(placed[i].fi == -1 && graph[i][th] == '1'){
							bool found = 0;
							for(int j : col_rooks)
								if(graph[j][i] == '1'){
									found = 1;
									placed[i] = mkp(placed[th].fi, placed[j].se);
									break;
								}
							if(!found) newRows.pb(i);
						}
					for(int i : newRows){
						col_rooks.pb(i);
						placed[i] = mkp(placed[th].fi, col_rooks.size());
					}
					row_used++;
				}
			}
			
			for(int i = 0; i < n; ++i)
				for(int j = i + 1; j < n; ++j){
					if((placed[i].fi == -1) ^ (placed[j].fi == -1)){
						if(graph[i][j] == '1') return 0;
					}
					
					if(placed[i].fi != -1 && placed[j].fi != -1){
						if(placed[i] == placed[j]) return 0;
						if((placed[i].fi == placed[j].fi || placed[i].se == placed[j].se) != graph[i][j] - '0')
							return 0;
					}
				}

			vector<string> re_graph;
			for(int i = 0; i < n; ++i)
				if(placed[i].fi == -1){
					string s = "";
					for(int j = 0; j < n; ++j)
						if(placed[j].fi == -1) s += graph[i][j];
					re_graph.pb(s);
				}
			
			reGraph[n] = re_graph;
			colsize[n] = col_rooks.size();
			rowsize[n] = row_rooks.size();
			calc[n] = 1;
		}
		
		int &ret = f[n][C][R];
		if(ret == -1){
			int colSize = colsize[n];
			int rowSize = rowsize[n];
			int th1 = 0, th2 = 0;
			th1 = (ll)c[C][colSize + 1] * c[R][rowSize + 1] % M;
			th1 = (ll)th1 * fac[colSize + 1] % M;
			th1 = (ll)th1 * fac[rowSize + 1] % M;
			th1 = (ll)th1 * solve(C - 1 - colSize, R - 1 - rowSize, reGraph[n]) % M;
			if(colSize){
				th2 = (ll)c[C][rowSize + 1] * c[R][colSize + 1] % M;
				th2 = (ll)th2 * fac[colSize + 1] % M;
				th2 = (ll)th2 * fac[rowSize + 1] % M;
				th2 = (ll)th2 * solve(C - 1 - rowSize, R - 1 - colSize, reGraph[n]) % M;
			}
			ret = (th1 + th2) % M;
		}
		return ret;
	}

	int countPlacements(int N, vector<string> graph) {
		init();
		memset(f, -1, sizeof(f));
		return solve(N, N, graph);
	}
};
