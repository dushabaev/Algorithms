#include "BigInt.h"
#include <functional>
#include <cctype>
#include <iterator>
#include <memory>

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
}

Ratio compare(const BigInt& left, const BigInt& right) {
	if (
		(left.sign == positive && right.sign == negative) ||
		(left.size() > right.size() && left.sign == positive) ||
		(left.size() < right.size() && right.sign == negative)
		)
		return Ratio::greater;

	if (
		(left.sign == negative && right.sign == positive) ||
		(left.size() < right.size() && left.sign == positive) ||
		(left.size() > right.size() && left.sign == negative)
		)
		return Ratio::less;
	return Ratio::undefined;
}

BigInt abs(const BigInt& arg){
	return arg.sign == positive ? arg : arg.make_opposite();
}

void front_track(Number& num, size_t i){
	num[i] %= 10;
	if (i == num.size() - 1)
		num.push_back(1);
	else num[i + 1] += 1;
}

void back_track(Number& num, size_t i){
	num[i] += 10;
	num[i + 1] -= 1;
}

// Add trail zeros to make left & right sizes equal and even
// Return 1 if left & right sizes are equal to 1
size_t fit(BigInt& left, BigInt& right){
	BigInt *bigger, *smaller;

	auto lsz = left.size();
	auto rsz = right.size();
	
	if (lsz == 1 && rsz == 1)
		return 1;

	if (lsz > rsz)
		bigger = &left, smaller = &right;
	else
		bigger = &right, smaller = &left;
	
	if (bigger->size() % 2)
		bigger->add_trail_zero(1);

	smaller->add_trail_zero(bigger->size() - smaller->size());
	return bigger->size();
}

// Assume that left if bigger
BigInt subtrct(const BigInt& left, const BigInt& right){
	size_t i{}, j{};
	size_t j_len = right.size();
	size_t i_len = left.size();

	// make BigInt with max length
	BigInt res(left);

	do {
		res[i] -= right[j];

		if (res[i] < 0)
			back_track(res.number, i);

		++i; ++j;

	} while (j != j_len);

	// Go deeper
	for (; i < i_len && res[i] < 0; ++i)
		back_track(res.number, i);

	// remove trailing zeros
	while (res.number.back() == 0)
		res.number.pop_back();

	return res;
}

// Constructors

BigInt::BigInt(const string & num) {
	auto beg = num.begin();
	int is_dig = isdigit(*beg);
	sign = is_dig || *beg == '+' ? positive : negative;
	if (!is_dig)
		++beg;
	for (auto i = beg; i != num.end(); i++) 
		number.push_front(*i - '0');
}

BigInt::BigInt(const char* num){
	if (!num)
		throw("BigInt::BigInt(const char* num) => num == nullptr or num == NULL");
	
	if (!isdigit(*num))
		sign = *(num++) == '+' ? positive : negative;

	while (*num)
		number.push_front(*(num++) - '0');
}

// Destructor

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
	return 
		sign == right.sign ? 
			add(right) :
		abs(*this) > abs(right) ?	
			sub(right) :
		subtrct(right, *this);
}

BigInt BigInt::operator-=(const BigInt & right) {
	if (sign != right.sign)
		return add(right);
	if (abs(*this) > abs(right))
		return sub(right);
	else return subtrct(right, *this).change_sign();
}

BigInt BigInt::operator*=(BigInt right) {
	auto sz = fit(*this, right);
	if (sz == 1)
		return *(this->begin())*(*right.begin());

	auto beg = this->begin();
	auto end = this->end();
	auto mid = beg + sz / 2;

	BigInt a(beg, mid, positive);
	BigInt b(mid, end, positive);

	beg = right.begin();
	end = right.end();
	mid = beg + sz / 2;
	
	BigInt c(beg, mid, positive);
	BigInt d(mid, end, positive);

	BigInt sum((a + b)*(c + d));
	a *= c;
	b *= d;

	return a.pow10(sz) + (sum-(a+b)).pow10(sz/2) + b;
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

BigInt BigInt::add(const BigInt& right){
	unsigned i{}, j{};

	// push zero elements to make diff <= 0
	long int diff = right.size() - size();
	for (long k = 0; k < diff; k++)
		number.push_back(0);
	
	do {
		number[i] += right[j];

		if (number[i] > 9)
			front_track(number, i);
		
		++i; ++j;

	} while (j != right.size());
	
	// Go deeper
	for (; i < size() && number[i] > 9; ++i)
		front_track(number, i);
	
	return *this;
}

BigInt BigInt::sub(const BigInt& right){
	unsigned i{}, j{};
	size_t len = right.size();
	// push zero elements to make diff <= 0
	long int diff = len - size();
	for (long k = 0; k < diff; k++)
		number.push_back(0);

	do {
		number[i] -= right[j];

		if (number[i] < 0)
			back_track(number, i);

		++i; ++j;

	} while (j != len);

	// Go deeper
	for (; i < size() && number[i] < 0; ++i)
		back_track(number, i);
	
	// remove trailing zeros
	while (number.back() == 0)
		number.pop_back();

	return *this;
}