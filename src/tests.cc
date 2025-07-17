#include <gtest/gtest.h>

#include "biginteger.hpp"


TEST(Create, default_constructor)
{
    BigInteger x;
    BigInteger y = 0;

    EXPECT_EQ(BigInteger(0), x);
    EXPECT_EQ(y, x);
}

TEST(Create, copy_constructor)
{
    BigInteger x = 3;
    BigInteger y = x;

    EXPECT_EQ(y, x);
    EXPECT_EQ(3, y);
}

TEST(Create, copy_constructor_real_copy_to)
{
    BigInteger x = 2;
    BigInteger y = x;
    x = 4;

    EXPECT_EQ(2, y);
}

TEST(Create, copy_constructor_real_copy_from)
{
    BigInteger x = 3;
    BigInteger y = x;
    y = 5;

    EXPECT_EQ(3, x);
}


TEST(Create, constructor_string)
{

    EXPECT_EQ(BigInteger("0"), 0);
    EXPECT_EQ(BigInteger("1"), 1);
    EXPECT_EQ(BigInteger("-1"), -1);
    EXPECT_EQ(BigInteger("1234567"), 1234567);
    EXPECT_EQ(BigInteger("-9876543"), -9876543);
    EXPECT_EQ(BigInteger("+9876543"), 9876543);
    EXPECT_EQ(BigInteger("2147483647"), 2147483647);
    EXPECT_EQ(BigInteger("-2147483648"), -2147483648);
}

TEST(Create, constructor_hex_string)
{
    EXPECT_EQ(BigInteger("A", biginteger_base::hex), 10);
    EXPECT_EQ(BigInteger("AB", biginteger_base::hex), 171);
    EXPECT_EQ(BigInteger("ABBA", biginteger_base::hex), 43962);
    EXPECT_EQ(BigInteger("1234567", biginteger_base::hex), 19088743);
    EXPECT_EQ(BigInteger("FEEE", biginteger_base::hex), 65262);
    EXPECT_EQ(BigInteger("BAADF00D", biginteger_base::hex), 3131961357);
    EXPECT_EQ(BigInteger("CCCCCCCC", biginteger_base::hex), 3435973836);
    EXPECT_EQ(BigInteger("DEADBEEF", biginteger_base::hex), 3735928559);
    EXPECT_EQ(BigInteger("FEEDCAFE", biginteger_base::hex), 4276996862UL);
    EXPECT_EQ(BigInteger("FFCCDDEE", biginteger_base::hex), 4291616238UL);
    EXPECT_EQ(BigInteger("1234567890ABCDEF", biginteger_base::hex), BigInteger("1311768467294899695"));
    EXPECT_EQ(BigInteger("FEDCBA987654321", biginteger_base::hex), BigInteger("1147797409030816545"));
}

TEST(Create, constructor_invalid_string)
{
    EXPECT_THROW(BigInteger("abc"), std::invalid_argument);
    EXPECT_THROW(BigInteger("123x"), std::invalid_argument);
    EXPECT_THROW(BigInteger(""), std::invalid_argument);
    EXPECT_THROW(BigInteger("-"), std::invalid_argument);
    EXPECT_THROW(BigInteger("-x"), std::invalid_argument);
    EXPECT_THROW(BigInteger("123-456"), std::invalid_argument);
    EXPECT_THROW(BigInteger("--5"), std::invalid_argument);
    EXPECT_THROW(BigInteger("++5"), std::invalid_argument);
}

TEST(Comparisons, comparison_operators_small_numbers)
{
    BigInteger a = 100;
    BigInteger b = 100;
    BigInteger c = 200;
    BigInteger d = -100;

    EXPECT_TRUE(a == b);
    EXPECT_TRUE(a != c);
    EXPECT_TRUE(a < c);
    EXPECT_TRUE(c > a);
    EXPECT_TRUE(a <= a);
    EXPECT_TRUE(a <= b);
    EXPECT_TRUE(a <= c);
    EXPECT_TRUE(c >= a);
    EXPECT_TRUE(d < a);
    EXPECT_TRUE(d != 0);
}

TEST(Comparisons, comparison_operators_false_small_numbers)
{
    BigInteger a = 100;
    BigInteger b = 100;
    BigInteger c = 200;
    BigInteger d = -100;
    EXPECT_FALSE(a < b);
    EXPECT_FALSE(a == c);
    EXPECT_FALSE(a > c);
    EXPECT_FALSE(c <= a);
    EXPECT_FALSE(a < a);
    EXPECT_FALSE(a > b);
    EXPECT_FALSE(d > a);
    EXPECT_FALSE(d >= a);
    EXPECT_FALSE(d == 0);
}

