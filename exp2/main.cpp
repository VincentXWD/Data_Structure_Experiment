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
#define Rll(a) scanf("%I64d", &a)
#define Rs(a) scanf("%s", a)
#define Cin(a) cin >> a
#define FRead() freopen("in", "r", stdin)
#define FWrite() freopen("out", "w", stdout)
#define Rep(i, len) for(int i = 0; i < (len); i++)
#define For(i, a, len) for(int i = (a); i < (len); i++)
#define Cls(a) memset((a), 0, sizeof(a))
#define Clr(a, x) memset((a), (x), sizeof(a))
#define Full(a) memset((a), 0x7f7f, sizeof(a))
#define lrt rt << 1
#define rrt rt << 1 | 1

const int inf = 2147483647;
const int maxh = 100010;
const int maxn = 1000010;

typedef struct Node {
	char c;
	int w;
	Node* l; Node* r;
	Node() { l = NULL; r = NULL; }
	Node(char cc, int tt, Node* ll = NULL, Node* rr = NULL) : c(cc), w(tt), l(ll), r(rr) {}
}Node;

typedef struct Heap {
	Heap() { size = 0; }
	Node heap[maxh];
	int pos, size;
	inline void init() {
		size = pos = 0; Cls(heap);
		heap[0] = Node(0, -inf);
	}
	inline void push(Node x) {
		int i = ++pos;
		for(; heap[i>>1].w > x.w; i>>=1) heap[i] = heap[i>>1];
		heap[i] = x; size++;	
	}
	inline void pop() {
		if(pos == 0) return;
		int child = 1, i = 1;
		Node last = heap[pos--];
		for(; i<<1 <= pos; i=child) {
			child = i<<1;
			if(child != pos && heap[child].w > heap[child+1].w) ++child;
			if(last.w > heap[child].w) heap[i] = heap[child];
			else break;
		}
		heap[i] = last; size--;
	}
	inline Node top() { return heap[1]; }
}Heap;

map<char, string>::iterator it;
map<char, string> ret;
Heap pq;
int n, m, w;
char c[5];

void build() {
	while(pq.size != 1) {
		Node* l = new Node(pq.top()); pq.pop();
		Node* r = new Node(pq.top()); pq.pop();
		pq.push(Node(0, l->w+r->w, l, r));
	}
}

void huffman(Node* rt, string& pfx) {
	string tmp = pfx;
	if(rt->l == NULL) return;
	pfx += "0";
	if(rt->l->l == NULL) ret[rt->l->c] = pfx;
	else huffman(rt->l, pfx);
	pfx = tmp; pfx += "1";
	if(rt->r->r == NULL) ret[rt->r->c] = pfx;
	else huffman(rt->r, pfx);
}

string encoding(string str) {
	string ans = "";
	int len = str.length();
	Rep(i, len) {
		it = ret.find(str[i]);
		assert(it != ret.end());
		ans += it->second;
	}
	return ans;
}

string decoding(string str) {
	string ans = "";
	string tmp = "";
	int len = str.length();
	Rep(i, len) {
		tmp += str[i];
		for(it = ret.begin(); it != ret.end(); it++) {
			if(it->second == tmp) {
				ans += it->first;
				tmp.clear();
				break;
			}
		}
	}
	return ans;
}

int main() {
	FRead();
	printf("Please input n: "); 
	while(~Rint(n)) {
		pq.init(); ret.clear();
		printf("Please input %d character and frequency :\n", n);
		Rep(i, n) {
			Rs(c); Rint(w);
			pq.push(Node(c[0], w));
		}
		build();
		Node rt = pq.top();
		string pfx = "";
		huffman(&rt, pfx);
		for(it = ret.begin(); it != ret.end(); it++) {
			printf("%c %s\n", it->first, it->second.c_str());
		}
		printf("Please input the string that you want to encoding\n");
		string tmp;
		Rint(m);
		W(m) {
			Cin(tmp);
			cout << encoding(tmp) << endl;
		}
		printf("Please input the string that you want to decoding\n");
		Rint(m);
		W(m) {
			Cin(tmp);
			cout << decoding(tmp) << endl;
		}
	}
	return 0;
}
