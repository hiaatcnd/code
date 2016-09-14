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
#define M 1000000007

char s[500100];
int inv[500100];

int main(){
	scanf("%s", s);
	int n = strlen(s), cnt1 = 0, cnt0 = 0, cnt2 = 0;
	ll sum1 = 0, sum2 = 0;
	
	for(int i = 0; i < n; ++i)
		if(s[i] == '0') cnt0++;
		else if(s[i] == '1') cnt1++, sum1 += i;
		else cnt2++, sum2 += i;

	sum1 %= M, sum2 %= M;
	
	inv[1] = 1;
	int now = 1, ans = 0;
	for(int i = 0; i <= cnt2; ++i){
		int cnt = i + cnt1;
		int tmp = ((ll)(n - 1) * cnt - (ll)cnt * (cnt - 1) / 2) % M;
		ans += (ll)now * tmp % M;
		ans = (ans % M + M) % M;
		if(i) inv[i + 1] = (ll)(M - M / (i + 1)) * inv[M % (i + 1)] % M;
		now = (ll)now * (cnt2 - i) % M * inv[i + 1] % M;
	}

	int two = 1;
	for(int i = 1; i < cnt2; ++i) two = two * 2 % M;
	ans -= ((ll)two * sum2 + (ll)two * (cnt2 ? 2 : 1) * sum1) % M;
	if(ans < 0) ans += M;
	ans = (ans % M + M) % M;
	printf("%d\n", ans);
  return 0;
}

