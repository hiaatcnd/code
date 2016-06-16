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

class RockPaperScissorsMagic{
public:
	int C[1010][1010];
	int count(int win, int lose, int tie, vector<int> card) {
		int n = card.size();
		vector<int> cnt(3);
		for(int i = 0; i < n; ++i) cnt[card[i]]++;
		for(int i = 0; i <= 1000; C[i++][0] = 1)
			for(int j = 1; j <= i; ++j)
				C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % M;	

		map<pair<int, int>, int> mp[3];
		for(int i = 0; i < 3; ++i)
			for(int j = 0; j <= cnt[i]; ++j)
				for(int k = 0; j + k <= cnt[i]; ++k){
					int l = cnt[i] - j - k;
					int TS = win * j + tie * k + lose * l;
					int TR = win * l + tie * j + lose * k;
					int TP = win * k + tie * l + lose * j;
					int C1 = TS - TP;
					int C2 = TR - TS;
					(mp[i][mkp(C1, C2)] += (ll)C[cnt[i]][j] * C[cnt[i] - j][k] % M) %= M;
				}
		int ans = 0;
		for(auto p : mp[0]){
			if(!mp[1].count(p.fi) || !mp[2].count(p.fi)) continue;
			//if(mp[1][p.fi] == 1 && mp[2][p.fi] == 1) ans++;
			(ans += (ll)mp[0][p.fi] * mp[1][p.fi] % M * mp[2][p.fi] % M) %= M;
		}
		return ans;
	}
};
