#pragma once
#include "lib/List"

using kirai::List;

#define positive 1
#define negative 0

class BigInteger {
public:
	BigInteger() { _symbol = positive; }
	BigInteger(const char*);
	~BigInteger() = default;
	BigInteger add(const BigInteger&);
	BigInteger sub(const BigInteger&);
	bool symbol()const { return this->_symbol; }
	void setSymbol(bool isPositive) { this->_symbol = isPositive; }
	void setNum(List<short> s) { data = s; }
	void show();
	int cmp(const BigInteger&);
	BigInteger addTwoPositive(const BigInteger&, const BigInteger&);
	BigInteger bigSubSmall(const BigInteger&, const BigInteger&);
	bool _symbol;
	List<short> data;
};
