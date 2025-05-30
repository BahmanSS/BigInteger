#include "biginteger.hpp"

constexpr uint64_t TWO_32 = 4294967296ULL; // 2^32

void BigInteger::normalize() {
	while (lenNumber > 1 && absNumber[lenNumber - 1] == 0) { --lenNumber; }
	if (lenNumber == 1 && absNumber[0] == 0) { positive = true; }
}

BigInteger::BigInteger(int x) : lenNumber(1) {
	absNumber = new uint32_t[1];
	positive = (x >= 0);
	uint64_t abs_x = positive ? static_cast<uint64_t>(x) : static_cast<uint64_t>(-(x + 1)) + 1;
	absNumber[0] = static_cast<uint32_t>(abs_x);
}
BigInteger::BigInteger(unsigned int x) : lenNumber(1), positive(true) {
	absNumber = new uint32_t[1];
	absNumber[0] = static_cast<uint32_t>(x);
}
BigInteger::BigInteger(long x) {
	positive = (x >= 0);
	uint64_t abs_x = positive ? static_cast<uint64_t>(x) : static_cast<uint64_t>(-(x + 1)) + 1;
	if (abs_x >= static_cast<long>(TWO_32)) {
		lenNumber = 2;
		absNumber = new uint32_t[2];
		absNumber[1] = static_cast<uint32_t>(abs_x >> 32);
		absNumber[0] = static_cast<uint32_t>(abs_x);
	}
	else {
		lenNumber = 1;
		absNumber = new uint32_t[1];
		absNumber[0] = static_cast<uint32_t>(abs_x);
	}
	normalize();
}
BigInteger::BigInteger(unsigned long x) : positive(true) {
	if (x >= TWO_32) {
		lenNumber = 2;
		absNumber = new uint32_t[2];
		absNumber[1] = static_cast<uint32_t>(x >> 32);
		absNumber[0] = static_cast<uint32_t>(x);
	}
	else {
		lenNumber = 1;
		absNumber = new uint32_t[1];
		absNumber[0] = static_cast<uint32_t>(x);
	}
	normalize();
}
BigInteger::BigInteger(long long x) {
	positive = (x >= 0);
	uint64_t abs_x = positive ? static_cast<uint64_t>(x) : static_cast<uint64_t>(-(x + 1)) + 1;
	if (abs_x >= static_cast<long long>(TWO_32)) {
		lenNumber = 2;
		absNumber = new uint32_t[2];
		absNumber[1] = static_cast<uint32_t>(abs_x >> 32);
		absNumber[0] = static_cast<uint32_t>(static_cast<uint32_t>(abs_x));
	}
	else {
		lenNumber = 1;
		absNumber = new uint32_t[1];
		absNumber[0] = static_cast<uint32_t>(abs_x);
	}
	normalize();
}
BigInteger::BigInteger(unsigned long long x) : positive(true) {
	if (x >= static_cast<unsigned long long>(TWO_32)) {
		lenNumber = 2;
		absNumber = new uint32_t[2];
		absNumber[1] = static_cast<uint32_t>(x >> 32);
		absNumber[0] = static_cast<uint32_t>(static_cast<uint32_t>(x));
	}
	else {
		lenNumber = 1;
		absNumber = new uint32_t[1];
		absNumber[0] = static_cast<uint32_t>(x);
	}
	normalize();
}

