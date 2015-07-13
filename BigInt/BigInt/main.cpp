#include "BigInt.h"
#include <iostream>
#include <vector>
#include <functional>
using namespace std;

int main() {
	auto f = not_equal_to<int>();
	cout << boolalpha << f(0, 123);
	return 0;
}