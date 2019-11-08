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
#define pw(x) (1ll << (x))
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
typedef long long ll;
typedef double db;
typedef vector<int> vi;
typedef pair<int, int> pii;

bool ok;
int n, m, k;
int cnt[33], ans[33][33];

void dfs(int x, int y) {
	//if (x == n + 1 && y == 1) de(233);
	if(ok || (x == n + 1 && y == 1)) return ok = 1, void();
	int nx = x, ny = y + 1;
	if(ny > m) nx++, ny = 1;
	rep(c, 1, k + 1) if(cnt[c] && c != ans[x][y - 1] && c != ans[x - 1][y]) {
		--cnt[c];
		ans[x][y] = c;
		dfs(nx, ny);
		++cnt[c];
		if(ok) break;
	}
}

bool dp[33];

bool solve() {
	n = m = 5; k = 0; int tot = n * m;
	while(tot) {
		cnt[++k] = rand() % tot + 1;
		tot -= cnt[k];
	}
	rep(i, 1, k + 1) cout << cnt[i] << " \n"[i == k];

//	cin >> n >> m >> k;
	int ma = 0;
	rep(i, 1, k + 1) //cin >> cnt[i], 
	ma = max(ma, cnt[i]);
	if(ma > (n * m + 1) / 2) return 0;

	memset(dp, 0, sizeof(dp));
	dp[0] = 1;
	rep(i, 1, k + 1) per(j, cnt[i], n * m + 1) dp[j] |= dp[j - cnt[i]];
	int cc = n * m / 2;
	//if(dp[cc] || dp[n * m - cc]) return 1;

	ok = 0; dfs(1, 1);
	return ok;
}

int main() {
	//std::ios::sync_with_stdio(0);
	//std::cin.tie(0);
	int T; cin >> T;
	T = 5000;
	rep(cas, 1, T + 1) {
		cout << "Case #" << cas << ":" << endl;
		if(solve()) {
			cout << "YES" << endl;
			rep(i, 1, n + 1) rep(j, 1, m + 1) cout << ans[i][j] << " \n"[j == m];
		} else {
			cout << "NO" << endl;
		}
	}
	return 0;
}
