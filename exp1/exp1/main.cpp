#pragma warning(disable:4996)
#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
#include "BigInteger.h"
#include "Solve.h"

using namespace std;

int main() {
	//BigInteger A, B;
	//List<short> t, y;
	//t.push_back(1234);
	//t.push_back(1234);
	//t.push_back(1234);
	//y.push_back(5555);
	//y.push_back(5355);
	//y.push_back(555);
	//A.setNum(t);
	//B.setNum(y);
	//A = A.sub(B);
	//A.show();
	char cmd[1024];
	Solve t;
	memset(cmd, 0, sizeof(cmd));
	while (gets(cmd)) {
		t.input(string(cmd));
		memset(cmd, 0, sizeof(cmd));
		t.output();
	}
	return 0;
}