#include "DataBase.h"
#include <iostream>
using namespace std;

int main() {
	DataBase d("D:\\alice.txt");
	for (size_t i = 0; i < 2; i++) {
		int x, y;
		cout << "Enter user_x: "; cin >> x;
		cout << "Enter user_y: "; cin >> y;
		--x; --y;
		cout << d.get_inversion(x, y) << endl;
	}
	//system("pause");
	return 0;
}