TEST(Comparisons, compare_with_sign)
{
    BigInteger a = 123;
    BigInteger b = -a;

    EXPECT_TRUE(a != b);
}

TEST(Comparisons, compare_zero_and_minus_zero)
{
    BigInteger a;
    BigInteger b = -a;

    EXPECT_TRUE(a == b);
}

TEST(Comparisons, comparison_operators)
{
    BigInteger a("1234567890ABCDEF", biginteger_base::hex);
    BigInteger b(a);
    BigInteger c("1234567891ABCDEF", biginteger_base::hex);
    BigInteger d = -100;

    EXPECT_TRUE(a == b);
    EXPECT_TRUE(a != c);
    EXPECT_TRUE(a < c);
    EXPECT_TRUE(c > a);
    EXPECT_TRUE(a <= a);
    EXPECT_TRUE(a <= b);
    EXPECT_TRUE(a <= c);
    EXPECT_TRUE(c >= a);
    EXPECT_TRUE(d < a);
    EXPECT_TRUE(d != 0);
}

TEST(Comparisons, comparison_operators_false)
{
    BigInteger a("1234567890ABCDEF", biginteger_base::hex);
    BigInteger b(a);
    BigInteger c("1234567891ABCDEF", biginteger_base::hex);
    BigInteger d = -100;

    EXPECT_FALSE(a < b);
    EXPECT_FALSE(a == c);
    EXPECT_FALSE(a > c);
    EXPECT_FALSE(c <= a);
    EXPECT_FALSE(a < a);
    EXPECT_FALSE(a > b);
    EXPECT_FALSE(d > a);
    EXPECT_FALSE(d >= a);
    EXPECT_FALSE(d == 0);
}

TEST(Assignments, assignment_operator)
{
    BigInteger a("1234567890ABCDEF", biginteger_base::hex);
    BigInteger b = 7;
    b = a;

    EXPECT_TRUE(a == b);
}

TEST(Assignments, self_assignment)
{
    BigInteger a = 5;
    a = a;

    EXPECT_TRUE(a == 5);
}

TEST(Assignments, assignment_return_value)
{
    BigInteger a = 4;
    BigInteger b = 7;
    (a = b) = a;

    EXPECT_TRUE(a == 7);
    EXPECT_TRUE(b == 7);
}


TEST(Converting, string_conv)
{
    EXPECT_EQ("100", to_string(BigInteger("100")));
    EXPECT_EQ("100", to_string(BigInteger("0100")));
    EXPECT_EQ("0", to_string(BigInteger("0")));
    EXPECT_EQ("0", to_string(BigInteger("-0")));
    EXPECT_EQ("-1000000000000000", to_string(BigInteger("-1000000000000000")));

    EXPECT_EQ("2147483647", to_string(BigInteger("2147483647")));
    EXPECT_EQ("2147483648", to_string(BigInteger("2147483648")));
    EXPECT_EQ("-2147483649", to_string(BigInteger("-2147483649")));
}

TEST(Converting, hex_conv)
{
    EXPECT_EQ("0", to_hex(BigInteger(0)));
    EXPECT_EQ("2A", to_hex(BigInteger(42)));
    EXPECT_EQ("FEEDCAFE", to_hex(BigInteger("FEEDCAFE", biginteger_base::hex)));
    EXPECT_EQ("DEADBEEF", to_hex(BigInteger("DEADBEEF", biginteger_base::hex)));
    EXPECT_EQ("BAADF00D", to_hex(BigInteger("BAADF00D", biginteger_base::hex)));
    EXPECT_EQ("CCCCCCCC", to_hex(BigInteger("CCCCCCCC", biginteger_base::hex)));
    EXPECT_EQ("1234567890ABCDEF", to_hex(BigInteger("1234567890ABCDEF", biginteger_base::hex)));
    EXPECT_EQ("FEDCBA987654321", to_hex(BigInteger("FEDCBA987654321", biginteger_base::hex)));
}


namespace
{
    template <typename T>
    void test_converting_ctor(T value)
    {
        using std::to_string;

        BigInteger bi = value;
        EXPECT_EQ(to_string(value), to_string(bi));
    }
}

