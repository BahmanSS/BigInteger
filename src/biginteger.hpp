#ifndef BIG_INTEGER_HPP
#define BIG_INTEGER_HPP
#include <string>
#include <iostream>

enum class biginteger_base { dec = 10, hex = 16 };

class BigInteger {
private:
	std::uint32_t* absNumber;
	std::size_t lenNumber;
	bool positive;
public:
	
	static void HexToDec(std::string& x);
	static uint32_t DeltoTWO_32(std::string& x);
	static void Reverse(std::string& str);
	static std::string SumStrings(const std::string& x, const std::string& y);
	static std::string MultiplicationStrings(const std::string& x, const std::string& y);
	static std::uint8_t DelTo16(std::string& x);

	
	static BigInteger SumModules(const BigInteger& first, const BigInteger& second);
	static BigInteger DiffModules(const BigInteger& first, const BigInteger& second);
	static BigInteger Mult(const BigInteger& first, const BigInteger& second);
	static BigInteger DivModules(const BigInteger& dividend, const BigInteger& divisor);
	void normalize();
	static BigInteger divWithRemainder(const BigInteger& x, const BigInteger& y, BigInteger& remainder); // my

	BigInteger() : lenNumber(1), positive(true), absNumber(new uint32_t[1]{ 0 }) {}
	BigInteger(int x);
	BigInteger(unsigned int x);
	BigInteger(long x);
	BigInteger(unsigned long x);
	BigInteger(long long x);
	BigInteger(unsigned long long x);

	BigInteger(std::string x, biginteger_base base = biginteger_base::dec);

	BigInteger(const BigInteger& x);
	BigInteger(BigInteger&& x) noexcept;

	void clear() { delete[] absNumber; }
	~BigInteger() { clear(); }

	bool operator==(const BigInteger& other) const;

	BigInteger& operator=(const BigInteger& x);
	BigInteger& operator=(BigInteger&& x) noexcept;

	BigInteger& operator+=(const BigInteger& other);
	BigInteger& operator-=(const BigInteger& other) { *this += -(other); return *this; }
	BigInteger& operator*=(const BigInteger& other);
	BigInteger& operator/=(const BigInteger& other);
	BigInteger& operator%=(const BigInteger& other);

	BigInteger divBy2() const {
		BigInteger result;
		result.lenNumber = lenNumber;
		result.absNumber = new std::uint32_t[result.lenNumber];

		std::uint32_t carry = 0;
		for (std::size_t i = lenNumber; i-- > 0;) {
			std::uint64_t current = (static_cast<std::uint64_t>(carry) << 32) | absNumber[i];
			result.absNumber[i] = static_cast<std::uint32_t>(current / 2);
			carry = static_cast<std::uint32_t>(current % 2);
		}

		result.positive = positive;
		result.normalize(); // если есть такая функция
		return result;
	}
	BigInteger operator-() const;
	BigInteger operator+() const { return *this; }

	BigInteger& operator++() { *this += 1; return *this; }
	BigInteger& operator--() { *this -= 1; return *this; }
	BigInteger operator++(int) { BigInteger tmp = *this; *this += 1; return tmp; }
	BigInteger operator--(int) { BigInteger tmp = *this; *this -= 1; return tmp; }

	bool operator<(const BigInteger& other);
	bool operator<=(const BigInteger& other);
	bool operator>(const BigInteger& other);
	bool operator>=(const BigInteger& other);

	std::string to_string() const;
};

BigInteger operator+(const BigInteger& first, const BigInteger& second);
BigInteger operator-(const BigInteger& first, const BigInteger& second);
BigInteger operator*(const BigInteger& first, const BigInteger& second);
BigInteger operator/(const BigInteger& first, const BigInteger& second);
BigInteger operator%(const BigInteger& first, const BigInteger& second);

bool operator!=(const BigInteger& first, const BigInteger& second);

std::string to_string(const BigInteger& x);
std::string to_hex(const BigInteger& x);

#endif
