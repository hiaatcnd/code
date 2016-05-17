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

class FoxAirline2{
public:
	int m;
	vector<int> A, B;
	int find(vector<int> &a, int x){
		return(a[x] == x ? x : a[x] = find(a, a[x]));
	}
	bool check(vector<int> &a, int x, int y){
		int xx = find(a, x), yy = find(a, y);
		return xx != yy;
	}
	void merge(vector<int> &a, int x, int y){
		int xx = find(a, x), yy = find(a, y);
		a[xx] = yy;
	}
	bool dfs(int i, vector<int> g, vector<int> f){
		int n = g.size();
		if(i == m){
			for(int i = 1; i < n; i++)
				if(find(g, 0) != find(g, i) || find(f, 0) != find(f, i)) return 0;
			return 1;
		}
		if(!check(g, A[i], B[i]) && !check(f, A[i], B[i])) return dfs(i + 1, g, f);
		if(check(g, A[i], B[i])){
			auto gg = g;
			merge(gg, A[i], B[i]);
			if (dfs(i + 1, gg, f)) return 1;
		}
		if(check(f, A[i], B[i])){ 
			auto ff = f;
			merge(ff, A[i], B[i]);
			if (dfs(i + 1, g, ff)) return 1;
		}
		return 0; 
	}
	
	string isPossible(int n, vector<int> a, vector<int> b) {
		m = a.size();
		A = a, B = b;
		if(m < 2 * n - 2) return "Impossible";
		vector<int> g, f;
		for(int i = 0; i < n; i++) g.pb(i), f.pb(i);
		if(dfs(0, g, f)) return "Possible";
		else return "Impossible";
	}
};
