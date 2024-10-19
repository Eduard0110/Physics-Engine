#ifndef VEC2_HPP
#define VEC2_HPP


#include <cmath>
#include <iostream>

class Vec2 {
public:
    double x, y;

    Vec2() : x(0), y(0) {}
    Vec2(double x, double y) : x(x), y(y) {}

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

    Vec2 operator+(const Vec2& other) const {
        return Vec2(x + other.x, y + other.y);
    }

    Vec2 operator-(const Vec2& other) const {
        return Vec2(x - other.x, y - other.y);
    }

    Vec2 operator*(double scalar) const {
        return Vec2(x * scalar, y * scalar);
    }

    double Dot(const Vec2& other) const {
        return x * other.x + y * other.y;
    }

    double Length() const {
        return std::sqrt(x * x + y * y);
    }

    Vec2 Normalize() const {
        double len = Length();
        return len > 0 ? Vec2(x / len, y / len) : Vec2(0, 0);
    }

    bool operator==(const Vec2& other) const {
        return x == other.x && y == other.y;
    }

    friend std::ostream& operator<<(std::ostream& os, const Vec2& vec) {
        os << "(" << vec.x << ", " << vec.y << ")";
        return os;
    }
};

#endif