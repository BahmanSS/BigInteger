# 💥 BigInteger
![License](https://img.shields.io/badge/license-MIT-blue.svg)
![C++](https://img.shields.io/badge/language-C++17-blue)
![Status](https://img.shields.io/badge/status-active-brightgreen)

## 🚀 Contents
[Description](#Description)

[Operators](#Operators)

[Methods](#Methods)

[Mathematical algorithms used](#Mathematical)


## 📖 <a id="Description">Description</a>
I started this project as part of my studies at **SPBU** (Programme Programming and Information Technologies programme) !

This project will describe **BigInteger** class in **C++** programming language

The BigInteger class is used for arithmetic operations with *veeeeeeeeeeeeeeeeery large* numbers (up to several thousand bits).
It allows storing values that go beyond primitive data types such as int and long.

The goal is to perfect the project, i.e. to optimise the work of most methods, to write tests for the BigInteger class, to design the repository properly and to perfect the work with cmake.

When the project is finished and ready, there will be a tick !!! ❌

## 🔧 <a id="Operators">Operators</a>
| Category               | Operator                          | Description                      | Implemented |
| ---------------------- | --------------------------------- | -------------------------------- | ----------- |
| 📥 Input / Output      | `operator<<`                      | Output to `std::ostream`         | ❌          |
|                        | `operator>>`                      | Input from `std::istream`        | ❌           |
| 📐 Arithmetic          | `operator+`                       | Addition                        | 🔄           |
|                        | `operator-`                       | Subtraction                      | 🔄           |
|                        | `operator*`                       | Multiplication                   | 🔄           |
|                        | `operator/`                       | Integer division                 | 🔄           |
|                        | `operator%`                       | Remainder                        | 🔄           |
|                        | `operator-()`                     | Unary minus                      | 🔄           |
| 📈 Increment/Decrement | `operator++`                      | Prefix / postfix increment       | 🔄          |
|                        | `operator--`                      | Prefix / postfix decrement       | 🔄           |
| 🟰 Assignment          | `operator=`                       | Assignment                       | 🔄           |
|                        | `operator+=`                      | Addition assignment              | 🔄           |
|                        | `operator-=`                      | Subtraction assignment           | 🔄           |
|                        | `operator*=`                      | Multiplication assignment        | 🔄           |
|                        | `operator/=`                      | Division assignment              | 🔄           |
|                        | `operator%=`                      | Modulo assignment                | 🔄           |
| 🧮 Comparison          | `operator==`                      | Equality                         | 🔄           |
|                        | `operator!=`                      | Inequality                       | 🔄           |
|                        | `operator<`                       | Less than                        | 🔄           |
|                        | `operator<=`                      | Less than or equal               | 🔄           |
|                        | `operator>`                       | Greater than                     | 🔄           |
|                        | `operator>=`                      | Greater than or equal            | 🔄           |



## 🛠️ <a id="Methods">Methods</a>
| Method Signature                                                           | Description                                             | Implemented |
| -------------------------------------------------------------------------- | ------------------------------------------------------- | ----------- |
| `BigInteger mod(const BigInteger& other) const`                            | Returns remainder after division (modulo)               | ❌         |
| `std::string to_string() const`                                            | Returns decimal string representation                   | 🔄           |
| `std::string to_hex() const`                                               | Returns hexadecimal string representation               | 🔄           |
| `BigInteger pow(unsigned int exp) const`                                   | Returns this number raised to power `exp`               | ❌           |

## 🧠 <a id="Mathematical">Mathematical algorithms used</a>
TODO
