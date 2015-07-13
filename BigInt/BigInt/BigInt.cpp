#include "BigInt.h"
#include <functional>
#include <cctype>

template<typename T, typename Proof_function>
bool comp(T x, T y, Proof_function f) {
	size_t len = x.size();
	size_t i = 0;
	while (i < len-1 && x[i] == y[i])
		++i;
	return f(x[i], y[i]);
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

BigInt::BigInt(int num) {
	sign = num < 0 ? negative : positive;
	number = parse_int(num);
}

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

BigInt::~BigInt() {
}


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

// TODO: Implement operators

BigInt& BigInt::operator+=(const BigInt & right) {
	return *this;
}

BigInt& BigInt::operator-=(const BigInt & right) {
	return *this;
}

BigInt& BigInt::operator*=(const BigInt & right) {
	return *this;
}

const BigInt operator+(const BigInt& arg) {
	return arg.number;
}
const BigInt operator-(const BigInt& arg) {
	return BigInt(arg.number, !arg.sign);
}

BigInt operator+(BigInt left, const BigInt & right) {
	return left += right;
}
BigInt operator-(BigInt left, const BigInt & right) {
	return left -= right;
}

bool operator<(const BigInt & left, const BigInt & right) {
	switch (compare(left, right)) {
	case Ratio::greater:
		return false;
	case Ratio::less:
		return true;
	case Ratio::undefined:
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
	case Ratio::undefined:
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


Number BigInt::parse_int(int num) {
	Number n;
	while (num) {
		int i = num % 10;
		n.emplace_back(i);
		num /= 10;
	}
	return n;
}