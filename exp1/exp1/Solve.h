#pragma once
#include <string>
#include "BigInteger.h"
#include <string>
#include <iostream>

using namespace std;

class Solve {
public:
	Solve() = default;
	Solve(string c) : cmd(c) {}
	~Solve() = default;
	void input(string);
	void output();
private:
	void calc();
	char symbol;
	string cmd;
	BigInteger A, B, S;
};

