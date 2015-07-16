#include "BigInt.h"
#include <iostream>
#include <random>
#include <functional>
#include <string>
using namespace std;

int main() {
	BigInt b1, b2;
	default_random_engine re{};
	uniform_int_distribution<long long> d{numeric_limits<int>::min(), numeric_limits<int>::max()};
	auto rnd = bind(d, re);
	bool flag{true};

	for (size_t i = 0; i < 10000 && flag; i++) {
		long long x, y;
		BigInt bx, by;
		bx = x = rnd(); 
		by = y = rnd();
		long long sum = x + y;
		cout << "[" << (flag ? '+' : '-') << "] " << x << " + " << y << " = " << sum << endl;

		BigInt bsum(bx + by);
		
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

	}
	cout << (flag ? "Ok." : "Failed.")<< endl;
	/*cout << "Enter num 1: "; cin >> b1;
	cout << "Enter num 2: "; cin >> b2;
	cout << b1 << " + " << b2 << " = " << b1 + b2 << endl;*/
	return 0;
}