uint32_t BigInteger::DeltoTWO_32(std::string& x) {
	std::string quotient;
	uint64_t remainder = 0;

	for (char digit : x) {
		uint64_t current = remainder * 10 + (digit - '0');
		quotient += static_cast<char>((current / TWO_32) + '0');
		remainder = current % TWO_32;
	}

	size_t pos = quotient.find_first_not_of('0');
	if (pos == std::string::npos) { x = "0"; }
	else { x = quotient.substr(pos); }

	return static_cast<uint32_t>(remainder);
}
void BigInteger::Reverse(std::string& str) {
	int left = 0;
	int right = static_cast<int>(str.size()) - 1;

	while (left < right) {
		char temp = str[left];
		str[left] = str[right];
		str[right] = temp;
		++left;
		--right;
	}
}
std::string BigInteger::SumStrings(const std::string& x, const std::string& y) {
	std::string result;

	int i = static_cast<int>(x.size()) - 1;
	int j = static_cast<int>(y.size()) - 1;

	int transfer{};

	while (i >= 0 || j >= 0 || transfer != 0) {
		int digit_x = (i >= 0) ? x[i--] - '0' : 0;
		int digit_y = (j >= 0) ? y[j--] - '0' : 0;

		int sum = digit_x + digit_y + transfer;
		result.push_back(static_cast<char>((sum % 10) + '0'));
		transfer = sum / 10;
	}

	Reverse(result);
	return result;
}
std::string BigInteger::MultiplicationStrings(const std::string& x, const std::string& y) {
	if (x == "0" || y == "0") { return "0"; }

	std::string result = "0";

	for (int i = static_cast<int>(x.size()) - 1, shift = 0; i >= 0; --i, ++shift) {
		std::string tmpSum(shift, '0');
		int transfer{};

		for (int j = static_cast<int>(y.size()) - 1; j >= 0; --j) {
			int mult = (x[i] - '0') * (y[j] - '0') + transfer;
			tmpSum.push_back(static_cast<char>((mult % 10)+'0'));
			transfer = mult / 10;
		}

		if (transfer > 0) { tmpSum.push_back(static_cast<char>(transfer + '0')); }
		Reverse(tmpSum);

		result = SumStrings(result, tmpSum);
	}

	return result;
}
std::uint8_t BigInteger::DelTo16(std::string& x) {
	std::string quotient;
	uint32_t remainder = 0;

	for (char digit : x) {
		uint32_t current = remainder * 10 + (digit - '0');
		quotient += static_cast<char>((current / 16) + '0');
		remainder = current % 16;
	}

	size_t pos = quotient.find_first_not_of('0');
	if (pos == std::string::npos) {
		x = "0";
	}
	else {
		x = quotient.substr(pos);
	}

	return static_cast<uint8_t>(remainder);
}
void BigInteger::HexToDec(std::string& x) {
	std::string result = "0";
	for (size_t i = 0, end = x.size(); i < end; ++i) {
		int digit_16{};
		if (isdigit(x[i]) != 0) {
			digit_16 = x[i] - '0';
		} else if (x[i] >= 'a' && x[i] <= 'f') {
			digit_16 = x[i] - 'a' + 10;
		} else if (x[i] >= 'A' && x[i] <= 'F') {
			digit_16 = x[i] - 'A' + 10;
		} else {
			throw std::invalid_argument("Invalid character in string.");
		}
		result = SumStrings(MultiplicationStrings(result, "16"), std::to_string(digit_16));
	}
	x = result;
}

BigInteger::BigInteger(std::string x, biginteger_base base) {
	if (x.empty()) { throw std::invalid_argument("Empty string is not a valid number."); }

	if (base == biginteger_base::hex) { HexToDec(x); }

	if (x[0] == '-') {
		positive = false;
		x = x.substr(1);
	}
	else if (x[0] == '+') {
		positive = true;
		x = x.substr(1);
	}
	else { positive = true; }
	if (x.empty()) { throw std::invalid_argument("Empty string is not a valid number."); }

	if (x.find_first_not_of('0') == std::string::npos) {
		x = "0";
		positive = true;
		lenNumber = 1;
		absNumber = new uint32_t[1]{0};
	}
	else {
		
		for (char ch : x) {
			if (isdigit(ch)==0) { throw std::invalid_argument("Invalid character in input."); }
		}

		uint32_t* temp = new uint32_t[x.size()];
		lenNumber = 0;
		while (x != "0") {
			temp[lenNumber] = DeltoTWO_32(x);
			++lenNumber;
		}
		absNumber = new uint32_t[lenNumber];
		for (int i = 0; i < static_cast<int>(lenNumber); ++i) {
			absNumber[i] = temp[i];
		}
		delete[] temp;
	}
}


