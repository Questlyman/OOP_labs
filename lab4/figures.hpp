#pragma once
#include <iostream>
#include <memory>
#include <array>
#include <cmath>
#include <concepts>
#include <numbers>
#include <stdexcept>

template <typename T>
concept Scalar = std::is_arithmetic_v<T>;

template <Scalar T>
struct Point
{
    T x{}, y{};
    Point() = default;
    Point(T x_, T y_);
};

template <Scalar T>
std::ostream &operator<<(std::ostream &os, const Point<T> &p);
template <Scalar T>
std::istream &operator>>(std::istream &is, Point<T> &p);

template <Scalar T>
class Figure
{
public:
    virtual ~Figure() = default;
    virtual double area() const = 0;
    virtual Point<T> center() const = 0;
    virtual void print(std::ostream &) const = 0;
    explicit virtual operator double() const;
};

template <Scalar T>
std::ostream &operator<<(std::ostream &os, const Figure<T> &f);
template <Scalar T>
bool operator==(const Figure<T> &lhs, const Figure<T> &rhs);
template <Scalar T>
bool operator<(const Figure<T> &lhs, const Figure<T> &rhs);

template <Scalar T, std::size_t N>
class RegularPolygon : public Figure<T>
{
public:
    RegularPolygon();
    RegularPolygon(const Point<T> &center, T radius);
    RegularPolygon(const RegularPolygon &other);
    RegularPolygon &operator=(const RegularPolygon &other);

    double area() const override;
    Point<T> center() const override;
    void print(std::ostream &) const override;
    explicit operator double() const override;

    template <Scalar U, std::size_t M>
    friend std::istream &operator>>(std::istream &, RegularPolygon<U, M> &);

protected:
    std::array<std::unique_ptr<Point<T>>, N> vertices_;
    void build_from_center_radius(const Point<T> &center, T radius);
};

template <Scalar T, std::size_t N>
std::istream &operator>>(std::istream &is, RegularPolygon<T, N> &poly);

template <Scalar T>
class Pentagon : public RegularPolygon<T, 5>
{
public:
    using RegularPolygon<T, 5>::RegularPolygon;
};
template <Scalar T>
class Hexagon : public RegularPolygon<T, 6>
{
public:
    using RegularPolygon<T, 6>::RegularPolygon;
};
template <Scalar T>
class Octagon : public RegularPolygon<T, 8>
{
public:
    using RegularPolygon<T, 8>::RegularPolygon;
};

template <class T>
class Array
{
public:
    Array();
    explicit Array(std::size_t capacity);
    Array(const Array &other);
    Array &operator=(const Array &other);

    void push_back(const T &value);
    void erase(std::size_t index);
    std::size_t size() const noexcept;
    std::size_t capacity() const noexcept;
    T &operator[](std::size_t index);
    const T &operator[](std::size_t index) const;

private:
    void ensure_capacity(std::size_t newSize);
    std::shared_ptr<T[]> data_;
    std::size_t size_;
    std::size_t capacity_;
};

template <Scalar T>
double total_area(const Array<std::shared_ptr<Figure<T>>> &arr);
