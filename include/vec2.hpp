#ifndef VEC2_HPP
#define VEC2_HPP

#include <cmath>
#include <iostream>

class Vec2 {
public:
    double x, y;

    // Constructors
    Vec2() : x(0), y(0) {}
    Vec2(double x, double y) : x(x), y(y) {}

    // Compound assignment operators
    Vec2& operator+=(const Vec2& other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    Vec2& operator-=(const Vec2& other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    Vec2& operator*=(double scalar) {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    Vec2& operator/=(double scalar) {
        if (scalar != 0) {
            x /= scalar;
            y /= scalar;
        }
        else {
            throw std::runtime_error("Division by zero error.");
        }
        return *this;
    }

    // Basic arithmetic operators
    Vec2 operator+(const Vec2& other) const {
        return Vec2(x + other.x, y + other.y);
    }

    Vec2 operator-(const Vec2& other) const {
        return Vec2(x - other.x, y - other.y);
    }

    Vec2 operator*(double scalar) const {
        return Vec2(x * scalar, y * scalar);
    }

    // New operator for element-wise Vec2 * Vec2 multiplication
    Vec2 operator*(const Vec2& other) const {
        return Vec2(x * other.x, y * other.y);
    }

    Vec2 operator/(double scalar) const {
        if (scalar != 0) {
            return Vec2(x / scalar, y / scalar);
        }
        else {
            throw std::runtime_error("Division by zero error.");
        }
    }

    // Dot product
    double Dot(const Vec2& other) const {
        return x * other.x + y * other.y;
    }

    // Length/magnitude of the vector
    double Length() const {
        return std::sqrt(x * x + y * y);
    }

    // Distance between two vectors
    double Distance(const Vec2& other) const {
        double dx = x - other.x;
        double dy = y - other.y;
        return std::sqrt(dx * dx + dy * dy);
    }

    // Normalize the vector
    Vec2 Normalize() const {
        double len = Length();
        return len > 0 ? Vec2(x / len, y / len) : Vec2(0, 0);
    }

    // Equality operator
    bool operator==(const Vec2& other) const {
        return x == other.x && y == other.y;
    }

    // Friend function to allow std::ostream to print the vector
    friend std::ostream& operator<<(std::ostream& os, const Vec2& vec) {
        os << "(" << vec.x << ", " << vec.y << ")";
        return os;
    }
};

#endif
