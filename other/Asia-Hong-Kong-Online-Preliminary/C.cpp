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

const int maxn = 200100;
struct line{
	int s, f;
	bool operator < (const line &a) const {
		return s < a.s;
	}
}l[maxn];
int n, k;

int main(){
	scanf("%d%d", &n, &k);
	for(int i = 1; i <= n; ++i)
		scanf("%d%d", &l[i].s, &l[i].f);

	sort(l + 1, l + n + 1);

	multiset<int> q;
	int ans = 0;
	for(int i = 1; i <= n; ++i){
		while(!q.empty() && *q.begin() < l[i].s) q.erase(q.begin()), ans++;
		q.insert(l[i].f);
		if(q.size() > k){
			auto it = q.end(); it--;
			q.erase(it);
		}
	}
	ans += q.size();
	printf("%d\n", ans);
  return 0;
}
