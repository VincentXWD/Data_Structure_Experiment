#include "Solve.h"

using namespace std;

void Solve::input(string cmd) {
	string A, B;
	this->cmd.clear();
	A.clear(), B.clear();
	this->cmd = cmd;
	bool sa = positive, sb = positive;
	bool s = positive;
	int len = this->cmd.length();
	if (this->cmd[0] == '-') sa = negative;
	else sa = positive;
	bool flag = 0;	//判断遇到的是否是第一个“负号”
	for (int i = 0; i < len; i++) {
		if (i == 0 && (this->cmd[i] == '+' || this->cmd[i] == '-')) continue;
		if (this->cmd[i] == ' ') continue;
		if (!flag && (this->cmd[i] == '+' || this->cmd[i] == '-')) {
			flag = 1;
			if (this->cmd[i] == '+') s = positive;
			else s = negative;
			continue;	
		}
		if (!flag) {
			if (this->cmd[i] != '+' || this->cmd[i] != '-')
				A += this->cmd[i];
		}
		else {
			if (this->cmd[i] == '-') {
				sb = negative;
				continue;
			}
			B += this->cmd[i];
		}
	}
	string tmp;

	List<short> nums1, nums2;
	short num;
	tmp.clear();
	len = A.length();
	for (int i = 0; i < len; i++) {
		if (A[i] != ',') tmp += A[i];
		if (A[i] == ',') {
			num = atoi(tmp.c_str());
			tmp.clear();
			nums1.push_back(num);
		}
	}
	// 处理A
	num = atoi(tmp.c_str());
	nums1.push_back(num);
	len = nums1.size();
	for (int i = len - 1; i >= 0; i--) {
		this->A.data.push_back(nums1.get(i));
	}
	this->A.setSymbol(sa);

	flag = 0;
	len = B.length();
	tmp.clear();
	for (int i = 0; i < len; i++) {
		if (B[i] != ',') tmp += B[i];
		if (B[i] == ',') {
			num = atoi(tmp.c_str());
			tmp.clear();
			nums2.push_back(num);
		}
	}

	// 处理B
	num = atoi(tmp.c_str());
	nums2.push_back(num);
	len = nums2.size();
	for (int i = len - 1; i >= 0; i--) {
		this->B.data.push_back(nums2.get(i));
	}
	this->B.setSymbol(sb);

	this->symbol = (s == positive ? '+' : '-');
	
	//cout << (sa == positive ? "+" : "-") << A << 
	//	" " << (s == positive ? "+" : "-") << 
	//	" " << (sb == positive ? "+" : "-") << B << endl;
}

void Solve::calc() {
	if (symbol == '+') this->S = this->A.add(this->B);
	if (symbol == '-') this->S = this->A.sub(this->B);
}

void Solve::output() {
	this->calc();
	S.show();
	this->A.data.clear();
	this->B.data.clear();
	this->S.data.clear();
}
