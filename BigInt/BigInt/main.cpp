#include "BigInt.h"
#include <iostream>
#include <random>
#include <functional>
#include <string>

using namespace std;
int main() {
	
	//bool flag{true};
	//default_random_engine re{};
	//uniform_int_distribution<long long> d{numeric_limits<int>::min()/2, numeric_limits<int>::max()/2};
	//auto rnd = bind(d, re);
	////cout << BigInt("-1")*BigInt("5") << endl;
	//for (size_t i = 0; i < 10000 && flag; i++) {
	//	long long x, y;
	//	BigInt bx, by;
	//	bx = x = rnd();
	//	by = y = rnd();
	//	long long mult = x * y;
	//	BigInt bmult(bx * by);

	//	cout << "[" << (flag ? '+' : '-') << "] " << x << " * " << y << " = " << bmult << endl;


	//	if (bmult != mult) {
	//		flag = false;
	//		cout
	//			<< endl << endl
	//			<< "X: " << x << endl
	//			<< "B: " << bx << endl
	//			<< "\nY: " << y << endl
	//			<< "B: " << by << endl
	//			<< "\nUI mult = " << mult << endl
	//			<< "BI mult = " << bmult << endl;
	//	}

	//}
	//cout << (flag ? "Ok." : "Failed.")<< endl;
	BigInt
		b1,
		b2;
		/*b1("1685287499328328297814655639278583667919355849391453456921116729"),
		b2("7114192848577754587969744626558571536728983167954552999895348492"),*/
		//b3("2205647016448403");
	cout << "Enter num 1: "; cin >> b1;
	cout << "Enter num 2: "; cin >> b2;
	cout << "Enter value: "; cin >> value;
	cout
		<< "[1]: " << b1 << endl
		<< "[2]: " << b2 << endl << endl;
	cout << b1 << "\n*\n" << b2 << "\n=\n" << b1 * b2 << endl;
	//cout << endl << b3 << endl;
	cout << "\nValue: " << value << "\nCounter: " << counter << endl;
	//cout << b1 << " + " << b2 << " = " << b1 + b2 << endl;
	//cout << b1 << " - " << b2 << " = " << b1 - b2 << endl;
	return 0;
}