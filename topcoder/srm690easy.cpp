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

class WolfCardGame{
public:
	vector<int> createAnswer(int N, int K) {
		vector<int> ans;
		if(N % 2 != 0){
			for(int i = 1; i <= K; i++) ans.pb(i * 2);
		}else if(N % 3 != 0){
			for(int i = 1; i <= K; i++) ans.pb(i * 3);
		}else if(N % 5 != 0){
			for(int i = 1; i <= K; i++) ans.pb(i * 5);
		}else{
			if(N != 60){
				for(int i = 1; i <= K; i++) ans.pb(i * 4);
			}else{
				for(int i = 1; i <= K && i <= 14; ++i) ans.pb(i * 7);
				if(K == 15) ans.pb(1);
			}
		}
		return ans;
	}
};
