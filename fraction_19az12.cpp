//  The Fraction Class
//
//  Created by Tony Zheng on 2021-10-18.
//

#include <fstream>
#include "fraction_19az12.h"

//constructors
Fraction::Fraction() : num(0), denom(1) {}

Fraction::Fraction(int numerator) : num(numerator), denom(1) {}

Fraction::Fraction(int numerator, int denominator) {
    if(denominator == 0){
        throw FractionException("Fraction cannot have denominator of 0");
    }
    int divisor = gcd(abs(numerator), abs(denominator));
    num = numerator/divisor;
    denom = denominator/divisor;
    if(num < 0 && denom < 0){
        num = abs(num);
        denom = abs(denom);
    }
    if(denom < 0){
        denom = abs(denom);
        num = -num;
    }
}

int Fraction::numerator() const{
    return num;
}

int Fraction::denominator() const{
    return denom;
}
                         
int Fraction::gcd(int n, int m) {
    if(m <= n && (n % m == 0)){
        return m;
    }
    else if(n < m){
        return gcd(m, n);
    }
    else{
        return gcd(m, n % m);
    }
}

Fraction Fraction::operator- () {
    return Fraction(-num, denom);
}

Fraction& Fraction::operator++ () {
    num = num + denom;
    return *this;
}

Fraction Fraction::operator++ (int unused){
    Fraction clone(num, denom);
    num = num + denom;
    return clone;
}

Fraction operator+ (const Fraction& lhs, const Fraction& rhs) {
    if(rhs.denominator() == lhs.denominator()){
        return Fraction((lhs.numerator() + rhs.numerator()), lhs.denominator());
    }
    else{
        return Fraction((lhs.numerator() * rhs.denominator() + rhs.numerator() * lhs.denominator()), rhs.denominator() * lhs.denominator());
    }
}

Fraction operator- (const Fraction& lhs, const Fraction& rhs) {
    if(rhs.denominator() == lhs.denominator()){
        return Fraction(lhs.numerator() - rhs.numerator(), lhs.denominator());
    }
    else{
        return Fraction((lhs.numerator() * rhs.denominator() - rhs.numerator() * lhs.denominator()), rhs.denominator() * lhs.denominator());
    }
}

Fraction operator* (const Fraction& lhs, const Fraction& rhs) {
    return Fraction(lhs.numerator() * rhs.numerator(), lhs.denominator() * rhs.denominator());
}

Fraction operator/ (const Fraction& lhs, const Fraction& rhs) {
    return Fraction(lhs.numerator() * rhs.denominator(), lhs.denominator() * rhs.numerator());
}

Fraction* operator+= (Fraction& lhs, const Fraction& rhs){
    Fraction *pleft = &lhs;
    *pleft = lhs + rhs;
    return pleft;
}

bool operator< (const Fraction& lhs, const Fraction& rhs) {
    return(lhs.numerator() * rhs.denominator() < rhs.numerator() * lhs.denominator());
}

bool operator<= (const Fraction& lhs, const Fraction& rhs) {
    return(lhs.numerator() * rhs.denominator() <= rhs.numerator() * lhs.denominator());
}

bool operator== (const Fraction& lhs, const Fraction& rhs) {
    return(lhs.numerator() * rhs.denominator() == rhs.numerator() * lhs.denominator());
}

bool operator!= (const Fraction& lhs, const Fraction& rhs) {
    return(lhs.numerator() * rhs.denominator() != rhs.numerator() * lhs.denominator());
}

bool operator> (const Fraction& lhs, const Fraction& rhs) {
    return(lhs.numerator() * rhs.denominator() > rhs.numerator() * lhs.denominator());
}

bool operator>= (const Fraction& lhs, const Fraction& rhs) {
    return(lhs.numerator() * rhs.denominator() >= rhs.numerator() * lhs.denominator());
}

ostream& operator<< (ostream& out, const Fraction& val) {
    out << val.numerator() << "/" << val.denominator();
    return out;
}

