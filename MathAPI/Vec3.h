#ifndef VEC3_H
#define VEC3_H

//includes
#include <utility>

#include "Real.h"

/**
 * \brief This class is a visualization of a 3D vector, an object of data that saves values across 3 axis, x y and z,
 * and calculates with those values to represent a 3D world
 */
class Vec3 {
public:
    explicit Vec3(Real nx, Real ny, Real nz): x(std::move(nx)), y(std::move(ny)), z(std::move(nz)) {
    }

    template<arithmetic T,arithmetic K,arithmetic Z>
    explicit Vec3(T nx, K ny, Z nz) : x(nx), y(ny), z(nz) {
    }

    //Destructor
    ~Vec3() = default;

    //Copy and Move constructors

    Vec3(const Vec3& vector) = default;

    Vec3(Vec3&& vector) noexcept: x(std::move(vector.x)),y(std::move(vector.y)),z(std::move(vector.z)) {
    }

    //Copy and Move operators

    Vec3& operator =(const Vec3& vector) {
        if (this != &vector) {
            x(vector.x), y(vector.y), z(vector.z);
        }
        return *this;
    }

    Vec3& operator =(Vec3&& vector) noexcept {
        if (this != &vector) {
            x(vector.x), y(vector.y), z(vector.z);
            vector.x = vector.y = vector.z = 0;
        }
        return *this;
    }


    //Arithmetic operators

    Vec3 operator+(const Vec3& vector) const {
        return Vec3(x + vector.x, y + vector.y, z + vector.z);
    }

    Vec3 operator-(const Vec3& vector) const {
        return Vec3(x - vector.x, y - vector.y, z - vector.z);
    }

    Vec3 operator*(const Vec3& vector) const {
        return Vec3(x * vector.x, y * vector.y, z * vector.z);
    }

    Vec3 operator/(const Vec3& vector) const {
        return Vec3(x / vector.x, y / vector.y, z / vector.z);
    }

    //self arithmetics

    Vec3 operator+=(const Vec3& vector) {
        x += vector.x, y += vector.y, z += vector.z;
        return *this;
    }

    Vec3 operator-=(const Vec3& vector) {
        x -= vector.x, y -= vector.y, z -= vector.z;
        return *this;
    }

    Vec3 operator*=(const Vec3& vector) {
        x *= vector.x, y *= vector.y, z *= vector.z;
        return *this;
    }

    Vec3 operator/=(const Vec3& vector) {
        x /= vector.x, y /= vector.y, z /= vector.z;
        return *this;
    }

    //Arithetics with scalar values
    Vec3 operator+(const Real& number) const {
        return Vec3(x + number, y + number, z + number);
    }

    template<arithmetic T>
    Vec3 operator+(T number) const {
        return Vec3(x + number, y + number, z + number);
    }

    template<arithmetic T>
    Vec3 operator-(T number) const {
        return Vec3(x - number, y - number, z - number);
    }

    template<arithmetic T>
    Vec3 operator*(T number) const {
        return Vec3(x * number, y * number, z * number);
    }

    template<arithmetic T>
    Vec3 operator/(T number) const {
        return Vec3(x / number, y / number, z / number);
    }

    //self arithmetics

    template<arithmetic T>
    Vec3 operator+=(T number) {
        x += number, y += number, z += number;
        return *this;
    }

    template<arithmetic T>
    Vec3 operator-=(T number) {
        x -= number, y -= number, z -= number;
        return *this;
    }

    template<arithmetic T>
    Vec3 operator*=(T number) {
        x *= number, y *= number, z *= number;
        return *this;
    }

    template<arithmetic T>
    Vec3 operator/=(T number) {
        x /= number, y /= number, z /= number;
        return *this;
    }


    [[nodiscard]] Real getMagnitude() const {
        return Real(x.sqre() + y.sqre() + z.sqre()).sqrt();
    }

    void normalize() {
        const Real normal = getMagnitude();
        x /= normal;
        y /= normal;
        z /= normal;
    }

    void operator++() {
        const Real magn = getMagnitude() + 1;
        normalize();
        x *= magn, y *= magn, z *= magn;
    }

    void operator--() {
        const Real magn = getMagnitude() - 1;
        normalize();
        x *= magn, y *= magn, z *= magn;
    }

    /**
     * \brief A kind of play to a function call. this has no meaning other than me wanting to overload every possible
     *        operator there is
     * \return value of the Real
     */

    Real operator()(int index) const {
        if(index >= 3 || index <0) throw std::invalid_argument("index of a vec3 has to be 0,1,2");
        switch (index) {
            case 0: return x;
            case 1: return y;
            case 2: return z;
            default: throw std::invalid_argument("index is not either 0,1 or 2");
        }
    }


    // and of course changing the value by having any value in it
    void operator()(const Vec3& vec) {
        x = vec.x;
        y = vec.y;
        z = vec.z;
    }

    template<arithmetic T>
    void operator()(T xn, T yn, T zn) {
        x = xn;
        y = yn;
        z = zn;
    }

    Vec3* operator->() {
        return this;
    }

    Vec3* operator*() {
        return this;
    }

    //comparison operators

    bool operator==(const Vec3& vec) const {
        return x == vec.x && y == vec.y && z == vec.z;
    }

    bool operator<=(const Vec3& vec3) const {
        return x <= vec3.x && y <= vec3.y && z <= vec3.z;
    }

    bool operator>=(const Vec3& vec3) const {
        return x >= vec3.x && y >= vec3.y && z >= vec3.z;
    }

    bool operator<(const Vec3& vec3) const {
        return x < vec3.x && y < vec3.y && z < vec3.z;
    }

    bool operator>(const Vec3& vec3) const {
        return x > vec3.x && y > vec3.y && z > vec3.z;
    }


    //IO operators
    friend std::istream& operator>>(std::istream& in, Vec3& vec3) {
        in >> vec3.x;
        in >> vec3.y;
        return in >> vec3.z;
    }

    friend std::ostream& operator<<(std::ostream& out, const Vec3& vec3 ) {
        return out << vec3.x << ", "<< vec3.y << ", " << vec3.z << std::endl;
    }

    /**
     * This should be enough for now. if I find anything that needs to be implemented, I will do so after finding the
     * need and reason for it as well as document it properly
     */

private:
    Real x, y, z;
};


#endif //VEC3_H
