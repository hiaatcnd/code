//看看会不会爆int!
#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define mkp make_pair
#define fi first
#define se second
#define FOR(i, l, r) for(int i = l; i <= r; i++)
#define ROF(i, r, l) for(int i = r; i >= l; i--)
#define all(a) a.begin(), a.end()
inline int ckmax(int &a, int b) { return a < b ? a = b, 1 : 0; }
inline int ckmin(int &a, int b) { return a > b ? a = b, 1 : 0; }
#define clean(a) memset(a, 0, sizeof(a))

typedef long long ll;
const double pi = acos(-1.0);

struct Comp{
  double x, y;
  Comp(): x(0), y(0) {}
  Comp(double _x, double _y): x(_x), y(_y) {}
  Comp operator + (const Comp &rhs) const {
    return Comp(x + rhs.x, y + rhs.y);
  }
  Comp operator - (const Comp &rhs) const {
    return Comp(x - rhs.x, y - rhs.y);
  }
  Comp operator * (const Comp &rhs) const {
    return Comp(x * rhs.x - y * rhs.y, x * rhs.y + y * rhs.x);
  }
  Comp &operator += (const Comp &rhs) {
    x += rhs.x; y += rhs.y;
    return *this;
  }
  Comp &operator -= (const Comp &rhs) {
    x -= rhs.x; y -= rhs.y;
    return *this;
  }
  Comp conj() const {
    return Comp(x, -y);
  }
};

const int MAXN = 262144;
Comp A[MAXN], X[MAXN], Y[MAXN], Z[MAXN];
int bitrev[MAXN];

void FFT(Comp a[], int n, int o){
	for(int i = 0; i < n; i++) A[bitrev[i]] = a[i];
	for(int s = 0; 1 << s <= n; s++){
		int m = 1 << s;
		double ang = 2 * pi / m * o;
		Comp od = Comp(cos(ang), sin(ang));
		for(int k = 0; k < n; k += m){
			Comp w = Comp(1.0, 0);
			for(int j = 0; j < m / 2; j++){
				Comp t = w * A[k + j + m / 2];
				A[k + j + m / 2] = A[k + j] - t;
				A[k + j] = A[k + j] + t;
				w = w * od;
			}
		}
	}
	for(int i = 0; i < n; i++) a[i] = A[i];
}

void conv(int x[], int n, int y[], int m, ll z[]){
  int l = 0;
  while ((1 << l) < n + m - 1) ++l;
  int s = 1 << l;
  for (int i = 0; i < s; ++i)
    bitrev[i] = bitrev[i >> 1] >> 1 | ((i & 1) << (l - 1));
  for (int i = 0; i < s; ++i){
		X[i] = Comp(i < n ? x[i] : 0, 0);
		Y[i] = Comp(i < m ? y[i] : 0, 0);
  }
  FFT(X, s, 1); FFT(Y, s, 1);
	for(int i = 0; i < s; ++i) Z[i] = X[i] * Y[i];
  FFT(Z, s, -1);
  for (int i = 0; i < s; ++i)
		z[i] = ll(Z[i].x / s + 0.5);
}

const int maxn = 200100;
int n;
int cnt[MAXN], a[maxn];
ll cal[MAXN];

int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) scanf("%d", a + i), cnt[a[i] + 50000]++;
	conv(cnt, 100001, cnt, 100001, cal);

	ll ans = 0;
	for(int i = 50000; i <= 150000; ++i)
		ans += cnt[i - 50000] * cal[i];

	ans -= (ll)cnt[50000] * (cnt[50000] - 1) * 3 + cnt[50000];
	ans -= (ll)(n - cnt[50000]) * cnt[50000] * 2;
	for(int i = 1; i <= n; ++i)
		if(a[i] && abs(a[i]) <= 25000) ans -= cnt[a[i] * 2 + 50000];

	printf("%lld\n", ans);
  return 0;
}
