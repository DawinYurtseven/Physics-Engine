//
// Created by dawin on 12.12.2023.
//

#ifndef REAL_H
#define REAL_H
#include <concepts>
#include <iostream>


/**
 * Decleration of the type Real that only sets the floating point to a certain minimum to get to the number 0 better
 * differentiation of number 0 and small numbers therefore will be much easier
 */
#if FLOATINGPOINT_PRECISION==1
typedef float RealNumber;
#define FP_REAL_MAX __FLT_MAX__
#define VECTOR_EPSILON (1e-5f)
#else
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


    //Copy and Move constructors

    Real(const Real& number) {
        value = number.value;
    }

    Real(Real&& number) noexcept {
        value = number.value;
    }

    //Copy and Move operators

    Real& operator =(Real const& number) = default;

    Real& operator =(Real&& number) noexcept = default;

    //String operator



    //Arithmetic operators




    [[nodiscard]] RealNumber getValue() const {
        return value;
    }
private:
    RealNumber value{};
};

inline std::ostream& operator<<(std::ostream& out, const Real& real) {
    return out<<real.getValue();
}

#endif //REAL_H
