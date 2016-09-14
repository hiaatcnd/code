//看看会不会爆int!
#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define FOR(i, l, r) for(int i = l; i <= r; i++)
#define ROF(i, r, l) for(int i = r; i >= l; i--)
#define all(a) a.begin(), a.end()
inline int ckmax(int &a, int b) { return a < b ? a = b, 1 : 0; }
inline int ckmin(int &a, int b) { return a > b ? a = b, 1 : 0; }
#define clean(a) memset(a, 0, sizeof(a))
typedef long long ll;

const int maxn = 200100, maxp = 200100 * 20 * 2;
int n, tot;
string s, str;
int p[maxn], rt[maxn], tr[maxn], cnt[maxp], ls[maxp], rs[maxp];
ll cal[maxp];

void manacher(string s, int n){
	int mx = 0, id;
	for(int i = 1; i < n; ++i){
		if(mx > i) p[i] = min(p[2 * id - i], mx - i);
		else p[i] = 1;
		while(s[i + p[i]] == s[i - p[i]]) ++p[i];
		if(p[i] + i > mx) mx = p[i] + i, id = i;
	}
}

int modify(int rt, int l, int r, int x){
	int t = ++tot; cnt[t] = cnt[rt], cal[t] = cal[rt];
	if(l == r){
		++cnt[t];
		cal[t] += x;
		return t;
	}
	int mid = (l + r) >> 1;
	if(x <= mid) ls[t] = modify(ls[rt], l, mid, x), rs[t] = rs[rt];
	else rs[t] = modify(rs[rt], mid + 1, r, x), ls[t] = ls[rt];
	cnt[t] = cnt[ls[t]] + cnt[rs[t]];
	cal[t] = cal[ls[t]] + cal[rs[t]];
	return t;
}

void build(){
	for(int i = 1; i < n; ++i){
		rt[i] = modify(rt[i - 1], 1, n, i - p[i]);
		tr[i] = modify(tr[i - 1], 1, n, i + p[i]);
	}
}

ll ask(int t, int l, int r, int x, int y, int v){
	if(!t) return 0;
	if(x <= l && y >= r) return cal[t] - (ll)cnt[t] * v;
	int mid = (l + r) >> 1;
	ll res = 0;
	if(x <= mid) res += ask(ls[t], l, mid, x, y, v);
	if(y > mid) res += ask(rs[t], mid + 1, r, x, y, v);
	return res;
}

ll get(int l, int r){
	int mid = (l + r) >> 1;
	ll res = (ll)(l + mid) * (mid - l + 1) / 2	- (ll)(mid + 1 + r) * (r - mid) / 2;
	ll res1 = ask(rt[mid], 1, n, l, n, l - 1) - ask(rt[l - 1], 1, n, l, n, l - 1);
	ll res2 = ask(tr[r], 1, n, 1, r, r + 1) - ask(tr[mid], 1, n, 1, r, r + 1);
	res -= res1 + (ll)(mid - l + 1) * (l - 1);
	res += res2 + (ll)(r - mid) * (r + 1);
	res -= (r - l) / 2 + 1;
	assert(!(res & 1));
	return res / 2;
}

int main(){
	cin >> s;
	n = s.size();
	str = '$';
	for(int i = 0; i < n; ++i)
		str += '#', str += s[i];
	str += '#';
	n = 2 * n + 2;
	manacher(str, n);
	build();

	int T, l, r;
	cin >> T;
	while(T--){
		cin >> l >> r;
		ll ans = get(2 * l - 1, 2 * r + 1);
		cout << ans << '\n';
	}
  return 0;
}

