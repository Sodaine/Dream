#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define rep(i, a, b) for(int i=(a); i<(b); i++)
#define per(i, a, b) for(int i=(b)-1; i>=(a); i--)
#define sz(a) (int)a.size()
#define de(a) cout << #a << " = " << a << endl
#define dd(a) cout << #a << " = " << a << " "
#define all(a) a.begin(), a.end()
#define pw(x) (1ll<<(x))
#define endl "\n"
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef double db;

void file_put() {
    freopen("filename.in", "r", stdin);
    freopen("filename.out", "w", stdout);
}

const int N=705;
int n,k; double f[N];

int main() {
	//file_put();
	
	scanf("%d%d",&n,&k);
	rep(i,1,n+1) rep(j,1,701)
		f[j]=((double)j/(j+1)*(f[j]+(j+1.)/2)+(f[j+1]+j)/(j+1.)+(k-1.)*f[j])/k;
	printf("%.12f\n",f[1]*k);
	
	return 0;
}