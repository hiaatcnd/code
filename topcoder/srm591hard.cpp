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
#define M 1000000009

inline void add(int &a, int b){
	a += b;
	if(a >= M) a -= M;
}

inline int mul(int a, int b){
	return (ll)a * b % M;
}

class StringPath{
public:
	int f[8][8][1 << 8][1 << 8];
	int countBoards(int n, int m, string A, string B) {
		if(A[0] != B[0]) return 0;
		for(int i = 0; i < n; ++i){
			if(i == 0) f[0][0][1][1] = 1; else
				for(int k = 0; k < 1 << m; ++k)
					for(int l = 0; l < 1 << m; ++l){
						if(A[i] == B[i]){
							add(f[i][0][k][l], f[i - 1][m - 1][k][l]);
							add(f[i][0][k & (k ^ 1)][l & (l ^ 1)], mul(f[i - 1][m - 1][k][l], 25));
						}else{
							add(f[i][0][k][l & (l ^ 1)], f[i - 1][m - 1][k][l]);
							add(f[i][0][k & (k ^ 1)][l], f[i - 1][m - 1][k][l]);
							add(f[i][0][k & (k ^ 1)][l & (l ^ 1)], mul(f[i - 1][m - 1][k][l], 24));
						}
					}

			for(int j = 1; j < m; ++j)
				for(int k = 0; k < 1 << m; ++k)
					for(int l = 0; l < 1 << m; ++l){
						int p1 = (k & (1 << (j - 1))) << 1, q1 = k & (1 << j);
						int p2 = (l & (1 << (j - 1))) << 1, q2 = l & (1 << j);
						if(A[i + j] == B[i + j]){
							add(f[i][j][k | p1][l | p2], f[i][j - 1][k][l]);
							add(f[i][j][k & (k ^ q1)][l & (l ^ q2)], mul(f[i][j - 1][k][l], 25));
						}else{
							add(f[i][j][k | p1][l & (l ^ q2)], f[i][j - 1][k][l]);
							add(f[i][j][k & (k ^ q1)][l | p2], f[i][j - 1][k][l]);
							add(f[i][j][k & (k ^ q1)][l & (l ^ q2)], mul(f[i][j - 1][k][l], 24));
						}
					}
		}
		int ans = 0;
		for(int k = 1 << (m - 1); k < 1 << m; ++k)
			for(int l = 1 << (m - 1); l < 1 << m; ++l)
				add(ans, f[n - 1][m - 1][k][l]);
		return ans;
	}
};
