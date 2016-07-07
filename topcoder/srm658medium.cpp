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

bool cmp1(int a, int b){
	return a % 9 > b % 9;
}

class Mutalisk{
public:
	int a[30], b[30], c[30];
	int dp[21][100][100];

	bool check(int d, vector<int> x){
		int n = x.size();
		memset(dp, 127, sizeof(dp));
		memset(dp[0], 0, sizeof(dp[0]));
		for(int i = 1; i <= n; ++i){
			for(int j = 0; j <= d; ++j)
				for(int k = 0; k <= d; ++k)
					if(dp[i - 1][j][k] < 1e9){
						for(int jj = 0; jj * 9 <= x[i - 1] + 9 && j + jj <= d; ++jj)
							for(int kk = 0; jj * 9 + kk * 3 <= x[i - 1] + 9 && jj + kk <= d && k + kk <= d; ++kk){
								int t = max(x[i - 1] - jj * 9 - kk * 3, 0);
								if(jj + kk + t > d) continue;
								dp[i][j + jj][k + kk] = min(dp[i][j + jj][k + kk], dp[i - 1][j][k] + t);
							}
					}
		}
		for(int i = 0; i <= d; ++i)
			for(int j = 0; j <= d; ++j)
				if(dp[n][i][j] <= d) return 1;
		return 0;
	}

	int minimalAttacks(vector<int> x) {
		int l = 0, r = 100;
		while(l + 1 < r){
			int m = (l + r) >> 1;
			if(check(m, x)) r = m;
			else l = m;
		}
		return r;
	}
};

// CUT begin
ifstream data("Mutalisk.sample");

string next_line() {
    string s;
    getline(data, s);
    return s;
}

template <typename T> void from_stream(T &t) {
    stringstream ss(next_line());
    ss >> t;
}

void from_stream(string &s) {
    s = next_line();
}

template <typename T> void from_stream(vector<T> &ts) {
    int len;
    from_stream(len);
    ts.clear();
    for (int i = 0; i < len; ++i) {
        T t;
        from_stream(t);
        ts.push_back(t);
    }
}

template <typename T>
string to_string(T t) {
    stringstream s;
    s << t;
    return s.str();
}

string to_string(string t) {
    return "\"" + t + "\"";
}

bool do_test(vector<int> x, int __expected) {
    time_t startClock = clock();
    Mutalisk *instance = new Mutalisk();
    int __result = instance->minimalAttacks(x);
    double elapsed = (double)(clock() - startClock) / CLOCKS_PER_SEC;
    delete instance;

    if (__result == __expected) {
        cout << "PASSED!" << " (" << elapsed << " seconds)" << endl;
        return true;
    }
    else {
        cout << "FAILED!" << " (" << elapsed << " seconds)" << endl;
        cout << "           Expected: " << to_string(__expected) << endl;
        cout << "           Received: " << to_string(__result) << endl;
        return false;
    }
}

int run_test(bool mainProcess, const set<int> &case_set, const string command) {
    int cases = 0, passed = 0;
    while (true) {
        if (next_line().find("--") != 0)
            break;
        vector<int> x;
        from_stream(x);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(x, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1467898644;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 650 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
    }
    return 0;
}

int main(int argc, char *argv[]) {
    cout.setf(ios::fixed, ios::floatfield);
    cout.precision(2);
    set<int> cases;
    bool mainProcess = true;
    for (int i = 1; i < argc; ++i) {
        if ( string(argv[i]) == "-") {
            mainProcess = false;
        } else {
            cases.insert(atoi(argv[i]));
        }
    }
    if (mainProcess) {
        cout << "Mutalisk (650 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
