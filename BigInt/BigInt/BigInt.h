#pragma once
#include <deque>
#include <iostream>
#include <type_traits>

using namespace std;

template<typename C>
using Iter = typename C::iterator;

using Elem = short;
using Number = deque<Elem>;
enum class Ratio { greater, less, undefined };
enum Sign { negative, positive };

inline Sign operator!(const Sign& s) {
	return s == negative ? positive : negative;
}

class BigInt
{
public:

	BigInt() 
		: number{}
		, sign{positive}
	{}
	template<typename T>
	BigInt(const T num);
	BigInt(const string& num) = delete; // Will be improved :3
	BigInt(const Number& num, Sign s=positive)
		: number(num)
		, sign{s}
	{}
	
	BigInt(const BigInt& other)
		: number(other.number)
		, sign{other.sign}
	{}

	BigInt(BigInt&& other)
		: number(move(other.number))
		, sign{other.sign}
	{}
	
	BigInt& operator=(const BigInt& other);
	BigInt& operator=(BigInt&& other);


	~BigInt();

	friend const BigInt operator+(const BigInt& arg);
	friend const BigInt operator-(const BigInt& arg);

	friend BigInt operator+(BigInt left, const BigInt& right);
	friend BigInt operator-(BigInt left, const BigInt& right);

	friend Ratio compare(const BigInt& left, const BigInt& right);

	friend bool operator<(const BigInt& left, const BigInt& right);
	friend bool operator>(const BigInt& left, const BigInt& right);
	friend bool operator==(const BigInt& left, const BigInt& right);
	friend bool operator!=(const BigInt& left, const BigInt& right);
	friend bool operator<=(const BigInt& left, const BigInt& right);
	friend bool operator>=(const BigInt& left, const BigInt& right);

	friend ostream& operator<<(ostream& os, BigInt& val);
	friend istream& operator>>(istream& is, BigInt& val);

	BigInt operator+=(const BigInt& right);
	BigInt& operator-=(const BigInt& right);
	BigInt& operator*=(const BigInt& right);

	Number::const_iterator begin() const { return number.begin(); }
	Number::const_iterator end() const { return number.end(); }

	Number::iterator begin() { return number.begin(); }
	Number::iterator end() { return number.end(); }

	Elem& operator[](size_t index) { return number[index]; }
	const Elem& operator[](size_t index) const { return number[index]; }

	size_t size() const { return number.size(); }

private:
	template<typename T>
	Number parse_numeric(T num);

	// Base operations
	BigInt add(const BigInt& right);
	BigInt sub(const BigInt& right, bool saveSign);
	
	Number number;
	Sign sign;
};

// Template methods

template<typename T>
BigInt::BigInt(const T num) {
	static_assert(is_integral<T>::value, "Required integer type of argument !!");
	sign = num < 0 ? negative : positive;
	number = parse_numeric(num);
}

template<typename T>
Number BigInt::parse_numeric(T num) {
	static_assert(is_integral<T>::value, "Required integer type of argument !!");
	Number n;
	while (num) {
		int i = num % 10;
		n.push_back(i);
		num /= 10;
	}
	return n;
}