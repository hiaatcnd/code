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

class ApplesAndOrangesEasy{
public:
	int apple[2016], cnt[2016];

	int maximumApples(int N, int K, vector<int> info) {
		memset(apple, 0, sizeof(apple));
		memset(cnt, 0, sizeof(cnt));
		for(auto v : info) apple[v] = 1;
		for(int i = 1; i <= N; ++i)
			for(int j = i; j >= 1 && i - j < K; --j)
				cnt[i] += apple[j];
		for(int i = N; i >= 1; --i){
			if(apple[i]) continue;
			bool flag = 1;
			for(int j = i; j <= N && j - i < K; ++j)
				if(cnt[j] >= K / 2) flag = 0;
			if(flag){
				apple[i] = 1;
				for(int j = i; j <= N && j - i < K; ++j)
					cnt[j]++;
			}
		}
		int ans = 0;
		for(int i = 1; i <= N; ++i) ans += apple[i];
		return ans;
	}
};

// CUT begin
ifstream data("ApplesAndOrangesEasy.sample");

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

bool do_test(int N, int K, vector<int> info, int __expected) {
    time_t startClock = clock();
    ApplesAndOrangesEasy *instance = new ApplesAndOrangesEasy();
    int __result = instance->maximumApples(N, K, info);
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
        vector<int> info;
        from_stream(info);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(N, K, info, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1467980919;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 250 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "ApplesAndOrangesEasy (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
