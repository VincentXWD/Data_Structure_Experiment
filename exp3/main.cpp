/*
━━━━━┒ギリギリ♂ eye！
┓┏┓┏┓┃キリキリ♂ mind！
┛┗┛┗┛┃＼○／
┓┏┓┏┓┃ /
┛┗┛┗┛┃ノ)
┓┏┓┏┓┃
┛┗┛┗┛┃
┓┏┓┏┓┃
┛┗┛┗┛┃
┓┏┓┏┓┃
┛┗┛┗┛┃
┓┏┓┏┓┃
┃┃┃┃┃┃
┻┻┻┻┻┻
*/
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <cstring>
#include <climits>
#include <complex>
#include <fstream>
#include <cassert>
#include <cstdio>
#include <bitset>
#include <vector>
#include <deque>
#include <queue>
#include <stack>
#include <ctime>
#include <set>
#include <map>
#include <cmath>
using namespace std;
#define fr first
#define sc second
#define cl clear
#define BUG puts("here!!!")
#define W(a) while(a--)
#define pb(a) push_back(a)
#define Rint(a) scanf("%d", &a)
#define Rll(a) scanf("%lld", &a)
#define Rs(a) scanf("%s", a)
#define Cin(a) cin >> a
#define FRead() freopen("in", "r", stdin)
#define FWrite() freopen("out", "w", stdout)
#define Rep(i, len) for(int i = 0; i < (len); i++)
#define For(i, a, len) for(int i = (a); i < (len); i++)
#define Cls(a) memset((a), 0, sizeof(a))
#define Clr(a, x) memset((a), (x), sizeof(a))
#define Full(a) memset((a), 0x7f7f, sizeof(a))
#define lp p << 1
#define rp p << 1 | 1
#define pi 3.14159265359
#define RT return
typedef long long LL;
typedef long double LD;
typedef unsigned long long ULL;
typedef pair<int, int> pii;
typedef pair<string, int> psi;
typedef map<string, int> msi;
typedef vector<int> vi;
typedef vector<LL> vl;
typedef vector<vl> vvl;
typedef vector<bool> vb;

const int maxn = 1010;
int dp[maxn][maxn];
int path[maxn][maxn];
bool vis[maxn][maxn];
bool use[maxn];
int n;
string u, v, t;
map<string, int> pos;
string code[maxn];
string ans[maxn];
string tmp[maxn];
map<string, int>::iterator it;
vi ve;
int rt;
bool flag;

void init(string graph) {	
	ifstream fileRead;
	fileRead.open(graph.c_str());
	int u, v, w, t, code;
	string name;
	pos.cl(); Cls(dp); Cls(path); Cls(vis);
	fileRead >> n;
	Rep(i, n) {
		fileRead >> code >> name;
		pos[name] = code;
		::code[code] = name;
	}
	Rep(i, n) {
		Rep(j, n) {
			fileRead >> dp[i][j];
			path[i][j] = j;
		}
	}
	fileRead.close();
}

void floyd() {
	Rep(k, n) {
		Rep(i, n) {
			Rep(j, n) {
				if(dp[i][j] > dp[i][k] + dp[k][j]) {
					dp[i][j] = dp[i][k] + dp[k][j];
					path[i][j] = path[i][k];
				}
			}
		}
	}
	// Rep(i, n) {
	// 	Rep(j, n) {
	// 		printf("%3d ", dp[i][j]);
	// 	}
	// 	printf("\n");
	// }
}

void dfs(int u, int cnt) {
	if(flag) return;
	if(cnt >= n) return;
	if(cnt == n - 1) {
		Rep(i, ve.size()) {
			cout << code[ve[i]] << " ";
		}
		flag = 1;
		return;
	}
	Rep(v, n) {
		if(!use[v]) {
			use[v] = 1;
			ve.pb(v);
			dfs(v, cnt+1);
			use[v] = 0;
		}
	}
}

int main() {
	int u, v, w, t, code;
	init(string("in"));
	floyd();
	int cmd;
	cout << "欢迎使用公园导航，目前公园内有：" << endl;
	for(it = pos.begin(); it != pos.end(); it++) {
		cout << it->first << " ";
	}
	cout << endl << "共计" << n << "个地方。您可以输入：" << endl;
	cout << "[1 起点 终点] 从起点走到终点，查询最佳方案和行走距离。" << endl;
	cout << "[2 起点] 输出环游公园的一条路径。" << endl << endl;
	while(1) {
		cout << "请输入 : ";
		cin >> cmd;
		if(cmd == 1) {
			int a = 0, b = 0;
			cin >> ::u >> ::v;
			for(it = pos.begin(); it != pos.end(); it++) {
				if(it->first == ::u) a++;
				if(it->first == ::v) b++;
			}
			if(a + b != 2) {
				cout << "对不起，您的输入有误。请重试！" << endl;
				continue;
			}
			u = pos[::u]; v = pos[::v];
			t = u; ::t = ::u;
			cout << "最佳路径：";
			cout << ::code[pos[::u]];
			while(t != v) {
				t = path[t][v];
				::t = ::code[t];
				cout << " --> " << ::code[pos[::t]];
			}
			cout << endl;
			cout << "总计距离 ：" << dp[u][v] << "百米" << endl;
		}
		else if(cmd == 2) {
			Cls(use); flag = 0; ve.cl();
			cin >>::u;
			cout << ::u << " ";
			rt = pos[::u];
			use[rt] = 1;
			dfs(rt, 1);
			cout << ::u << endl;
		}
		else cout << "对不起，您的输入有误。请重试！" << endl;
	}
	RT 0;
}