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
#define M 1000000000

const int maxn = 300100;

class TreeSums{
public:
	int size[maxn], par[maxn], L[maxn], cen[maxn];
	ll ans[maxn], len[maxn], dp[maxn], res;
	vector<int> g[maxn];

	void dfs(int u){
		dp[u] += L[u] + dp[par[u]];
		size[u] = 1;
		len[u] = ans[u] = 0;
		auto max_son = mkp(0, -1);
		for(auto v : g[u]){
			dfs(v);
			size[u] += size[v];
			len[u] += (ll)L[v] * size[v] + len[v];
			max_son = max(max_son, mkp(size[v], v));
		}
		if(!max_son.fi) return(void)(cen[u] = u);
		int p = max_son.se, v = cen[p];
		ans[u] = ans[p] + len[u] - (len[p] + (ll)size[p] * L[p]);
		ans[u] -= (ll)(dp[u] - dp[v]) * (size[u] - size[p]);
		while(v != u){
			int delta = size[u] - 2 * size[v];
			if(delta <= 0) break;
			ans[u] -= (ll)delta * L[v];
			v = par[v];
		}
		cen[u] = v;
		res ^= ans[u];
	}

	long long findSums(int N, int seed, int C, int D) {
		int n = N;
		ll cur = seed;
		for(int i = 1; i < n; ++i){
			cur = (cur * C + D) % M;
			par[i] = cur % i;
			cur = (cur * C + D) % M;
			L[i] = cur % 1000000;
			g[par[i]].pb(i);
		}
		res = 0;
		dfs(0);
		return res;
	}
};

// CUT begin
ifstream data("TreeSums.sample");

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

bool do_test(int N, int seed, int C, int D, long long __expected) {
    time_t startClock = clock();
    TreeSums *instance = new TreeSums();
    long long __result = instance->findSums(N, seed, C, D);
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
        int seed;
        from_stream(seed);
        int C;
        from_stream(C);
        int D;
        from_stream(D);
        next_line();
        long long __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(N, seed, C, D, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1465571433;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 900 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "TreeSums (900 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
