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

class RobotOnMoon{
public:
	int longestSafeCommand(vector<string> board) {
		int n = board.size();
		int m = board[0].size();
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < m; ++j)
				if(board[i][j] == 'S'){
					for(int k = 0; k < n; ++k)
						if(board[k][j] == '#') return -1;
					for(int k = 0; k < m; ++k)
						if(board[i][k] == '#') return -1;
					return n - 1 + m - 1;
				}
		return 0;
	}
};
