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

const int maxn = 110;

class DancingForever{
public:
	int inx, vis[maxn], n, p[maxn], ok[maxn];
	bool a[maxn][maxn], del[maxn];
	vector<int> ans;

	bool find(int x){
		for(int i = 0; i < n; ++i){
			if(a[x][i] == 1 && vis[i] < inx){
				vis[i] = inx;
				if(p[i] == -1 || find(p[i])){
					p[i] = x;
					return 1;
				}
			}
		}
		return 0;
	}

	bool work(){
		memset(p, -1, sizeof(p));
		for(int i = 0; i < n; ++i)
			if(!del[i]){
				inx++;
				find(i);
			}
		bool flag = 1;
		for(int i = 0; i < n; ++i)
			if(p[i] != -1) ok[p[i]] = inx;
		for(int i = 0; i < n; ++i)
			if(!del[i] && ok[i] == inx){
				for(int j = 0; j < n; ++j)
					if(a[i][j] && p[j] == -1){
						del[i] = 1;
						flag = 0;
					}
			}
		if(!flag) return 0;
		else{
			for(int i = 0; i < n; ++i)
				if(p[i] != -1) ans.pb(p[i]), ans.pb(i);
			return 1;
		}
	}
	vector<int> getStablePairs(string x) {
		n = sqrt(x.size() + 0.1);
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < n; ++j)
				a[i][j] = x[i * n + j] == 'Y';
		while(!work());
		return ans;
	}
};

// CUT begin
ifstream data("DancingForever.sample");

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

template <typename T> string to_string(vector<T> ts) {
    stringstream s;
    s << "[ ";
    for (int i = 0; i < ts.size(); ++i) {
        if (i > 0) s << ", ";
        s << to_string(ts[i]);
    }
    s << " ]";
    return s.str();
}

bool do_test(string x, vector<int> __expected) {
    time_t startClock = clock();
    DancingForever *instance = new DancingForever();
    vector<int> __result = instance->getStablePairs(x);
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
        string x;
        from_stream(x);
        next_line();
        vector<int> __answer;
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
        int T = time(NULL) - 1467900168;
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
        cout << "DancingForever (850 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
