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

const int maxn = 55;

void add(int &a, int b){
	a += b;
	if(a >= M) a -= M;
}

int mul(int a, int b) { return (ll)a * b % M; }

int pow(int a, int b){
	if(a == 1) return 1;
	int ans = 1;
	for(; b; b >>= 1, a = mul(a, a))
		if(b & 1) ans = mul(ans, a);
	return ans;
}

class Fragile{
public:
	int arb[maxn], con[maxn], dcon[maxn][maxn], f[maxn][maxn], C[maxn][maxn];

	int countGraphs(int N, int K) {
		C[0][0] = 1;
		for(int i = 1; i <= N; C[i++][0] = 1)
			for(int j = 1; j <= i; ++j)
				C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % M;

		for(int i = 1; i <= N; ++i) con[i] = arb[i] = pow(2, i * (i - 1) / 2);
		for(int i = 1; i <= N; ++i)
			for(int j = 1; j < i; ++j)
				add(con[i], M - mul(mul(C[i - 1][j - 1], con[j]), arb[i - j]));
		
		for(int i = 1; i <= N; ++i){
			dcon[i][0] = con[i];
			for(int j = 1; j < i; ++j){
				for(int k = 1; k < i; ++k)
					for(int l = 0; l < j; ++l)
						add(dcon[i][j], mul(mul(dcon[k][l], dcon[i - k][j - 1 - l]), mul(C[i - 1][k - 1], mul(k, i - k))));
				dcon[i][j] = mul(dcon[i][j], pow(j, M - 2));
				add(dcon[i][0], M - dcon[i][j]);
			}
		}

		f[0][0] = 1;
		for(int i = 1; i <= N; ++i)
			for(int j = 0; j < i; ++j)
				for(int k = 1; k <= i; ++k)
					for(int l = 0; l <= j; ++l)
						add(f[i][j], mul(mul(dcon[k][l], f[i - k][j - l]), C[i - 1][k - 1]));
		return f[N][K];
	}
};

// CUT begin
ifstream data("Fragile.sample");

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

template <typename T>
string to_string(T t) {
    stringstream s;
    s << t;
    return s.str();
}

string to_string(string t) {
    return "\"" + t + "\"";
}

bool do_test(int N, int K, int __expected) {
    time_t startClock = clock();
    Fragile *instance = new Fragile();
    int __result = instance->countGraphs(N, K);
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
        int K;
        from_stream(K);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(N, K, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1465395522;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 850 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "Fragile (850 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
