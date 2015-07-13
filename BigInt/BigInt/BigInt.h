#pragma once
#include <deque>
#include <valarray>
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
	
	BigInt(const int num);
	BigInt(const string& num);
	BigInt(const Number& num, Sign s=positive)
		: number{num}
		, sign{s}
	{}
	
	BigInt(const BigInt& other)
		: number{other.number}
		, sign{other.sign} 
	{}

	BigInt(BigInt&& other)
		: number{move(other.number)}
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

	BigInt& operator+=(const BigInt& right);
	BigInt& operator-=(const BigInt& right);
	BigInt& operator*=(const BigInt& right);

	Number::const_iterator begin() const { return number.begin(); }
	Number::const_iterator end() const { return number.end(); }

	Number::iterator begin() { return number.begin(); }
	Number::iterator end() { return number.end(); }

	Elem operator[](size_t index) { return number[index]; }
	Elem operator[](size_t index) const { return number[index]; }

	size_t size() const { return number.size(); }

private:
	Number parse_int(int num);
	Number number;
	Sign sign;
};