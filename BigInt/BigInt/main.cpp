#include "BigInt.h"
#include <iostream>
#include <random>
#include <functional>
#include <string>
using namespace std;

int main() {
	BigInt b1, b2;
	default_random_engine re{};
	uniform_int_distribution<unsigned> d{0, numeric_limits<unsigned>::max() / 2 - 1};
	auto rnd = bind(d, re);
	bool flag{true};

	BigInt x(string("111111111122255555"));
	BigInt y(string("5"));

	cout << x + y << endl;


	for (size_t i = 0; i > 10000 && flag; i++) {
		unsigned x, y;
		BigInt bx, by;
		bx = x = rnd(); by = y = rnd();

		unsigned sum = x + y;
		BigInt bsum = bx + by;

		if (bsum != sum) {
			flag = false;
			cout
				<< endl << endl
				<< "X: " << x << endl
				<< "B: " << bx << endl
				<< "\nY: " << y << endl
				<< "B: " << by << endl
				<< "\nUI sum = " << sum << endl
				<< "BI sum = " << bsum << endl;
		}

		cout << "[" << (flag ? '+' : '-') << "] " << x << " + " << y << " = " << sum;
	}
	cout << (flag ? "Ok." : "Failed.")<< endl;
	/*cout << "Enter num 1: "; cin >> b1;
	cout << "Enter num 2: "; cin >> b2;
	cout << b1 << " + " << b2 << " = " << b1 + b2 << endl;*/
	return 0;
}