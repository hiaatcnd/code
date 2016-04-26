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

class ParenthesesDiv1Easy{
public:
	int n;
	string S;
	int F(char c) { return c == '(' ? 1 : -1; }
	vector<int> correct(string s) {
		n = s.length(); int tot = 0;
		S = s;
		vector<int> ans;
		if(n & 1) return vector<int>(1, -1);
		for(int i = 0; i < n; i++) tot += F(s[i]);
		for(int i = 0, j = 0; i < n; i++){
			j += F(s[i]);
			if(tot - 2 * j == 0){
				ans.pb(0);
				ans.pb(i);
				for(int k = 0; k <= i; k++)
					s[k] = S[i - k] == '(' ? ')' : '(';
				break;
			}
		}
		int maxR = -1;
		for(int i = n - 1; i >= 0; i--){
			bool flag = 1; int tt = 0;
			for(int j = i; j >= 0; j--){
				tt += F(s[j]);
				if(tt > 0) { flag = 0; break; }
			}
			if(!flag) continue;
			maxR = i; break;
		}
		ans.pb(0); ans.pb(maxR);
		return ans;
	}
};
