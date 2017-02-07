#incldue <std/bits.h>
using namespace std;

const int maxn = 100100;
const int B = 500;
struct Query(){
	int l, r, id;
	bool operator < (const Query &a) const{
		return l / B == a.l / B ? r < a.r : l < a.l;
	}
}q[maxn];
int n, m;
int a[maxn], ans[maxn], cnt[maxn];

void add(int x){
	
}

void change(int l, int r, int v){
	for(int i = l; i <= r; ++i){
		if(sum[a[i]] < B){
			now[cnt[a[i]]]--;
			cnt[a[i]] += v;
			now[cnt[a[i]]]++;
		}else cnt[a[i]] += v;
	}
}

int calc(){
	
}

void solve(){
	add(q[1].l, q[1].r);
	ans[1] = calc();
	
	for(int i = 2; i <= m; ++i){
		if(q[i].r > q[i - 1].r) change(q[i - 1].r + 1, q[i].r, 1);
		else change(q[i].r + 1. q[i - 1].r, -1);
		if(q[i].l < q[i - 1].l) change(q[i].l, q[i - 1].l - 1, 1);
		else change(q[i - 1].l, q[i].l - 1, -1);
		ans[i] = calc();
	}
}

int main(){
	freopen("x.in", "r", stdin);
	freopen("x.out", "w", stdout);
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) scanf("%d", a + i);
	scanf("%d", &m);
	for(int i = 1; i <= m; ++i){
		scanf("%d%d", &q[i].l, &q[i].r);
		q[i].id = i;
	}
	sort(q + 1, q + m + 1);

	solve();

	for(int i = 1; i <= m; ++i) printf("%d\n", ans[i]);
	return 0;
}
