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

class SquareScores{
public:
	double calcexpectation(vector<int> p, string s) {
		int n = s.size(), m = p.size(); double ans = 0;
		for(int i = 0; i < n; ++i)
			if(s[i] == '?'){
				for(int k = 0; k < m; ++k){
					double pos = 0.01 * p[k];
					ans += pos;
					for(int j = i - 1; j >= 0; --j){
						if(s[j] == '?') pos *= 0.01 * p[k];
						else if(s[j] != 'a' + k) pos = 0;
						ans += pos;
					}
				}
			}else{
				double pos = 1;
				ans += pos;
				for(int j = i - 1; j >= 0; --j){
					if(s[j] == '?') pos *= 0.01 * p[s[i] - 'a'];
					else if(s[j] != s[i]) pos = 0;
					ans += pos;
				}
			}
		return ans;
	}
};
