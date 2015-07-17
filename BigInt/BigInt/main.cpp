#include "BigInt.h"
#include <iostream>
#include <random>
#include <functional>
#include <string>
using namespace std;

int main() {
	
	/*bool flag{true};
	for (size_t i = 0; i > 10000 && flag; i++) {
		default_random_engine re{};
		uniform_int_distribution<long long> d{numeric_limits<int>::min(), numeric_limits<int>::max()};
		auto rnd = bind(d, re);
		long long x, y;
		BigInt bx, by;
		bx = x = rnd();
		by = y = rnd();
		long long sub = x - y;
		cout << "[" << (flag ? '+' : '-') << "] " << x << " - " << y << " = " << sub << endl;

		BigInt bsub(bx - by);

		if (bsub != sub) {
			flag = false;
			cout
				<< endl << endl
				<< "X: " << x << endl
				<< "B: " << bx << endl
				<< "\nY: " << y << endl
				<< "B: " << by << endl
				<< "\nUI sub = " << sub << endl
				<< "BI sub = " << bsub << endl;
		}

	}
	cout << (flag ? "Ok." : "Failed.")<< endl;*/
	BigInt
		b1("-2999458865415082029"),
		b2("-1717806038993388682");
	//cout << "Enter num 1: "; cin >> b1;
	//cout << "Enter num 2: "; cin >> b2;
	cout << b1 << " + " << b2 << " = " << b1 + b2 << endl;
	cout << b1 << " - " << b2 << " = " << b1 - b2 << endl;
	return 0;
}