BigInteger::BigInteger(const BigInteger& x)
	: positive(x.positive), lenNumber(x.lenNumber) {
	absNumber = new uint32_t[lenNumber];
	std::copy(x.absNumber, x.absNumber + lenNumber, absNumber);
}
BigInteger::BigInteger(BigInteger&& x) noexcept
	: positive(x.positive), lenNumber(x.lenNumber), absNumber(x.absNumber) {
	x.absNumber = nullptr;
	x.lenNumber = 0;
	x.positive = true;
}

bool BigInteger::operator==(const BigInteger& other) const {
	if (positive != other.positive) { return false; }
	if (lenNumber != other.lenNumber) { return false; }
	for (int i = 0; i < static_cast<int>(lenNumber); ++i) {
		if (absNumber[i] != other.absNumber[i]) {
			return false;
		}
	}
	return true;
}
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   
bool operator!=(const BigInteger& first, const BigInteger& second) {
	return !(first == second);
}

BigInteger& BigInteger::operator=(const BigInteger& x) {
	if (this != &x) {
		delete[] absNumber;
		lenNumber = x.lenNumber;
		positive = x.positive;
		absNumber = new uint32_t[lenNumber];
		std::copy(x.absNumber, x.absNumber + lenNumber, absNumber);
	}
	return *this;
}

BigInteger& BigInteger::operator=(BigInteger&& x) noexcept {
	if (this != &x) {
		delete[] absNumber;

		absNumber = x.absNumber;
		lenNumber = x.lenNumber;
		positive = x.positive;

		x.absNumber = nullptr;
		x.lenNumber = 0;
		x.positive = true;
	}
	return *this;
}
bool BigInteger::operator<(const BigInteger& other) {
	if (*this == other) { return false; }
	if (positive && other.positive) {
		if (lenNumber < other.lenNumber) { return true; }
		if (lenNumber > other.lenNumber) { return false; }
		for (int i = static_cast<int>(lenNumber) - 1; i >= 0; --i) {
			if (absNumber[i] < other.absNumber[i]) { return true; }
			if (absNumber[i] > other.absNumber[i]) { return false; }
		}
	}
	if (!positive && !other.positive) {
		if (lenNumber < other.lenNumber) { return false; }
		if (lenNumber > other.lenNumber) { return true; }
		
		for (int i = static_cast<int>(lenNumber) - 1; i >= 0; --i) {
			if (absNumber[i] < other.absNumber[i]) { return false; }
			if (absNumber[i] > other.absNumber[i]) { return true; }
		}
	}
	return !positive && other.positive;
	return false;
}
bool BigInteger::operator<=(const BigInteger& other) { return (*this == other || *this < other); }
bool BigInteger::operator>(const BigInteger& other) { return !(*this <= other); }
bool BigInteger::operator>=(const BigInteger& other) { return !(*this < other); }

BigInteger BigInteger::operator-() const {
	BigInteger copy(*this);
	if (lenNumber == 1 && absNumber[0] == 0) {
		copy.positive = true;
	}
	else {
		copy.positive = !copy.positive;
	}
	return copy;
}

