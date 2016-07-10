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

const int maxn = 1000, maxe = 10000000, oo = 1e9;
int e = 1, inx, vis[maxn], ln[maxn], ht[maxn], l, r, S, T, totflow, sum, SS, TT;
int to[maxe], ne[maxe], he[maxn], cap[maxe];

void link(int x, int y, int v){
	to[++e] = y, ne[e] = he[x], he[x] = e, cap[e] = 0;
	to[++e] = x, ne[e] = he[y], he[y] = e, cap[e] = v;
}

void link(int x, int y, int l, int r){
	if(l < r) link(x, y, r - l);
	sum += l;
	link(SS, y, l), link(x, TT, l);
}

bool bfs(int S, int T){
	for(ln[l = r = 1] = S, vis[S] = ++inx, ht[S] = 1; l <= r; l++)
		for(int j = he[ln[l]]; j; j = ne[j])
			if(vis[to[j]] < inx && cap[j ^ 1]){
				vis[to[j]] = inx, ht[to[j]] = ht[ln[l]] + 1, ln[++r] = to[j];
				if(to[j] == T) return 1;
			}
	return 0;
}

int dfs(int f, int d, int S){
	if(!f || d == S) return f;
	int flow = 0, k;
	for(int j = he[d]; j; j = ne[j])
		if(vis[to[j]] == inx && ht[to[j]] == ht[d] - 1 && (k = dfs(min(f, cap[j]), to[j], S))){
			f -= k, flow += k;
			cap[j] -= k, cap[j ^ 1] += k;
			if(!f) return flow;
		}
	ht[d] = maxn + 1;
	return flow;
}

int dinic(int S, int T){
	int maxflow = 0;
	while(bfs(S, T)) maxflow += dfs(oo, T, S);
	return maxflow;
}

class SRMDiv0Easy{
public:
	int n, m, lq[250], rq[250], base[250], lim[250], edge[250];

	bool check(int d){
		return dinic(SS, TT) == sum;
	}

	int get(int N, vector<int> L, vector<int> R, vector<int> X, vector<int> Y) {
		n = N, m = L.size();
		SS = n + 1, TT = n + 2;
		int l = -1, r = 200 * 1000;
		while(l + 1 < r){
			int d = (l + r) >> 1;
			e = 1; memset(he, 0, sizeof(he));
			sum = 0;
			for(int i = 0; i < m; ++i){
				link(L[i], R[i] + 1, X[i], Y[i]);
			}
			link(n, 0, d, oo);

			if(check(d)) l = d;
			else r = d;
		}
		return l;
	}
};

// CUT begin
ifstream data("SRMDiv0Easy.sample");

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

bool do_test(int N, vector<int> L, vector<int> R, vector<int> X, vector<int> Y, int __expected) {
    time_t startClock = clock();
    SRMDiv0Easy *instance = new SRMDiv0Easy();
    int __result = instance->get(N, L, R, X, Y);
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
        vector<int> L;
        from_stream(L);
        vector<int> R;
        from_stream(R);
        vector<int> X;
        from_stream(X);
        vector<int> Y;
        from_stream(Y);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(N, L, R, X, Y, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1468081212;
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
        cout << "SRMDiv0Easy (900 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
