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

class BracketSequenceDiv1{
public:
	string S;
	int n;
	ll dp[64][64], dps[64][64];

	ll calcS(int s, int t){
		if(s > t) return 0;
		if(dps[s][t] != -1) return dps[s][t];
		dps[s][t] = 0;
		for(int i = s; i < t; i++)
			for(int j = i + 1; j <= t; j++)
				if((S[i] == '(' && S[j] == ')') || (S[i] == '[' && S[j] == ']'))
					dps[s][t] += calc(i + 1, j - 1) + 1;
		return dps[s][t];
	}

	ll calc(int s, int t){
		if(s > t) return 0;
		if(dp[s][t] != -1) return dp[s][t];
		dp[s][t] = calcS(s, t);
		for(int i = s + 1; i <= t; i++)
			dp[s][t] += (calcS(s, i) - calcS(s, i - 1)) * calc(i + 1, t);
		return dp[s][t];
	}
	long long count(string s) {
		S = s;
		n = s.length();
		memset(dp, -1, sizeof(dp));
		memset(dps, -1, sizeof(dps));
		return calc(0, n - 1);
	}
};