BigInteger BigInteger::SumModules(const BigInteger& first, const BigInteger& second) {
	size_t maxlen = std::max(first.lenNumber, second.lenNumber);
	uint64_t transfer = 0;

	uint32_t* absNumber = new uint32_t[maxlen + 1];
	size_t lenNumber = 0;

	for (size_t i = 0; i < maxlen; ++i) {
		uint64_t f = (i < first.lenNumber) ? static_cast<uint64_t>(first.absNumber[i]) : 0ULL;
		uint64_t s = (i < second.lenNumber) ? static_cast<uint64_t>(second.absNumber[i]) : 0ULL;

		uint64_t sum = f + s + transfer;
		absNumber[lenNumber] = sum % TWO_32;
		++lenNumber;
		transfer = sum >> 32;
	}
	if (transfer != 0U) {
		absNumber[lenNumber] = static_cast<uint32_t>(transfer);
		++lenNumber;
	}

	BigInteger res;
	res.clear();
	res.lenNumber = lenNumber;
	res.absNumber = new uint32_t[lenNumber];
	for (size_t i = 0; i < lenNumber; ++i) {
		res.absNumber[i] = absNumber[i];
	}
	res.positive = true;

	delete[] absNumber;

	return res;
}
BigInteger BigInteger::DiffModules(const BigInteger& first, const BigInteger& second) {
	size_t maxlen = first.lenNumber;
	uint32_t* absNumber = new uint32_t[maxlen];
	size_t lenNumber = 0;

	int64_t borrow = 0;

	for (size_t i = 0; i < maxlen; ++i) {
		int64_t f = static_cast<int64_t>(first.absNumber[i]);
		int64_t s = (i < second.lenNumber) ? static_cast<int64_t>(second.absNumber[i]) : 0;

		int64_t sub = f - s - borrow;

		if (sub < 0) {
			sub += static_cast<int64_t>(TWO_32);
			borrow = 1;
		}
		else {
			borrow = 0;
		}

		absNumber[lenNumber++] = static_cast<uint32_t>(sub);
	}

	while (lenNumber > 1 && absNumber[lenNumber - 1] == 0) {
		--lenNumber;
	}

	BigInteger res;
	res.clear();
	res.lenNumber = lenNumber;
	res.absNumber = new uint32_t[lenNumber];
	for (size_t i = 0; i < lenNumber; ++i) {
		res.absNumber[i] = absNumber[i];
	}
	res.positive = true;
	delete[] absNumber;
	return res;
}
BigInteger BigInteger::Mult(const BigInteger& first, const BigInteger& second) {
	BigInteger res;
	res.clear();
	res.lenNumber = first.lenNumber + second.lenNumber;
	res.absNumber = new uint32_t[res.lenNumber]();
	res.positive = (first.positive == second.positive);

	for (size_t i = 0; i < first.lenNumber; ++i) {
		uint64_t carry = 0;
		for (size_t j = 0; j < second.lenNumber; ++j) {
			size_t k = i + j;
			uint64_t mul = static_cast<uint64_t>(first.absNumber[i]) * second.absNumber[j];
			mul += res.absNumber[k] + carry;
			res.absNumber[k] = static_cast<uint32_t>(mul);
			carry = mul >> 32;
		}
		size_t k = i + second.lenNumber;
		while (carry != 0) {
			uint64_t sum = static_cast<uint64_t>(res.absNumber[k]) + carry;
			res.absNumber[k] = static_cast<uint32_t>(sum);
			carry = sum >> 32;
			++k;
		}
	}

	while (res.lenNumber > 1 && res.absNumber[res.lenNumber - 1] == 0) {
		--res.lenNumber;
	}
	
	return res;
}
uint32_t CountLeadingZeros32(uint32_t x) {
	if (x == 0) { return 32; }
	uint32_t count = 0;
	for (int i = 31; i >= 0; --i) {
		if (((x >> i) & 1) != 0U) { break; }
		++count;
	}
	return count;
}
BigInteger BigInteger::DivModules(const BigInteger& dividend, const BigInteger& divisor) {
	if (divisor.lenNumber == 1 && divisor.absNumber[0] == 0) {
		throw std::invalid_argument("Division by zero");
	}
	if (&dividend < &divisor) {
		return BigInteger(0);
	}
	if (divisor.lenNumber == 1 && divisor.absNumber[0] == 1) {
		return dividend;
	}

	size_t n = dividend.lenNumber;
	size_t m = divisor.lenNumber;

	// 1. Нормализация
	int s = static_cast<int>(CountLeadingZeros32(divisor.absNumber[m - 1]));
	uint32_t* u = new uint32_t[n + 1]();
	uint32_t* v = new uint32_t[m]();     

	// Скопировать и сдвинуть влево U и V
	for (size_t i = 0; i < n; ++i) {
		uint64_t cur = static_cast<uint64_t>(dividend.absNumber[i]) << s;
		u[i] |= static_cast<uint32_t>(cur);
		u[i + 1] |= static_cast<uint32_t>(cur >> 32);
	}
	for (size_t i = 0; i < m; ++i) {
		uint64_t cur = static_cast<uint64_t>(divisor.absNumber[i]) << s;
		v[i] |= static_cast<uint32_t>(cur);
		if (i + 1 < m) {
			v[i + 1] |= static_cast<uint32_t>(cur >> 32);
		}
	}

	// Результат
	if (n < m) {
		delete[] u;
		delete[] v;
		return BigInteger(0U);
	}
	size_t q_len = n - m + 1;
	uint32_t* q = new uint32_t[q_len]();

	uint64_t v1 = v[m - 1];
	uint64_t v2 = (m > 1) ? v[m - 2] : 0;

	for (size_t j = q_len; j-- > 0;) {
		uint64_t u0 = u[j + m];
		uint64_t u1 = u[j + m - 1];
		uint64_t u2 = (m >= 2) ? u[j + m - 2] : 0;

		uint64_t dividend_est = (u0 << 32) | u1;
		uint64_t q_hat = dividend_est / v1;
		uint64_t r_hat = dividend_est % v1;

		if (q_hat >= (1ULL << 32)) { q_hat = (1ULL << 32) - 1; }

		while (q_hat * v2 > ((r_hat << 32) | u2)) {
			--q_hat;
			r_hat += v1;
			if (r_hat >= (1ULL << 32)) { break; }
		}

		// Вычесть q_hat * v из u
		uint64_t borrow = 0;
		for (size_t i = 0; i < m; ++i) {
			uint64_t prod = q_hat * v[i];
			uint64_t sub = static_cast<uint64_t>(u[j + i]) - (prod & 0xFFFFFFFF) - borrow;
			u[j + i] = static_cast<uint32_t>(sub);
			borrow = (prod >> 32) + ((sub >> 63) & 1); // если sub < 0 → перенос
		}
		uint64_t final = static_cast<uint64_t>(u[j + m]) - borrow;
		u[j + m] = static_cast<uint32_t>(final);

		if ((final >> 63) != 0U) {
			// Откат и уменьшение q_hat
			--q_hat;
			uint64_t carry = 0;
			for (size_t i = 0; i < m; ++i) {
				uint64_t sum = static_cast<uint64_t>(u[j + i]) + v[i] + carry;
				u[j + i] = static_cast<uint32_t>(sum);
				carry = sum >> 32;
			}
			u[j + m] += static_cast<uint32_t>(carry);
		}

		q[j] = static_cast<uint32_t>(q_hat);
	}

	// Удалим ведущие нули
	while (q_len > 1 && q[q_len - 1] == 0)  { --q_len; }

	// Сформировать BigInteger
	BigInteger result;
	result.clear();
	result.positive = true;
	result.lenNumber = q_len;
	result.absNumber = new uint32_t[q_len];
	std::copy(q, q + q_len, result.absNumber);

	delete[] q;
	delete[] u;
	delete[] v;

	return result;
}


