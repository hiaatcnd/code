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

class DistinguishableSetDiv1{
public:
	bool nook[1 << 20];
	int count(vector<string> answer) {
		int n = answer.size();
		int m = answer[0].size();
		memset(nook, 0, sizeof(nook));
		for(int i = 1; i < n; ++i)
			for(int j = 0; j < i; ++j){
				int mask = 0;
				for(int k = 0; k < m; ++k)
					if(answer[i][k] == answer[j][k]) mask |= (1 << k);
				nook[mask] = 1;
			}
		int M = (1 << m) - 1, ans = 0;
		for(int i = M; i >= 0; --i){
			if(!nook[i]) ans++;
			else{
				for(int k = 0; k < m; ++k)
					if(i & (1 << k))
						nook[i ^ (1 << k)] = 1;
			}
		}
		return ans;
	}
};
