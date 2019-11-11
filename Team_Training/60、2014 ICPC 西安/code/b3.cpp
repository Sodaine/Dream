#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define de(x) cout << #x << " = " << x << endl
#define dd(x) cout << #x << " = " << x << " "
#define endl '\n'
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
#define pw(x) (1ll << (x))
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int N = 22;

int n = 5, m = 6;
char tmp[] = "RDLU";
int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};
char s[N][N], op[N], a[N][N];
int com, len, ansx, ansy, cnt;
char ansop[N];
bool vis[N][N];
int pre[N * N], id[N][N];

int top;
char savop[202020][11];
int ttx[202020], tty[202020], tlen[202020];

inline int find(int x) {
	return x == pre[x] ? x : pre[x] = find(pre[x]);
}
inline void join(int x, int y) { pre[find(x)] = find(y); }
int up[N];
inline void calc(pii &ans) {
	rep(j, 0, m) {
		up[j] = 0;
		per(i, 0, n) {
			if(a[i][j] == ' ') {
				up[j] = i + 1;
				break;
			}
			pre[id[i][j]] = id[i][j];
			vis[i][j] = 0;
		}
	}
	rep(j, 0, m) {
		per(i, up[j] + 1, n - 1) {
			if(a[i][j] == a[i - 1][j] && a[i][j] == a[i + 1][j]) {
				join(id[i - 1][j], id[i][j]);
				join(id[i + 1][j], id[i][j]);
				vis[i - 1][j] = vis[i][j] = vis[i + 1][j] = 1;
			}
		}
	}
	rep(j, 1, m - 1) {
		per(i, up[j], n) {
			if(a[i][j] == a[i][j - 1] && a[i][j] == a[i][j + 1]) {
				join(id[i][j - 1], id[i][j]);
				join(id[i][j + 1], id[i][j]);
				vis[i][j - 1] = vis[i][j] = vis[i][j + 1] = 1;
			}
		}
	}
	rep(j, 1, m) {
		per(i, up[j], n) if(vis[i][j] && vis[i][j - 1] && a[i][j] == a[i][j - 1]) join(id[i][j], id[i][j - 1]);
	}
	rep(j, 0, m) {
		per(i, up[j] + 1, n) if(vis[i][j] && vis[i - 1][j] && a[i][j] == a[i - 1][j]) join(id[i][j], id[i - 1][j]);
	}
	int com = 0, cnt = 0;
	rep(j, 0, m) {
		per(i, up[j], n) {
			if(vis[i][j]) {
				++cnt;
				if(id[i][j] == find(id[i][j])) ++com;
			}
		}
	}
	//rep(i, 0, n) rep(j, 0, m) if(vis[i][j]) a[i][j] = ' ';
	ans = mp(com, cnt);
}

inline void gao() {
	rep(j, 0, m) {
		int c = n;
		per(i, up[j], n) {
			if(!vis[i][j]) a[--c][j] = a[i][j];
		}
		if(c) {
			rep(i, up[j], c) a[i][j] = ' ';
		}
	}
}

inline bool check0(int tco, int tcnt, int dep) {
	if(com != tco) return com < tco;
	if(cnt != tcnt) return cnt < tcnt;
	return len > dep;
}
const int P = 1e9 + 7;
struct Str {
	static const int N = 44;
	int B[N], ha, ba;
	Str(int ba) : ba(ba) {
		B[0] = 1;
		rep(i, 1, N) B[i] = mul(B[i - 1], ba);
	}
	int upd(int a, int b) {
		if((a += b) >= P) a -= P;
		return a < 0 ? a + P : a;
	}
	int mul(int a, int b) { return 1ll * a * b % P; }
	int geth() {
		ha = 0;
		rep(i, 0, n) rep(j, 0, m) {
			ha = (ha * 1ll * ba + s[i][j]) % P;
		}
		return ha;
	}
}ha1(233), ha2(241);
unordered_map<ll, int> dp;
int tot;
inline void check(int x, int y, int dep) {
	int tco = 0, tcnt = 0;
	rep(i, 0, n) rep(j, 0, m) a[i][j] = s[i][j];
	int xx = x, yy = y;
	rep(i, 0, dep) {
		int d = 0;
		rep(j, 0, 4) if(op[i] == tmp[j]) { d = j; break; }
		int nx = xx + dx[d], ny = yy + dy[d];
		swap(a[xx][yy], a[nx][ny]);
		xx = nx, yy = ny;
	}
	//rep(i, 0, n) a[i][m] = '\0', de(a[i]); cout << endl;
	while(1) {
		pii t; calc(t);
		tco += t.fi, tcnt += t.se;
	//	dd(t.fi), de(t.se);
		if(!t.fi) break;
	//	rep(i, 0, n) a[i][m] = '\0', de(a[i]); cout << endl;
		gao();
	//	rep(i, 0, n) a[i][m] = '\0', de(a[i]); cout << endl;
	}
	if(check0(tco, tcnt, dep)) {
		com = tco, len = dep, ansx = x, ansy = y, cnt = tcnt;
		rep(i, 0, dep) ansop[i] = op[i];
	}
}
void sav(int x, int y, int dep) {
	ll val = ha1.geth() * 1ll * P + ha2.geth();
	if(dp.count(val)) {
		int i = dp[val];
		if(tlen[i] > dep) {
			tlen[i] = dep;
			ttx[i] = x;
			tty[i] = y;
			rep(j, 0, dep) savop[i][j] = op[j];
		}
	} else {
		int i = ++top;
		tlen[i] = dep;
		ttx[i] = x;
		tty[i] = y;
		rep(j, 0, dep) savop[i][j] = op[j];
		dp[val] = i;
	}
}
int tx, ty;
void dfs(int x, int y, int dep) {
	if(dep) sav(tx, ty, dep);
	if(dep == 9) return ;
	rep(i, 0, 4) {
		int nx = x + dx[i], ny = y + dy[i];
		if(nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
		swap(s[x][y], s[nx][ny]);
		op[dep] = tmp[i];
		dfs(nx, ny, dep + 1);
		swap(s[x][y], s[nx][ny]);
	}
}
void init() {
	rep(i, 0, n) rep(j, 0, m) s[i][j] = id[i][j] + 1;
	rep(i, 0, n) rep(j, 0, m) tx = i, ty = j, dfs(i, j, 0);
}
void solve() {
	com = cnt = -1; len = 10;
	rep(i, 0, n) cin >> s[i];//, de(s[i]); cout << endl;
	rep(i, 1, top + 1) {
		rep(j, 0, tlen[i]) op[j] = savop[i][j];
		op[tlen[i]] = '\0';
	//	if(strcmp(op, "LDDLLDRDL") == 0)
		check(ttx[i], tty[i], tlen[i]);
	}
//	++top; tlen[top] = 0; ttx[top] = tty[top] = 0;
	cout << "Combo:" << com << " Length:" << len << endl;
	cout << ansx + 1 << " " << ansy + 1 << endl;
	ansop[len] = '\0';
	cout << ansop << endl;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	rep(i, 0, n) rep(j, 0, m) id[i][j] = i * m + j;
	init();
	int T; cin >> T;
	rep(i, 1, T + 1) {
		cout << "Case #" << i << ":" << endl;
		solve();
	}
	return 0;
}
