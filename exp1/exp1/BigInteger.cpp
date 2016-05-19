#include "BigInteger.h"
#include <cassert>
#include <iostream>
#include <iomanip>

#define positive 1
#define negative 0

int BigInteger::cmp(const BigInteger& A) {
	// 比较两个数的绝对值大小，如果this大返回1，A大返回-1，相等返回0
	int la = this->data.size();
	int lb = A.data.size();
	if (la > lb) return 1;
	if (la < lb) return -1;
	// 长度相等的时候，从高位比到低位
	for (int i = la - 1; i >= 0; i--) {
		if (this->data.get(i) > A.data.get(i)) return 1;
		if (this->data.get(i) < A.data.get(i)) return -1;
	}
	return 0;
}

BigInteger BigInteger::add(const BigInteger& B) {
	assert(!this->data.empty() && !B.data.empty());
	// 拷贝
	BigInteger ta = *this;
	BigInteger tb = B;
	BigInteger ans;

	// 全都是负数到时候，传入参数的时候做相加操作
	if (negative == this->symbol() && negative == B.symbol()) {
		ta.setSymbol(positive); tb.setSymbol(positive);
		ans = addTwoPositive(ta, tb);
		ans.setSymbol(negative);
	}
	// 全都是正数的时候，直接相加
	if (positive == this->symbol() && positive == B.symbol()) {
		ans = addTwoPositive(ta, tb);
		ans.setSymbol(positive);
	}
	// 一正一负的情况，比较一下绝对值大小
	else {
		int flag;
		// A正B负
		if (positive == this->symbol() && negative == B.symbol()) {
			flag = this->cmp(B);
			if (flag == 1) {	//相当于非负数减法
				ta.setSymbol(positive); tb.setSymbol(positive);
				ans = bigSubSmall(ta, tb);
				ans.setSymbol(positive);
			}
			if (flag == 0) {	//直接返回0即可
				ta.setSymbol(positive); tb.setSymbol(positive);
				ans.data.push_back(0);
				ans.setSymbol(positive);
			}
			if (flag == -1) {	//相当于负数的绝对值减正数，结果为负
				ta.setSymbol(positive); tb.setSymbol(positive);
				ans = bigSubSmall(tb, ta);
				ans.setSymbol(negative);
			}
		}
		// A负B正
		if (negative == this->symbol() && positive == B.symbol()) {
			flag = this->cmp(B);
			if (flag == 1) {	//相当于负数的绝对值减正数，结果为负
				ta.setSymbol(positive); tb.setSymbol(positive);
				ans = bigSubSmall(ta, tb);
				ans.setSymbol(negative);
			}
			if (flag == 0) {	//直接返回0即可
				ta.setSymbol(positive); tb.setSymbol(positive);
				ans.data.push_back(0);
				ans.setSymbol(positive);
			}
			if (flag == -1) {	//相当于非负数减法
				ta.setSymbol(positive); tb.setSymbol(positive);
				ans = bigSubSmall(tb, ta);
				ans.setSymbol(positive);
			}
		}
	}
	return ans;
}

BigInteger BigInteger::sub(const BigInteger& B) {
	assert(!this->data.empty() && !B.data.empty());
	// 拷贝
	BigInteger* A = const_cast<BigInteger*>(this);
	BigInteger ta = *this;
	BigInteger tb = B;
	BigInteger ans;
	
	// A正B负，做加法，结果为正
	if (positive == this->symbol() && negative == B.symbol()) {
		ta.setSymbol(positive); tb.setSymbol(positive);
		ans = addTwoPositive(ta, tb);
		ans.setSymbol(positive);
	}
	// A负B正，做加法，结果为负
	if (negative == this->symbol() && positive == B.symbol()) {
		ta.setSymbol(positive); tb.setSymbol(positive);
		ans = addTwoPositive(ta, tb);
		ans.setSymbol(negative);
	}
	else {
		int flag;
		// 两个数都是正
		if (positive == this->symbol() && positive == B.symbol()) {
			flag = this->cmp(B);
			if (flag == 1) {	//相当于大减小，结果为正
				ta.setSymbol(positive); tb.setSymbol(positive);
				ans = bigSubSmall(ta, tb);
				ans.setSymbol(positive);
			}
			if (flag == 0) {	//直接返回0即可
				ta.setSymbol(positive); tb.setSymbol(positive);
				ans.data.push_back(0);
				ans.setSymbol(positive);
			}
			if (flag == -1) {	//相当于小减大，反着减结果为负
				ta.setSymbol(positive); tb.setSymbol(positive);
				ans = bigSubSmall(tb, ta);
				ans.setSymbol(negative);
			}
		}
		//两个数都是负
		if (negative == this->symbol() && negative == B.symbol()) {
			ta.setSymbol(positive); tb.setSymbol(positive);
			flag = this->cmp(B);
			if (flag == 1) {	//相当于大的减小的，结果为负
				ta.setSymbol(positive); tb.setSymbol(positive);
				ans = bigSubSmall(ta, tb);
				ans.setSymbol(negative);
			}
			if (flag == 0) {	//直接返回0即可
				ta.setSymbol(positive); tb.setSymbol(positive);
				ans.data.push_back(0);
				ans.setSymbol(positive);
			}
			if (flag == -1) {	//相当于小的减大的，结果为正
				ta.setSymbol(positive); tb.setSymbol(positive);
				ans = bigSubSmall(tb, ta);
				ans.setSymbol(positive);
			}
		}
	}
	return ans;
}

