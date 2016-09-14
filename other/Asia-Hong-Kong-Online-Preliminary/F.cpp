//看看会不会爆int!
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
inline int ckmax(int &a, int b) { return a < b ? a = b, 1 : 0; }
inline int ckmin(int &a, int b) { return a > b ? a = b, 1 : 0; }
#define clean(a) memset(a, 0, sizeof(a))

int n, c[100100];

int main(){
	scanf("%d", &n);
	for(int i = 1; i < n; ++i)
		scanf("%d", c + i);
	int now = 0, cmin = c[1], T;
	ll ans = 0;
	scanf("%d", &T);
	for(int i = 1; i < n; ++i){
		now++, ans += c[i];
		ckmin(cmin, c[i]);
		scanf("%d", &T);
		while(now < T) now += 2, ans += cmin * 2;
	}
	printf("%lld\n", ans);
  return 0;
}
