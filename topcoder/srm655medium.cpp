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
#define M 1000000007

void add(int &a, int b){
	a += b;
	if(a >= M) a -= M;
}

int mul(int a, int b) { return (ll)a * b % M; }

class Nine{
public:
	int ways[5001][9], cnt[1 << 5];
	int f[2][9*9*9*9*9];
	int count(int N, vector<int> d) {
		int m = d.size();
		ways[0][0] = 1;
		for(int i = 0; i < m; ++i)
			for(int j = 0; j < 9; ++j)
				for(int k = 0; k < 10; ++k)
					add(ways[i + 1][(j + k) % 9], ways[i][j]);
		
		bool tag = 0;
		for(int x : d) ++cnt[x];
		f[0][0] = 1;
		for(int mask = 0; mask < 32; ++mask){
			tag ^= 1;
			memset(f[tag], 0, sizeof(f[tag]));
			for(int k = 0; k < 9 * 9 * 9 * 9 * 9; ++k)
				if(f[tag ^ 1][k])
					for(int x = 0; x < 9; ++x){
						int num = k, res = 0;
						for(int j = 0, base = 1; j < 5; ++j, base *= 9){
							int t = (mask & (1 << j)) ? (num % 9 + x) % 9 : num % 9;
							res += t * base;
							num /= 9;
						}
						add(f[tag][res], mul(f[tag ^ 1][k], ways[cnt[mask]][x]));
					}
		}
		return f[tag][0];
	}
};

// CUT begin
ifstream data("Nine.sample");

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

bool do_test(int N, vector<int> d, int __expected) {
    time_t startClock = clock();
    Nine *instance = new Nine();
    int __result = instance->count(N, d);
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
        int N;
        from_stream(N);
        vector<int> d;
        from_stream(d);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(N, d, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1467730408;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 500 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "Nine (500 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