// A + B 全正
BigInteger BigInteger::addTwoPositive(const BigInteger& A, const BigInteger& B) {
	using namespace std;
	BigInteger ans;
	int la = A.data.size();
	int lb = B.data.size();
	int len = la < lb ? la : lb;
	for (int i = 0; i < len; i++) {
		ans.data.push_back(0);
		ans.data[i] = A.data.get(i) + B.data.get(i);
	}
	for (int i = len; i < la; i++) {
		ans.data.push_back(0);
		ans.data[i] = A.data.get(i);
	}
	for (int i = len; i < lb; i++) {
		ans.data.push_back(0);
		ans.data[i] = A.data.get(i);
	}
	// 处理进位
	len = la > lb ? la : lb;
	bool up = 0;	// 进位标记
	short cur;
	for (int i = 0; i < len; i++) {
		if (up == 1) {
			ans.data[i] += cur;
			up = 0;
		}
		if (ans.data.get(i) >= 10000) {
			cur = ans.data[i] / 10000;
			short tmp = ans.data[i] % 10000;
			ans.data[i] = tmp;
			up = 1;
		}
		else up = 0;
	}
	if (up) {	//最后一位还需要进位
		while (cur) {
			ans.data.push_back(cur);
			cur /= 10000;
		}
	}
	return ans;

}

// A - B (A > B) 全正
BigInteger BigInteger::bigSubSmall(const BigInteger& A, const BigInteger& B) {
	BigInteger ans;
	int la = A.data.size();
	int lb = B.data.size();
	int len = la < lb ? la : lb;
	for (int i = 0; i < len; i++) {
		ans.data.push_back(0);
		ans.data[i] = A.data.get(i) - B.data.get(i);
	}
	for (int i = len; i < la; i++) {
		ans.data.push_back(0);
		ans.data[i] = A.data.get(i);
	}
	len = la > lb ? la : lb;
	// 处理借位
	bool down = 0;
	for (int i = 0; i < len; i++) {
		if (down == 1) {
			ans.data[i] -= 1;
			down = 0;
		}
		if (ans.data[i] < 0) {
			ans.data[i] += 10000;
			down = 1;
		}
		else down = 0;
	}
	return ans;
}

void BigInteger::show() {
	using namespace std;
	int len = data.size();
	if (this->symbol() == negative) {
		cout << "-";
	}
	int flag = 0;
	if (len == 1) {
		cout << data[0] << endl;
		return;
	}
	if (data[len - 1] != 0) {
		flag = 2;
		cout << data[len - 1] << ",";
	}
	if (len == 1) {
		cout << endl;
		return;
	}
	for (int i = len - 2; i > 0; i--) {
		if (data[i] == 0 && !flag) continue;
		if (data[i] > 0) flag = 1;
		if (flag == 1) {
			cout << data[i] << ",";
			flag++;
			continue;
		}
		if (flag == 2) cout << std::setw(4) << std::setfill('0') << data[i] << ",";
	}
	if (flag == 0) cout << data[0] << endl;
	if (flag == 1 || flag == 2) cout << std::setw(4) << std::setfill('0') << data[0] << endl;
}
