#include "BigInteger.h"
#include <cassert>
#include <iostream>
#include <iomanip>

#define positive 1
#define negative 0

int BigInteger::cmp(const BigInteger& A) {
	// �Ƚ��������ľ���ֵ��С�����this�󷵻�1��A�󷵻�-1����ȷ���0
	int la = this->data.size();
	int lb = A.data.size();
	if (la > lb) return 1;
	if (la < lb) return -1;
	// ������ȵ�ʱ�򣬴Ӹ�λ�ȵ���λ
	for (int i = la - 1; i >= 0; i--) {
		if (this->data.get(i) > A.data.get(i)) return 1;
		if (this->data.get(i) < A.data.get(i)) return -1;
	}
	return 0;
}

BigInteger BigInteger::add(const BigInteger& B) {
	assert(!this->data.empty() && !B.data.empty());
	// ����
	BigInteger ta = *this;
	BigInteger tb = B;
	BigInteger ans;

	// ȫ���Ǹ�����ʱ�򣬴��������ʱ������Ӳ���
	if (negative == this->symbol() && negative == B.symbol()) {
		ta.setSymbol(positive); tb.setSymbol(positive);
		ans = addTwoPositive(ta, tb);
		ans.setSymbol(negative);
	}
	// ȫ����������ʱ��ֱ�����
	if (positive == this->symbol() && positive == B.symbol()) {
		ans = addTwoPositive(ta, tb);
		ans.setSymbol(positive);
	}
	// һ��һ����������Ƚ�һ�¾���ֵ��С
	else {
		int flag;
		// A��B��
		if (positive == this->symbol() && negative == B.symbol()) {
			flag = this->cmp(B);
			if (flag == 1) {	//�൱�ڷǸ�������
				ta.setSymbol(positive); tb.setSymbol(positive);
				ans = bigSubSmall(ta, tb);
				ans.setSymbol(positive);
			}
			if (flag == 0) {	//ֱ�ӷ���0����
				ta.setSymbol(positive); tb.setSymbol(positive);
				ans.data.push_back(0);
				ans.setSymbol(positive);
			}
			if (flag == -1) {	//�൱�ڸ����ľ���ֵ�����������Ϊ��
				ta.setSymbol(positive); tb.setSymbol(positive);
				ans = bigSubSmall(tb, ta);
				ans.setSymbol(negative);
			}
		}
		// A��B��
		if (negative == this->symbol() && positive == B.symbol()) {
			flag = this->cmp(B);
			if (flag == 1) {	//�൱�ڸ����ľ���ֵ�����������Ϊ��
				ta.setSymbol(positive); tb.setSymbol(positive);
				ans = bigSubSmall(ta, tb);
				ans.setSymbol(negative);
			}
			if (flag == 0) {	//ֱ�ӷ���0����
				ta.setSymbol(positive); tb.setSymbol(positive);
				ans.data.push_back(0);
				ans.setSymbol(positive);
			}
			if (flag == -1) {	//�൱�ڷǸ�������
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
	// ����
	BigInteger* A = const_cast<BigInteger*>(this);
	BigInteger ta = *this;
	BigInteger tb = B;
	BigInteger ans;
	
	// A��B�������ӷ������Ϊ��
	if (positive == this->symbol() && negative == B.symbol()) {
		ta.setSymbol(positive); tb.setSymbol(positive);
		ans = addTwoPositive(ta, tb);
		ans.setSymbol(positive);
	}
	// A��B�������ӷ������Ϊ��
	if (negative == this->symbol() && positive == B.symbol()) {
		ta.setSymbol(positive); tb.setSymbol(positive);
		ans = addTwoPositive(ta, tb);
		ans.setSymbol(negative);
	}
	else {
		int flag;
		// ������������
		if (positive == this->symbol() && positive == B.symbol()) {
			flag = this->cmp(B);
			if (flag == 1) {	//�൱�ڴ��С�����Ϊ��
				ta.setSymbol(positive); tb.setSymbol(positive);
				ans = bigSubSmall(ta, tb);
				ans.setSymbol(positive);
			}
			if (flag == 0) {	//ֱ�ӷ���0����
				ta.setSymbol(positive); tb.setSymbol(positive);
				ans.data.push_back(0);
				ans.setSymbol(positive);
			}
			if (flag == -1) {	//�൱��С���󣬷��ż����Ϊ��
				ta.setSymbol(positive); tb.setSymbol(positive);
				ans = bigSubSmall(tb, ta);
				ans.setSymbol(negative);
			}
		}
		//���������Ǹ�
		if (negative == this->symbol() && negative == B.symbol()) {
			ta.setSymbol(positive); tb.setSymbol(positive);
			flag = this->cmp(B);
			if (flag == 1) {	//�൱�ڴ�ļ�С�ģ����Ϊ��
				ta.setSymbol(positive); tb.setSymbol(positive);
				ans = bigSubSmall(ta, tb);
				ans.setSymbol(negative);
			}
			if (flag == 0) {	//ֱ�ӷ���0����
				ta.setSymbol(positive); tb.setSymbol(positive);
				ans.data.push_back(0);
				ans.setSymbol(positive);
			}
			if (flag == -1) {	//�൱��С�ļ���ģ����Ϊ��
				ta.setSymbol(positive); tb.setSymbol(positive);
				ans = bigSubSmall(tb, ta);
				ans.setSymbol(positive);
			}
		}
	}
	return ans;
}

// A + B ȫ��
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
	// �����λ
	len = la > lb ? la : lb;
	bool up = 0;	// ��λ���
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
	if (up) {	//���һλ����Ҫ��λ
		while (cur) {
			ans.data.push_back(cur);
			cur /= 10000;
		}
	}
	return ans;

}

// A - B (A > B) ȫ��
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
	// �����λ
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
