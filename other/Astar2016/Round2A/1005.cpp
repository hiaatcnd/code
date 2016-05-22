#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <set>
#include <queue>
#include <vector>
#include <iostream>
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
ll L, R;

ll got(ll len, ll n, bool k){
	if(len == n){ return len / 2 + k; }
	if(n <= len / 2) return got(len / 2, n, k);
	if(n == len / 2 + 1) return got(len / 2, len / 2, k) + k;
	return got(len / 2, len / 2, k) + k + got(len / 2, len / 2, k ^ 1) - got(len / 2, len - n, k ^ 1);
}

ll get(ll n){
	if(!n) return 0;
	int t = 1; ll len = 1;
	while(len < n) t++, len = len * 2 + 1;
	return got(len, n, 1);
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("e.in", "r", stdin);
	freopen("e.out", "w", stdout);
#endif
	cin >> T;
	while(T--){
		cin >> L >> R;
		cout << get(R) - get(L - 1) << '\n';
	}
  return 0;
}
/*
                   _ooOoo_
                  o8888888o
                  88" . "88
                  (| -_- |)
                  O\  =  /O
               ____/`---'\____
             .'  \\|     |//  `.
            /  \\|||  :  |||//  \
           /  _||||| -:- |||||-  \
           |   | \\\  -  /// |   |
           | \_|  ''\---/''  |   |
           \  .-\__  `-`  ___/-. /
         ___`. .'  /--.--\  `. . __
      ."" '<  `.___\_<|>_/___.'  >'"".
     | | :  `- \`.;`\ _ /`;.`/ - ` : | |
     \  \ `-.   \_ __\ /__ _/   .-` /  /
======`-.____`-.___\_____/___.-`____.-'======
                   `=---='
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
         佛祖保佑       永无BUG
*/
