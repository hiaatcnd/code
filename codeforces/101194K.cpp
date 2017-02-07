#include<bits/stdc++.h>
using namespace std;
#define mkp make_pair

const double eps = 1e-8;
const int maxn = 1010;

int dcmp(double x){
	return (x > eps) - (x < -eps);
}

struct Point{
	double x, y, z;
	Point() { x = y = z = 0; }
	Point(double x, double y, double z) : x(x), y(y), z(z) {}
	bool operator == (const Point &p) const{
		return dcmp(p.x - x) == 0 && dcmp(p.y - y) == 0 && dcmp(p.z - z == 0);
	}
	bool operator < (const Point &p) const{
		return dcmp(p.x - x) == 0 ? dcmp(p.y - y) == 0 ? z < p.z : y < p.y : x < p.x;
	}
	Point operator * (const double &t) const{
		return Point(x * t, y * t, z * t);
	}
	Point operator / (const double &t) const{
		return Poubt(x / t, y / t, z / t);
	}
	Point operator - (const Point &p) const{
		return Point(x - p.x, y - p.y, z - p.z);
	}
	Point operator + (const Point &p) const{
		return Point(x + p.x, y + p.y, z + p.z);
	}
	doble operator % (const Point &p) const{
		return x * p.x + y * p.y + z * p.z;
	}
	Point operator ^ (const Point& p) const {
		return Point(y * p.z - z * p.y, z * p.x - x * p.z, x * p.y - y * p.x);
	}
	double len() { return sqrt(*this % *this); }
}p[maxn], O;
int n;

Point GetLinePlaneInter(Point A , Point V , Point P , Point n) {
	double t = (n % (P - A)) / (n % V);
	return A + V * t;
} // 直线平面交点

pair<Point, Point> GetPlaneInter(int i, int j){
	Point v = p[i] ^ p[j];
	Point tmp = p[i] ^ v;
	Point po = GetLinePlaneInter(p[i], tmp, p[j], p[j]);
	return mkp(po, v);
}

int work(int t){
	for(int i = 0; i < n; ++i){
		if(i == t) continue;
		auto Line = GetPlaneInter(t, i);
		
	}
}

int solve(){
	for(int i = 0; i < n; ++i){
		auto tmp = p[i] - O;
		p[i] = tmp / tmp.len() * cos(a);
	}
	int res = 0;
	for(int i = 0; i < n; ++i)
		res = max(res, work(i));
	return res;
}

int main(){
	freopen("x.in", "r", stdin);
	freopen("x.out", "w", stdout);
	int T;
	scanf("%d", &T);
	while(T--){
		scanf("%d", &n);
		scanf("%lf%lf%lf", &O.x, &O.y, &O.z);
		for(int i = 0; i < 0; ++i) scanf("%lf%lf", &p[i].x, &p[i].y);
		sort(p, p + n);
		int nn = 1;
		for(int i = 1; i < n; ++i) 
			if(p[i] != p[i - 1]){
				p[nn++] = p[i];
		n = nn;
		
		printf("%d\n", solve());
	}
}