BigInteger& BigInteger::operator+=(const BigInteger& other) {
	if (positive == other.positive) {
		BigInteger res = SumModules(*this, other);
		res.positive = positive;
		*this = res;
	}
	else {
		BigInteger res;
		BigInteger a = *this;
		BigInteger b = other;
		a.positive = true;
		b.positive = true;

		if (a == b) {
			res.lenNumber = 1;
			res.clear();
			res.absNumber = new uint32_t[1]{ 0 };
			res.positive = true;
		}
		else if (a > b) {
			res = DiffModules(*this, other);
			res.positive = positive;
		}
		else {
			res = DiffModules(other, *this);
			res.positive = other.positive;
		}
		*this = res;
	}
	return *this;
}
BigInteger& BigInteger::operator*=(const BigInteger& other) {
	*this = BigInteger::Mult(*this, other);
	return *this;
}
BigInteger& BigInteger::operator/=(const BigInteger& other) {
	BigInteger a = *this;
	a.positive = true;
	BigInteger b = other;
	b.positive = true;
	if (other == 0) { throw std::invalid_argument("Division by zero."); }
	if (*this == 0 ) { *this = 0;}
	else if (*this == other) { *this = 1;}
	else if (a<b) { *this = 0; }
	else {
		bool pos = (positive == other.positive);
		positive = true;
		BigInteger second = other;
		second.positive = true;
		*this = DivModules(*this, second);
		positive = pos;
	}
	return *this;
}

