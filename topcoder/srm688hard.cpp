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

class ParenthesesDiv1Hard{
public:
	int dep[200];
	string ss[2];
	int calc(string s){
		if(!s.size()) return 0;
		int n = s.length(), cnt = 0, maxs = 0, match = -1;
		for(int i = 0; i < n; i++){
			if(s[i] == '(') cnt++;
			else{
				cnt--;
				if(cnt == 0){
					match = i;
					break;
				}
			}
			maxs = max(maxs, cnt);
		}
		return maxs * maxs + calc(s.substr(1, match - 1)) + calc(s.substr(match + 1, n - 1));
	}
	int minCost(string s) {
		int n = s.length();
		stack<int> q;
		for(int i = 0; i < n; i++)
			if(s[i] == '(') q.push(i);
			else{
				if(!q.size()) return -1;
				dep[q.top()] = q.size();
				dep[i] = q.size();
				q.pop();
			}
		if(q.size()) return -1;
		for(int i = 0; i < n; i++)
			ss[dep[i] & 1] += s[i];
		return calc(ss[0]) + calc(ss[1]);
	}
};
