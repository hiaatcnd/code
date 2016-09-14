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
#define M 1000000009
typedef long long ll;

int n, m, x;
int cnt[500100], two[500100];

inline int get(int l, int r){
	return cnt[r] - cnt[l - 1];
}

int main(){
	scanf("%d", &n);
	int cnt_zero = 0;

	int sum = 0;
	for(int i = 0; i < n; ++i){
		scanf("%d", &m);
		for(int j = 1; j <= m; ++j){
			scanf("%d", &x); x--;
			if(x == i) cnt_zero++;
			else cnt[(i - x + n) % n]++;
		}
		sum += m;
	}
	for(int i = 1; i <= n; ++i) cnt[i] += cnt[i - 1];

	two[0] = 1;
	for(int i = 1; i <= sum; ++i) two[i] = two[i - 1] * 2 % M;

	int ans = 0;
	for(int i = 1; i < n; ++i){
		int tmp = two[get(i, i)] - 1;
		if(n - i >= i){
			int tmp1 = two[get(1, i - 1)];
			ans += (ll)tmp * tmp1 % M * i % M;
		}else{
			int tmp1 = two[get(1, n - i)] - 1;
			int tmp2 = two[get(n - i + 1, i - 1)];
			ans += (ll)tmp * tmp1 % M * tmp2 % M * i % M;
		}
		ans %= M;
		
		int j = n - i;
		tmp = two[get(j, j)] - 1;
		if(n - i > i){
			int tmp1 = two[get(j + 1, n - 1)];
			ans += (ll)tmp * tmp1 % M * i % M;
		}else{
			int tmp1 = two[get(i + 1, n - 1)] - 1;
			int tmp2 = two[get(j + 1, i)];
			ans += (ll)tmp * tmp1 % M * tmp2 % M * i % M;
		}
		ans %= M;
	}
	ans = (ll)ans * two[cnt_zero] % M;
	
	printf("%d\n", ans);
  return 0;
}