BigInteger BigInteger::divWithRemainder(const BigInteger& x, const BigInteger& y, BigInteger& remainder) {
	// x != 0 y != 0, x > y > 0
	BigInteger result;
	remainder = 0;
	for (int i = static_cast<int>(x.lenNumber) - 1; i >= 0; --i) {
		remainder *= TWO_32;
		remainder += x.absNumber[i];
		result *= TWO_32;

		uint32_t left = 0;
		uint32_t right = UINT32_MAX;
		uint32_t qDigit = 0;

		while (left <= right) {
			uint32_t mid = left + ((right - left) >> 1);
			BigInteger midY = y * mid;
			if (midY <= remainder) {
				qDigit = mid;
				left = mid + 1;
			}
			else {
				right = mid - 1;
			}
		}

		remainder -= y * qDigit;
		result += qDigit;
	}
	return result;
}


BigInteger& BigInteger::operator%=(const BigInteger& other) {
	if (*this == 0) { return *this; }
	if (other == 0) { throw std::invalid_argument("Division by zero"); }

	bool pos = ((positive == other.positive) || (positive && !other.positive));
	
	BigInteger y = other;
	positive = true;
	y.positive = true;// x > 0 y > 0

	if (*this < y) { positive = pos; return *this; } //x > y
	
	BigInteger remainder;
	divWithRemainder(*this, y, remainder);
	*this = remainder;
	if (*this != 0) { positive = pos; }
	return *this;
}


BigInteger operator+(const BigInteger& first, const BigInteger& second) {
	BigInteger result{};
	result += first;
	result += second;
	return result;
}
BigInteger operator-(const BigInteger& first, const BigInteger& second) {
	BigInteger result{};
	result += first;
	result -= second;
	return result;
}
BigInteger operator*(const BigInteger& first, const BigInteger& second) {
	BigInteger res = first;
	res *= second;
	return res;
}
BigInteger operator/(const BigInteger& first, const BigInteger& second) {
	BigInteger res = first;
	res /= second;
	return res;
}
BigInteger operator%(const BigInteger& first, const BigInteger& second) {
	BigInteger res = first;
	res %= second;
	return res;
}

std::string BigInteger::to_string() const {
	std::string result = "0";
	for (int i = static_cast<int>(lenNumber) - 1; i >= 0; --i) {
		uint32_t digit = absNumber[i];
		result = SumStrings(MultiplicationStrings(result, "4294967296"), std::to_string(digit));
	}
	result = (positive) ? result : ("-" + result);
	return result;
}
std::string to_string(const BigInteger& x) { return x.to_string(); }
std::string to_hex(const BigInteger& x) {
	std::string num = to_string(x);
	if (num[0] == '-') { throw std::invalid_argument("Not positive num can^t be hex."); }
	if (num == "0") { return "0"; }
	std::string result{};
	while (num != "0") {
		uint8_t remainder = BigInteger::DelTo16(num);
		char remainder_char = (remainder >= 0 && remainder <= 9) ? static_cast<char>(remainder + '0') : static_cast<char>(remainder - 10 + 'A');
		result.push_back(remainder_char);
	}
	BigInteger::Reverse(result);
	return result;
}
