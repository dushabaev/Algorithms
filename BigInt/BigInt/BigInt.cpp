#include "BigInt.h"
#include <functional>
#include <cctype>
#include <iterator>

// Helpers
//typename T::value_type
template<typename T, typename Func>
bool comp(T x, T y, Func proof_f) {
	auto ib = x.begin();
	auto jb = y.begin();

	auto i = x.end()-1;
	auto j = y.end()-1;

	while (i != ib && j != jb && *i == *j) {
		--i; --j;
	}
	return proof_f(*i, *j);
	/*size_t len = x.size();
	size_t i = 0;
	while (i < len-1 && x[i] == y[i])
		++i;
	return f(x[i], y[i]);*/
}

Ratio compare(const BigInt& left, const BigInt& right) {
	if (
		left.sign == positive && right.sign == negative &&
		left.size() > right.size() && left.sign == positive &&
		left.size() < right.size() && left.sign == negative && right.sign == positive
		)
		return Ratio::greater;

	else if (
		left.sign == negative && right.sign == positive &&
		left.size() > right.size() && left.sign == negative &&
		left.size() < right.size() && left.sign == positive && right.sign == negative
		)
		return Ratio::less;
	return Ratio::undefined;
}

// Constructors

// TODO: Improve string constructor
BigInt::BigInt(const string & num) {
	auto beg = num.begin();
	int is_dig = isdigit(*beg);
	sign = is_dig || *beg == '+' ? positive : negative;
	if (is_dig)
		++beg;
	for (auto i = beg; i != num.end(); i++) {
		number.emplace_back(int{*i}+'0');
	}
}

// Destructure

BigInt::~BigInt() {
}

// Assignment operators

BigInt & BigInt::operator=(const BigInt & other) {
	if (this != &other) {
		this->number = other.number;
		this->sign = other.sign;
	}
	return *this;
}

BigInt & BigInt::operator=(BigInt && other) {
	if (this != &other) {
		this->number = move(other.number);
		this->sign = other.sign;
	}
	return *this;
}

// Binary operators

BigInt operator*(BigInt left, const BigInt& right){
	return left *= right;
}

BigInt operator+(BigInt left, const BigInt & right) {
	return left += right;
}

BigInt operator-(BigInt left, const BigInt & right) {
	return left -= right;
}

BigInt BigInt::operator+=(const BigInt & right) {
	return add(right);
}

BigInt& BigInt::operator-=(const BigInt & right) {
	return *this;
}

BigInt& BigInt::operator*=(const BigInt & right) {
	return *this;
}

// Unary operators

const BigInt operator+(const BigInt& arg) {
	return arg.number;
}
const BigInt operator-(const BigInt& arg) {
	return BigInt(arg.number, !arg.sign);
}


//Ratio operators

bool operator<(const BigInt & left, const BigInt & right) {
	switch (compare(left, right)) {
	case Ratio::greater:
		return false;
	case Ratio::less:
		return true;
	default:
		if (left.sign == negative)
			return comp(left, right, greater<Elem>());
		return comp(left, right, less<Elem>());
	}
}

bool operator>(const BigInt & left, const BigInt & right) {
	switch (compare(left, right)) {
	case Ratio::greater:
		return true;
	case Ratio::less:
		return false;
	default:
		if (left.sign == positive)
			return comp(left, right, greater<Elem>());
		return comp(left, right, less<Elem>());
	}
}

bool operator==(const BigInt & left, const BigInt & right) {
	if (left.size() != right.size() || left.sign != right.sign)
		return false;
	return comp(left, right, equal_to<Elem>());
}

bool operator!=(const BigInt & left, const BigInt & right) {
	return !(left == right);
}

bool operator<=(const BigInt & left, const BigInt & right) {
	return !(left > right);
}

bool operator>=(const BigInt & left, const BigInt & right) {
	return !(left < right);
}


// I/O operators

ostream& operator<<(ostream& os, BigInt& val){
	if (val.sign == negative)
		os << '-';

	for (int i = val.size() - 1; i >= 0; i--)
		os << val[i];

	return os;
}

istream& operator>>(istream& is, BigInt& val){
	// Skip spaces
	char t = ' ';
	while (isspace(t))
		is >> t;

	// check sign
	if (isdigit(t))
		val.number.push_front(t-'0');
	else
		val.sign = (t == '+' ? positive : negative);

	// read rest number
	for (char ch = is.get(); ch != '\n'; is.get(ch)) {
		val.number.push_front(ch-'0');
	}
	return is;
}

// Member-helpers

void role(Number& num, size_t i){
	num[i] %= 10;
	if (i == num.size() - 1)
		num.push_back(1);
	else num[i + 1] += 1;
}

BigInt BigInt::add(const BigInt& right){
	unsigned i{}, j{};

	// push zero elements to make diff <= 0
	long int diff = right.size() - size();
	for (long k = 0; k < diff; k++)
		number.push_back(0);
	
	do {
		number[i] += right[j];

		if (number[i] > 9)
			role(number, i);
		
		++i; ++j;

	} while (j != right.size());
	
	// Go deeper
	for (; i < size() && number[i] > 9; ++i)
		role(number, i);
	
	return *this;
}

BigInt BigInt::sub(const BigInt& right, bool saveSign){
	return *this;
}