TEST(Converting, converting_ctor)
{
    test_converting_ctor(1);
    test_converting_ctor(1U);
    test_converting_ctor(1L);
    test_converting_ctor(1UL);
    test_converting_ctor(1LL);
    test_converting_ctor(1ULL);
}

TEST(Converting, converting_ctor2)
{
    BigInteger a(1);
    BigInteger b(1U);
    BigInteger c(1L);
    BigInteger d(1UL);
    BigInteger e(1LL);
    BigInteger f(1ULL);

    EXPECT_TRUE(a == b);
    EXPECT_TRUE(a == c);
    EXPECT_TRUE(a == d);
    EXPECT_TRUE(a == e);
    EXPECT_TRUE(a == f);
}

TEST(Converting, converting_ctor3)
{
    BigInteger a(-1);
    BigInteger b(-1L);
    BigInteger c(-1LL);

    EXPECT_TRUE(a == b);
    EXPECT_TRUE(a == c);
    EXPECT_TRUE(b == c);
}


TEST(Arithmetic, one_plus_zero)
{
    EXPECT_EQ(BigInteger(1), BigInteger(1) + BigInteger(0));
    EXPECT_EQ(BigInteger(1), BigInteger(1) + 0); // implicit conversion from int must work
    EXPECT_EQ(BigInteger(1), 0 + BigInteger(1));
}

TEST(Arithmetic, one_plus_one)
{
    EXPECT_EQ(BigInteger(2), BigInteger(1) + BigInteger(1));
    EXPECT_EQ(BigInteger(2), BigInteger(1) + 1); // implicit conversion from int must work
    EXPECT_EQ(BigInteger(2), 1 + BigInteger(1));
}

TEST(Arithmetic, operator_plus)
{
    BigInteger a = 5;
    BigInteger b = 20;

    EXPECT_TRUE(a + b == 25);

    a += b;
    EXPECT_TRUE(a == 25);

    BigInteger x("FFFFFFFF", biginteger_base::hex);
    BigInteger y(1);
    EXPECT_TRUE(x + y == BigInteger("100000000", biginteger_base::hex));
    EXPECT_TRUE(x + x == BigInteger("1FFFFFFFE", biginteger_base::hex));

    x += y;
    EXPECT_TRUE(x == BigInteger("100000000", biginteger_base::hex));
}

TEST(Arithmetic, operator_plus_signed)
{
    BigInteger a = 5;
    BigInteger b = -20;
    EXPECT_TRUE(a + b == -15);

    a += b;
    EXPECT_TRUE(a == -15);
}

TEST(Arithmetic, operator_pluseq_return_value)
{
    BigInteger a = 5;
    BigInteger b = 1;

    (a += b) += b;
    EXPECT_EQ(7, a);
}

TEST(Arithmetic, operator_sub)
{
    BigInteger a = 20;
    BigInteger b = 5;

    EXPECT_TRUE(a - b == 15);
    a -= b;
    EXPECT_TRUE(a == 15);
}

TEST(Arithmetic, operator_sub_signed)
{
    BigInteger a = 5;
    BigInteger b = 20;

    EXPECT_TRUE(a - b == -15);

    a -= b;
    EXPECT_TRUE(a == -15);

    a -= -100;
    EXPECT_TRUE(a == 85);
}

TEST(Arithmetic, operator_subeq_return_value)
{
    BigInteger a = 5;
    BigInteger b = 1;

    (a -= b) -= b;
    EXPECT_EQ(3, a);
}

TEST(Arithmetic, operator_mul)
{
    BigInteger a = 5;
    BigInteger b = 20;
    EXPECT_TRUE(a * b == 100);

    a *= b;
    EXPECT_TRUE(a == 100);
}

TEST(Arithmetic, operator_mul_signed)
{
    BigInteger a = -5;
    BigInteger b = 20;


    EXPECT_TRUE(a * b == -100);

    a *= b;
    EXPECT_TRUE(a == -100);
}

TEST(Arithmetic, operator_muleq_return_value)
{
    BigInteger a = 5;
    BigInteger b = 2;

    (a *= b) *= b;
    EXPECT_EQ(20, a);
}


TEST(Arithmetic, operator_div)
{
    BigInteger a = 20;
    BigInteger b = 5;
    BigInteger c = 20;

    EXPECT_EQ(0, b / c);
    EXPECT_TRUE(a / b == 4);
    EXPECT_TRUE(a % b == 0);

    a /= b;
    EXPECT_TRUE(a == 4);

    c %= b;
    EXPECT_TRUE(c == 0);
}

