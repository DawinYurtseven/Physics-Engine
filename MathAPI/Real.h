#ifndef REAL_H
#define REAL_H

#include <cassert>
#include <concepts>
#include <format>
#include <iostream>


/**
 * Decleration of the type Real that only sets the floating point to a certain minimum to get to the number 0 better
 * differentiation of number 0 and small numbers therefore will be much easier
 */
#ifndef __DBL_MAX__
#	ifdef DBL_MAX // try to use it instead
#		define __DBL_MAX__ DBL_MAX
#	else // DBL_MAX
#		define __DBL_MAX__ 1.7976931348623158e+308
#	endif // DBL_MAX
#endif // __DBL_MAX__

#ifndef RealNumber
typedef double RealNumber;
#define FP_REAL_MAX __DBL_MAX__
#define VECTOR_EPSILON (1e-10)
#endif

template<typename T>
concept arithmetic = std::integral<T> || std::floating_point<T>;

class Real {
public:
    //Constructors

    /** I'd recommend you using RealNumber so that it will not go to any converting problems but Real is written so that
    *   it supports most of the operations if not a bit better
    *
    *   or at least that is what I attempt to do
     */
    explicit Real(RealNumber number) {
        value = number;
    }

    template<arithmetic T>
    explicit Real(T number) {
        value = static_cast<RealNumber>(number);
    }

    //Destructor
    ~Real() = default;

    //Copy and Move constructors

    Real(const Real& number) = default;

    Real(Real&& number) noexcept: value(number.value) {
    }

    //Copy and Move operators

    Real& operator =(const Real& number) {
        if (this != &number) {
            value = number.value;
        }
        return *this;
    }

    Real& operator =(Real&& number) noexcept {
        if (this != &number) {
            value = number.value;
            number.value = 0;
        }
        return *this;
    }

    //make the copy and move castable

    template<arithmetic T>
    Real& operator=(T const& number) {
        value = static_cast<RealNumber>(number);
        return *this;
    }

    template<arithmetic T>
    Real& operator =(T&& number) {
        value = static_cast<RealNumber>(number);
        return *this;
    }


    //Arithmetic operators

    Real operator+(const Real& number) const {
        return Real(value + number.value);
    }

    template<arithmetic T>
    Real operator+(T number) const {
        return Real(number + value);
    }

    Real operator-(const Real& number) const {
        return Real(value - number.value);
    }

    template<arithmetic T>
    Real operator-(T number) const {
        return Real(value - number);
    }

    Real operator*(const Real& number) const {
        return Real(value * number.value);
    }

    template<arithmetic T>
    Real operator*(T number) const {
        return Real(value * number);
    }

    Real operator/(const Real& number) const {
        return Real(value / number.value);
    }

    template<arithmetic T>
    Real operator/(T number) const {
        return Real(value / number);
    }

    //self arithmetics

    Real operator+=(const Real& number) {
        value += number.value;
        return *this;
    }

    template<arithmetic T>
    Real operator+=(T number) {
        value += number;
        return *this;
    }

    Real operator-=(const Real& number) {
        value -= number.value;
        return *this;
    }

    template<arithmetic T>
    Real operator-=(T number) {
        value -= number;
        return *this;
    }

    Real operator*=(const Real& number) {
        value *= number.value;
        return *this;
    }

    template<arithmetic T>
    Real operator*=(T number) {
        value *= number;
        return *this;
    }

    Real operator/=(const Real& number) {
        value /= number.value;
        return *this;
    }

    template<arithmetic T>
    Real operator/=(T number) {
        value /= number;
        return *this;
    }

    void operator++() {
        value += 1;
    }

    void operator--() {
        value -= 1;
    }

    /**
     * \brief A kind of play to a function call. this has no meaning other than me wanting to overload every possible
     *        operator there is
     * \return value of the Real
     */
    RealNumber operator()() const {
        return value;
    }

    // and of course changing the value by having any value in it
    void operator()(const Real& number) {
        value = number.value;
    }

    template<arithmetic T>
    void operator()(T number) {
        value = number.value;
    }

    Real* operator->() {
        return this;
    }

    Real* operator*() {
        return this;
    }

    //comparison operators

    bool operator==(const Real& number) const {
        return value == number.value;
    }

    template<arithmetic T>
    bool operator==(T number) const {
        return value == number;
    }

    bool operator<=(const Real& number) const {
        return value <= number.value;
    }

    template <arithmetic T>
    bool operator<=(T number) const {
        return value <= number;
    }

    bool operator>=(const Real& number) const {
        return value >= number.value;
    }

    template <arithmetic T>
    bool operator>=(T number) const {
        return value >= number;
    }

    bool operator<(const Real& number) const {
        return value < number.value;
    }

    template <arithmetic T>
    bool operator<(T number) const {
        return value < number;
    }

    bool operator>(const Real& number) const {
        return value > number.value;
    }

    template <arithmetic T>
    bool operator>(T number) const {
        return value > number;
    }


    //IO operators
    friend std::istream& operator>>(std::istream& in,Real& real ) {
        return  in >> real.value;
    }

    friend std::ostream& operator<<(std::ostream& out, const Real& real) {
        return out << std::format("{}", real());
    }

    /**
     * This should be enough for now. if I find anything that needs to be implemented, I will do so after finding the
     * need and reason for it as well as document it properly
     */

    [[nodiscard]] Real sqre() const {
        return Real(value*value);
    }

    [[nodiscard]] Real sqrt() const {
        assert(value >= 0);
        if(value == 0.0) return Real(0);
        RealNumber hi = value;
        RealNumber lo = 0;
        RealNumber guess = hi/2;
        while(abs(guess * guess - value)/guess > 0.0000000001) {
            if (guess*guess > value){
                hi = guess;
            }

            else {
                lo = guess;
            }

            guess = (hi + lo)/2;
        }
        return Real(guess);
    }

private:
    RealNumber value{};
};



#endif //REAL_H
