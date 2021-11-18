//  The Fraction Class
//
//  Created by Tony Zheng on 2021-10-18.
//

#ifndef fraction_h
#define fraction_h

#include <iostream>
#include <fstream>
#include <stdio.h>

using namespace std;

class Fraction{                                 //fraction class
public:
    Fraction();                                 //constructor that takes in no parameters and sets numerator to 0 and denominator to 1 eg.
    Fraction(int);                              //constructor that takes in a numerator value and sets denominator value to 1 (eg. integer)
    Fraction(int, int);                         //constructor that takes in a numerator and denominator value (eg. fraction)
    int numerator() const;                      //numerator accessor
    int denominator() const;                    //denominator accessor
    int gcd(int, int);                          //method that returns the greatest common factor
    
    //overloading negation, preincrement and postincrement (members)
    Fraction operator- ();
    Fraction& operator++ ();
    Fraction operator++ (int unused);
    
    //overloading addition, subtraction, multiplication, division, addition and assignment, comparison operators, cout operator and cin operator (friends)
    friend Fraction operator+ (const Fraction& lhs, const Fraction& rhs);     
    friend Fraction operator- (const Fraction& lhs, const Fraction& rhs);
    friend Fraction operator* (const Fraction& lhs, const Fraction& rhs);
    friend Fraction operator/ (const Fraction& lhs, const Fraction& rhs);
    friend Fraction* operator+= (Fraction& lhs, const Fraction& rhs);
    friend bool operator< (const Fraction& lhs, const Fraction& rhs);
    friend bool operator<= (const Fraction& lhs, const Fraction& rhs);
    friend bool operator== (const Fraction& lhs, const Fraction& rhs);
    friend bool operator!= (const Fraction& lhs, const Fraction& rhs);
    friend bool operator> (const Fraction& lhs, const Fraction& rhs);
    friend bool operator>= (const Fraction& lhs, const Fraction& rhs);
    friend ostream& operator<< (ostream& out, const Fraction& val);
    friend istream& operator>> (istream& in, Fraction& ret);
private:
    int num;                                    //private variables to store numerator and denominator
    int denom;
};

class FractionException{                        //Fraction exception class
public:
    FractionException(const string&);
    string what() const;                        //print message when getting an error
private:
    string message;
};

#endif