TEST(Arithmetic, operator_div_signed)
{
    BigInteger a = -20;
    BigInteger b = 5;

    EXPECT_TRUE(a / b == -4);
    EXPECT_TRUE(a % b == 0);
}

TEST(Arithmetic, operator_div_rounding)
{
    BigInteger a = 23;
    BigInteger b = 5;

    EXPECT_TRUE(a / b == 4);
    EXPECT_TRUE(a % b == 3);
}

TEST(Arithmetic, operator_div_rounding_negative)
{
    BigInteger a = 23;
    BigInteger b = -5;
    BigInteger c = -23;
    BigInteger d = 5;

    EXPECT_TRUE(a / b == -4);
    std::cout << "to";
    EXPECT_TRUE(c / d == -4);
    std::cout << "to";
    EXPECT_TRUE(a % b == 3);
    std::cout << "to";
    EXPECT_TRUE(c % d == -3);
    std::cout << "to";
    std::cout << to_string(c % d);
    std::cout << to_string(c / d);
}

TEST(Arithmetic, operator_div_return_value)
{
    BigInteger a = 100;
    BigInteger b = 2;

    (a /= b) /= b;
    EXPECT_EQ(25, a);
}

TEST(Arithmetic, operator_unary_plus)
{
    BigInteger a = 123;
    BigInteger b = +a;

    EXPECT_TRUE(a == b);
}

TEST(Arithmetic, negation)
{
    BigInteger a = 666;
    BigInteger b = -a;

    EXPECT_TRUE(b == -666);
}

TEST(Arithmetic, operator_increment)
{
    BigInteger a = 42;
    BigInteger pre = ++a;
    BigInteger post = a++;

    EXPECT_EQ(43, pre);
    EXPECT_EQ(43, post);
}

TEST(Arithmetic, operator_increment_zero)
{
    BigInteger a = 0;
    BigInteger pre = ++a;
    BigInteger post = a++;

    EXPECT_EQ(1, pre);
    EXPECT_EQ(1, post);
}

TEST(Arithmetic, operator_increment_to_zero)
{
    BigInteger a = -1;
    BigInteger pre = ++a;
    BigInteger post = a++;

    EXPECT_EQ(0, pre);
    EXPECT_EQ(0, post);
}

TEST(Arithmetic, operator_decrement)
{
    BigInteger a = 42;
    BigInteger pre = --a;
    BigInteger post = a--;

    EXPECT_EQ(41, pre);
    EXPECT_EQ(41, post);
}

TEST(Arithmetic, operator_decrement_zero)
{
    BigInteger a = 0;
    BigInteger pre = --a;
    BigInteger post = a--;

    EXPECT_EQ(-1, pre);
    EXPECT_EQ(-1, post);
}

TEST(Arithmetic, operator_decrement_to_zero)
{
    BigInteger a = 1;
    BigInteger pre = --a;
    BigInteger post = a--;

    EXPECT_EQ(0, pre);
    EXPECT_EQ(0, post);
}

