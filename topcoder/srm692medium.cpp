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

int mul(int a, int b) { return (ll)a * b % M; }
void add(int &a, int b) { a += b; if(a >= M) a -= M; }
vector<int> mul(vector<int> a, vector<int> b){
	int n = a.size();
	vector<int> ans(n);
	for(int i = 0; i < n; ++i)
		for(int j = 0; j <= i; ++j)
			add(ans[i], mul(a[j], b[i - j]));
	return ans;
}

class LinenCenter{
public:
	int trans[110][27], fail[110];
	int f[1010][110];

	int countStrings(string S, int N, int K) {
		int L = S.length();
		trans[0][S[0] - 'a'] = 1;
		for(int i = 1; i <= L; ++i){
			memcpy(trans[i], trans[fail[i]], sizeof(trans[i]));
			if(i < L){
				fail[i + 1] = trans[i][S[i] - 'a'];
				trans[i][S[i] - 'a'] = i + 1;
			}
		}
		
		memset(f, 0, sizeof(f));
		f[0][0] = 1;
		for(int i = 0; i < N; ++i)
			for(int j = 0; j < L; ++j)
				if(f[i][j])
					for(int k = 0; k < 26; ++k)
						add(f[i + 1][trans[j][k]], f[i][j]);
		
		vector<int> base(N + 1), other(N + 1);
		for(int j = 0; j < L; ++j){
			int t = j; bool flag = 1;
			for(int k = 0; k < L - 1; ++k){
				t = trans[t][S[k] - 'a'];
				if(t == L) flag = 0;
			}
			for(int i = 0; i <= N; ++i){
				if(flag) add(base[i], f[i][j]);
				add(other[i], f[i][j]);
			}
		}
		
		vector<int> g(N + 1); g[0] = 1;
		for(; K; K >>= 1, base = mul(base, base))
			if(K & 1) g = mul(g, base);
		g = mul(g, other);
		int res = 0;
		for(int i = 0; i <= N; ++i) add(res, g[i]);
		return res;
	}
};
