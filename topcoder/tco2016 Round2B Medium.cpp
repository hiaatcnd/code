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

class FoxAndGemstone{
public:
	int cnt[50][16];
	int maxi[1 << 16], sum[50][1 << 16];
	ll ways[1 << 16];

	string isPossible(vector<string> bags) {
		int n = bags.size(), m = 0;
		map<string, bool> MAP;
		memset(cnt, 0, sizeof(cnt));
		for(int i = 0; i < n; ++i){
			sort(bags[i].begin(), bags[i].end());
			if(!MAP.count(bags[i])){
				int l = bags[i].size();
				for(int j = 0; j < l; ++j) cnt[m][bags[i][j] - 'A']++;
				MAP[bags[i]] = 1;
				++m;
			}
		}
		
		for(int i = 0; i < m; ++i)
			for(int mask = 0; mask < 1 << 16; ++mask)
				for(int j = 0; j < 16; ++j)
					if((mask >> j) & 1) sum[i][mask] += cnt[i][j];
		for(int mask = 0; mask < 1 << 16; ++mask)
			for(int i = 0; i < m; ++i)
				maxi[mask] = max(maxi[mask], sum[i][mask]);
		
		ll res = 1;
		for(int i = 1; i <= 16; ++i) res *= i;		
		for(int i = 0; i < n; ++i){
			memset(ways, 0, sizeof(ways));
			ways[0] = 1;
			for(int mask = 1; mask < 1 << 16; ++mask)
				if(sum[i][mask] == maxi[mask])
					for(int j = 0; j < 16; ++j)
						if((mask >> j) & 1)
							ways[mask] += ways[mask ^ (1 << j)];
			res -= ways[(1 << 16) - 1];
		}
		return res > 0 ? "Impossible" : "Possible";
	}
};