TEST(Arithmetic, add_long)
{
    BigInteger a("10000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
    BigInteger b("100000000000000000000000000000000000000");
    BigInteger c("10000000000000000000000000000000000000000000000000000100000000000000000000000000000000000000");

    EXPECT_EQ(c, a + b);
}

TEST(Arithmetic, add_long_signed)
{
    BigInteger a("-1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
    BigInteger b("1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");

    EXPECT_EQ(0, a + b);
}

TEST(Arithmetic, add_long_signed2)
{
    BigInteger a("-1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
    BigInteger b("100000000000000000000000000000000000000");
    BigInteger c("-999999999999999999999999999999999999999999999999999900000000000000000000000000000000000000");

    EXPECT_EQ(c, a + b);
}

TEST(Arithmetic, add_long_pow2)
{
    BigInteger a("18446744073709551616");
    BigInteger b("-18446744073709551616");
    BigInteger c("36893488147419103232");

    EXPECT_EQ(c, a + a);
    EXPECT_EQ(a, b + c);
    EXPECT_EQ(a, c + b);
}

TEST(Arithmetic, sub_long)
{
    BigInteger a("10000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
    BigInteger b("100000000000000000000000000000000000000");
    BigInteger c("9999999999999999999999999999999999999999999999999999900000000000000000000000000000000000000");

    EXPECT_EQ(c, a - b);
}

TEST(Arithmetic, sub_long_pow2)
{
    BigInteger a("36893488147419103232");
    BigInteger b("36893488147419103231");

    EXPECT_EQ(1, a - b);
}

TEST(Arithmetic, mul_long)
{
    BigInteger a("10000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
    BigInteger b("100000000000000000000000000000000000000");
    BigInteger c("10000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
        "00000000000000000000000000000000000000");

    EXPECT_EQ(c, a * b);
}

TEST(Arithmetic, mul_long_signed)
{
    BigInteger a("-1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
    BigInteger b("100000000000000000000000000000000000000");
    BigInteger c("-1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
        "00000000000000000000000000000000000000");

    EXPECT_EQ(c, a * b);
}

TEST(Arithmetic, mul_long_signed2)
{
    BigInteger a("-100000000000000000000000000");
    BigInteger c("10000000000000000000000000000000000000000000000000000");

    EXPECT_EQ(c, a * a);
}

TEST(Arithmetic, mul_long_pow2)
{
    BigInteger a("18446744073709551616");
    BigInteger b("340282366920938463463374607431768211456");
    BigInteger c("115792089237316195423570985008687907853269984665640564039457584007913129639936");

    EXPECT_EQ(b, a * a);
    EXPECT_EQ(c, b * b);
}


TEST(Arithmetic, div_long)
{
    BigInteger a("10000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
    BigInteger b("100000000000000000000000000000000000000");
    BigInteger c("100000000000000000000000000000000000000000000000000000");
    EXPECT_EQ(c, a / b);
}

TEST(Arithmetic, div_long_signed)
{
    BigInteger a("-10000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
    BigInteger b("100000000000000000000000000000000000000");
    BigInteger c("-100000000000000000000000000000000000000000000000000000");

    EXPECT_EQ(c, a / b);
}

TEST(Arithmetic, div_long_signed2)
{
    BigInteger a("-10000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
    BigInteger b("-100000000000000000000000000000000000000");
    BigInteger c("100000000000000000000000000000000000000000000000000000");

    EXPECT_EQ(c, a / b);
}

TEST(Arithmetic, negation_long)
{
    BigInteger a("10000000000000000000000000000000000000000000000000000");
    BigInteger c("-10000000000000000000000000000000000000000000000000000");

    EXPECT_EQ(-a, c);
    EXPECT_EQ(a, -c);
}

TEST(Arithmetic, operator_mul_10_times)
{
    BigInteger answer("2432902008176640000");

    BigInteger x = 1;
    for (int i = 2; i <= 10; ++i) {
        x *= i;
    }
    EXPECT_TRUE(x == 3628800);

    BigInteger y = 1;
    for (int i = 11; i <= 20; ++i) {
        y *= i;
    }

    EXPECT_TRUE(x * y == answer);
}

TEST(Arithmetic, operator_div_10_times)
{
    BigInteger x("2432902008176640000");

    for (int i = 11; i <= 20; ++i) {
        x /= i;
    }
    EXPECT_EQ(3628800, x);

    BigInteger y("2432902008176640000");
    BigInteger z(y);
    z *= x;
    z *= y;

    z /= y;
    z /= x;
    EXPECT_EQ(z, y);

    z /= y;
    EXPECT_EQ(z, 1);
}

TEST(SimpleEfficiencyCheck, fibonacci_100)
{
    BigInteger F1 = 1;
    BigInteger F2 = 1;
    BigInteger F3;
    for (int i = 3; i < 101; ++i) {
        F3 = F1 + F2;
        F1 = F2;
        F2 = F3;
    }

    EXPECT_TRUE("354224848179261915075" == to_string(F3));
}

TEST(SimpleEfficiencyCheck, factorial_100)
{
    BigInteger f10 = 1;
    BigInteger f20 = 1;
    BigInteger f30 = 1;
    for (int i = 1; i < 11; ++i) {
        f10 = f10 * i;
        f20 *= (i + 10);
        f30 *= (i + 20);
    }

    BigInteger f100;
    f100 = f10 * f20 * f30;
    f100 = f100 / f10;
    f100 /= f20;
    EXPECT_TRUE(f100 == f30);

    for (int i = 21; i < 26; ++i) {
        f100 = f100 / i;
    }
    for (int i = 26; i < 30; ++i) {
        f100 /= i;
    }
    EXPECT_TRUE(f100 == 30);

    f100 /= 30;
    EXPECT_TRUE(f100 == 1);
}