istream& operator>> (istream& in, Fraction& ret) {
    string input;
    in >> input;
    unsigned long location = input.find('/');
    if(location == -1){
        ret.num = stoi(input);
        ret.denom = 1;
    }
    else{
        ret.num = stoi(input.substr(0, location));
        ret.denom = stoi(input.substr(location + 1, input.find('\0')));
    }
    cout << ret;
    return in;
}

FractionException::FractionException(const string& m) : message(m) {}

string FractionException::what() const{
    return message;
}


int main() {
    // Test constructors and << operator overloading
    Fraction test1;
    cout << "Should be \"0/1\": " << test1 << endl;
    Fraction test2(4);
    cout << "Should be \"4/1\": " << test2 << endl;
    Fraction test3(20, 30);
    cout << "Should be \"2/3\": " << test3 << endl;
    Fraction test4(210, -60);
    cout << "Should be \"-7/2\": " << test4 << endl;

    // Test exception for when denominator is zero
    try {
        Fraction test5(4, 0);
        cout << "Should not get here: " << test5 << endl;
    } catch (FractionException &e) {
        cout << "Exception message should indicate illegal denominator: " << e.what() << endl;
    }

    // Test accessors
    cout << "Numerator should be -7: " << test4.numerator() << endl;
    cout << "Denominator should be 2: " << test4.denominator() << endl;

    // Test binary arithmetic operators
    Fraction test6(9, 8);
    Fraction test7(1, 6);
    Fraction test8 = test6 + test7;
    cout << "Should be \"31/24\": " << test8 << endl;
    Fraction test9 = test6 - test7;
    cout << "Should be \"23/24\": " << test9 << endl;
    Fraction test10 = test6 - 1;
    cout << "Should be \"1/8\": " << test10 << endl;
    Fraction test11 = 2 - test7;
    cout << "Should be \"11/6\": " << test11 << endl;
    Fraction test12 = test6 * test7;
    cout << "Should be \"3/16\": " << test12 << endl;
    Fraction test13 = test6 / test7;
    cout << "Should be \"27/4\": " << test13 << endl;

    // Test unary negation
    cout << "Should be \"-1/6\": " << -test7 << endl;

    // Test pre and post-increment operators
    Fraction test14 = 2 + test3++;
    cout << "Should be \"8/3\": " << test14 << endl;
    cout << "Should be \"5/3\": " << test3 << endl;
    Fraction test15 = 2 + ++test3;
    cout << "Should be \"14/3\": " << test15 << endl;
    cout << "Should be \"8/3\": " << test3 << endl;

    // Test += operator
    Fraction test16(3, 8);
    test16 += test3;
    cout << "Should be \"73/24\": " << test16 << endl;

    // Test comparisons
    cout << "\nShould see six comparison test results:" << endl;
    Fraction test17(9, 8);
    if (test6 == test17)
        cout << "Equality test passed." << endl;
    if (test6 != test7)
        cout << "Inequality test passed." << endl;
    if (test6 > test7 && test6 >= test7)
        cout << "Greater than test passed." << endl;
    if (test7 < test6 && test7 <= test6)
        cout << "Less than test passed." << endl;
    if (test6 > 1)
        cout << "Mixed type comparison passed." << endl;
    if (1 < test6)
        cout << "Second mixed type comparison passed." << endl;

    // Test input, exception and +=:
    Fraction sum(0);
    Fraction fin;
    cout << "\nSumming fractions. Enter fractions as \"1/2\" or just enter a single integer." << endl;
    cout << "Enter zero to end the summation:" << endl;
    do {
        cout << "Enter a fraction to add to sum: ";
        try {
            cin >> fin;
            sum += fin;
        } catch (FractionException &e) {
            cout << e.what() << endl;
        }
    } while (fin != 0);
    cout << "Sum is: " << sum << endl;

    return 0;
}
