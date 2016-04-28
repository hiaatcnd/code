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

typedef pair<int, int> mp;
const int maxn = 2016;

class ParenthesesDiv1Medium{
public:
	bool flag;
	int a[maxn], res, le, ri;
	vector<int> g[maxn];
	stack<mp> st;

	void work(int l, int r){
		if(!flag) return;
		if((r - l + 1) & 1) flag = 0;
		int o = 0, w = 0;
		for(int i = l; i <= r; i++){
			o += a[i];
			w = min(w, o);
		}
		if(o > 0) le += o / 2;
		else ri -= o / 2;
		if(o < 0) w = w - o;
		res += (-w + 1) / 2;
		for(int i = l; i <= r; i++) a[i] = 0;
	}

	int minSwaps(string s, vector<int> L, vector<int> R) {
		int n = s.size();
		int m = L.size();
		flag = 1;
		for(int i = 0; i < m; i++) g[L[i]].pb(R[i]);
		for(int i = 0; i < n; i++){
			sort(all(g[i])); a[i] = s[i] == '(' ? 1 : -1;
			while(!st.empty() && st.top().se < i) work(st.top().fi, st.top().se), st.pop();
			for(auto v : g[i])
				if(!st.empty() && v >= st.top().se){
					auto t = st.top();
					st.pop();
					if(t.fi < i) work(t.fi, i - 1);
					t.fi = i;
					st.push(t);
					if(v > t.se) g[t.se + 1].pb(v);
				}else st.push(mkp(i, v));
		}
		while(!st.empty()) work(st.top().fi, st.top().se), st.pop();
		res += max(le, ri);
		int t = min(le, ri);
		le -= t, ri -= t;
		for(int i = 1; i <= n; i++)
			if(a[i] == -1) le--; else if(a[i] == 1) ri--;
		if(le > 0 || ri > 0) return -1;
		if(!flag) return -1;
		else return res;
	}
};
