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

const int maxn = 50010, maxk = 1000100, B = 300;
struct query{
	int l, r, id;
	bool operator < (const query &a) const{
		return l / B == a.l / B ? r < a.r : l < a.l;
	}
}que[maxn];

int n, m, k;
int ans[maxn], a[maxn], b[maxn];
int cnt1[maxk], cnt2[maxk];

int nowans;
void add(int l, int r, int v){
	for(int i = l; i <= r; ++i){
		nowans -= min(cnt1[a[i]], cnt2[a[i]]);
		cnt1[a[i]] += v;
		nowans += min(cnt1[a[i]], cnt2[a[i]]);
		nowans -= min(cnt1[b[i]], cnt2[b[i]]);
		cnt2[b[i]] += v;
		nowans += min(cnt1[b[i]], cnt2[b[i]]);
	}
}

void solve(){
	add(que[0].l, que[0].r, 1);
	ans[que[0].id] = nowans;

	for(int i = 1; i < m; ++i){
		if(que[i].r > que[i - 1].r) add(que[i - 1].r + 1, que[i].r, 1);
		else add(que[i].r + 1, que[i - 1].r, -1);
		if(que[i].l < que[i - 1].l) add(que[i].l, que[i - 1].l - 1, 1);
		else add(que[i - 1].l, que[i].l - 1, -1);
		ans[que[i].id] = nowans;
	}
}

int main(){
	scanf("%d%d%d", &n, &m, &k);
	
	for(int i = 0; i < n; ++i) scanf("%d", a + i);
	for(int i = 0; i < n; ++i) scanf("%d", b + i);

	for(int i = 0; i < m; ++i){
		scanf("%d%d", &que[i].l, &que[i].r);
		que[i].id = i;
	}
	sort(que, que + m);

	solve();

	for(int i = 0; i < m; ++i) printf("%d\n", ans[i]);
  return 0;
}
