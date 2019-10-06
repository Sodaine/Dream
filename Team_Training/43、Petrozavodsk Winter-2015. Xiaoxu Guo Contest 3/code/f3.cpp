#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse2")
#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define de(c) cout << #c << " = " << c << endl
#define dd(c) cout << #c << " = " << c << " "
#define endl '\n'
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
#define pw(x) (1ll << (x))
#define R register
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int N = 5e6 + 7, P = 1e9 + 7;
int f[N][11][2], n, m, t1[15], t2[15], t3[15];
char s[N];

inline int add(int a, int b) {
	if ((a += b) >= P) a -= P;
	return a;
}

inline int mul(int a, int b) {
	return 1ll * a * b % P;
}

inline void upd(int &t, int b) {
	t += b;
	if (t >= P) t -= P;
}

int main() {
	//std::ios::sync_with_stdio(0);
	//std::cin.tie(0);
	//cin >> n >> m;
	//n = 5000000, m = 10;
	//cin >> s + 1;
	scanf("%d%d%s", &n, &m, s+1);
	per(i, 1, n+1) {
		R int ls = i << 1, rs = (i << 1) + 1;
		if (ls > n) {
			f[i][0][0] = 1;
			if (s[i] == '0') rep(k, 1, m+1) f[i][k][1] = 1;
		}else if (rs > n) {
			rep(j, 0, m+1) {
				//if (ls >= lim) f[i][j][0] = f[ls][j][1] + (j == 0);
				//else 
					f[i][j][0] = add(f[ls][j][0], f[ls][j][1]);
			}
			if (s[i] == '0') { 
				int t = 0;
				rep(j, 1, m+1) {
					upd(t, f[ls][j-1][0]);
					f[i][j][1] = t;
				}
			}
		}else {
			rep(j, 0, m+1) {
				t1[j] = add(f[ls][j][0], f[ls][j][1]);
				t2[j] = add(f[rs][j][0], f[rs][j][1]);	
			}
			for(int j = 0; j <= m; j++)
				for (int k = 0; j + k <= m; k++)
					upd(f[i][j+k][0], mul(t1[j], t2[k]));
			if (s[i] == '0') {
				int t = 0;
				rep(j, 1, m+1) {
					upd(t, f[ls][j-1][0]);
					t3[j] = t;
				}
				for (int j = 1; j <= m; j++)
					for (int k = 0; j + k <= m; k++)
						upd(f[i][j + k][1], mul(t3[j], f[rs][k][0]));
			}	
		}
	}
	cout << add(f[1][m][1], f[1][m][0]) << endl; 
	return 0; 
}
