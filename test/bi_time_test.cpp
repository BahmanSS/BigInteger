#include <iostream>
#include "res/timer.hpp"
#include "../src/biginteger.hpp"

void add_fib(int n);
void fact_mult_eq(int n);

int main() {
    Timer tm;
   { // Сложение fib(100000)
    tm.start();

    add_fib(100000);

    tm.stop();
    std::cout << "Addition fib( 100_000 ): " << tm.microseconds() << " microseconds! \n";
   } 
   { // Умножение *= 3000!
    tm.start();

    fact_mult_eq(3000);

    tm.stop();
    std::cout << "Multiplication ( *= 3000! ): " << tm.microseconds() << " microseconds! \n";
   }
   { // Умножение * 3000!

   }


   
}

void add_fib(int n) {
    if (n == 0) { return; }
    if (n == 1) { return; }

    BigInteger a = 0;
    BigInteger b = 1;

    for (int i = 2; i <= n; ++i) {
        BigInteger next = a + b;
        a = b;
        b = next;
    }
}

void fact_mult_eq(int n) {
    if (n < 2) { return; }

    BigInteger result = 1;
    for (int i = 2; i <= n; ++i) {
        result *= i;
    }
}