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
int T;
char s[1000];
int main(){
	cin >> T;
	while(T--){
		scanf("%s", s);
		int k = strlen(s + 4);
		ll year = atoi(s + 4);
		ll F = 0, t = 10;
		for(int i = 1; i < k; i++){
			F += t;
			t = t * 10;
		}
		while(year < F + 1989) year += t;
		printf("%d\n", year);
	}
  return 0;
}
