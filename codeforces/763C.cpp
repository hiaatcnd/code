#include<bits/stdc++.h>
using namespace std; 

const int maxn = 100100;
int n, m;
int a[maxn];

int main(){
#ifndef ONLINE_JUDGE
	freopen("x.in", "r", stdin);
	freopen("x.out", "w", stdout);
#endif
	scanf("%d%d", &m, &n);
	for(int i = 1; i <= n; ++i) scanf("%d", a + i);
	if(n == 1) { printf("%d %d\n", a[1], 0); return 0; }
	sort(a + 1, a + n + 1);
	for(int i = 2; i <= n; ++i){
		int d = a[i] - a[1];
		int l = -1, r = 2, lt = (a[1] + m - d) % m, rt = (a[1] + 2 * d % m) % m;
		while(r - l <= n && *lower_bound(a + 1, a + n + 1, rt) == rt) r++, rt = (rt + d) % m;
		while(r - l <= n && *lower_bound(a + 1, a + n + 1, lt) == lt) l--, lt = (lt + m - d) % m;
		if (r - l - 1 >= n){
			printf("%d %d\n", (lt + d) % m, d);
			return 0;
		}
	}
	printf("-1\n");
}
