#include "figures.hpp"

template <Scalar T>
Point<T>::Point(T x_, T y_) : x(x_), y(y_) {}

template <Scalar T>
std::ostream &operator<<(std::ostream &os, const Point<T> &p)
{
    os << '(' << p.x << ", " << p.y << ')';
    return os;
}

template <Scalar T>
std::istream &operator>>(std::istream &is, Point<T> &p)
{
    is >> p.x >> p.y;
    return is;
}

template <Scalar T>
Figure<T>::operator double() const { return area(); }

template <Scalar T>
std::ostream &operator<<(std::ostream &os, const Figure<T> &f)
{
    f.print(os);
    return os;
}

template <Scalar T>
bool operator==(const Figure<T> &lhs, const Figure<T> &rhs)
{
    return std::abs(lhs.area() - rhs.area()) < 1e-7;
}

template <Scalar T>
bool operator<(const Figure<T> &lhs, const Figure<T> &rhs)
{
    return lhs.area() < rhs.area();
}

template <Scalar T, std::size_t N>
RegularPolygon<T, N>::RegularPolygon()
{
    build_from_center_radius(Point<T>(0, 0), static_cast<T>(1));
}

template <Scalar T, std::size_t N>
RegularPolygon<T, N>::RegularPolygon(const Point<T> &c, T r)
{
    if (r <= 0)
        throw std::invalid_argument("Radius must be positive");
    build_from_center_radius(c, r);
}

template <Scalar T, std::size_t N>
RegularPolygon<T, N>::RegularPolygon(const RegularPolygon &o)
{
    for (size_t i = 0; i < N; ++i)
        vertices_[i] = std::make_unique<Point<T>>(*o.vertices_[i]);
}

template <Scalar T, std::size_t N>
RegularPolygon<T, N> &RegularPolygon<T, N>::operator=(const RegularPolygon &o)
{
    if (this == &o)
        return *this;
    for (size_t i = 0; i < N; ++i)
        vertices_[i] = std::make_unique<Point<T>>(*o.vertices_[i]);
    return *this;
}

template <Scalar T, std::size_t N>
void RegularPolygon<T, N>::build_from_center_radius(const Point<T> &c, T r)
{
    const double step = 2.0 * std::numbers::pi_v<double> / static_cast<double>(N);
    double a = 0.0;
    for (size_t i = 0; i < N; ++i)
    {
        double x = c.x + r * std::cos(a);
        double y = c.y + r * std::sin(a);
        vertices_[i] = std::make_unique<Point<T>>(x, y);
        a += step;
    }
}

template <Scalar T, std::size_t N>
double RegularPolygon<T, N>::area() const
{
    double sum = 0.0;
    for (size_t i = 0; i < N; ++i)
    {
        const auto &p1 = *vertices_[i];
        const auto &p2 = *vertices_[(i + 1) % N];
        sum += p1.x * p2.y - p2.x * p1.y;
    }
    return std::abs(sum) / 2.0;
}

template <Scalar T, std::size_t N>
Point<T> RegularPolygon<T, N>::center() const
{
    double sx = 0, sy = 0;
    for (auto &v : vertices_)
    {
        sx += v->x;
        sy += v->y;
    }
    return Point<T>(sx / N, sy / N);
}

template <Scalar T, std::size_t N>
void RegularPolygon<T, N>::print(std::ostream &os) const
{
    os << N << "-gon\n";
    for (size_t i = 0; i < N; ++i)
        os << "  " << *vertices_[i] << "\n";
    os << "Area: " << area() << "\n";
}

template <Scalar T, std::size_t N>
RegularPolygon<T, N>::operator double() const
{
    return area();
}

template <Scalar T, std::size_t N>
std::istream &operator>>(std::istream &is, RegularPolygon<T, N> &poly)
{
    Point<T> c;
    T r;
    is >> c.x >> c.y >> r;
    poly.build_from_center_radius(c, r);
    return is;
}

template <class T>
Array<T>::Array() : size_(0), capacity_(0), data_(nullptr) {}

template <class T>
Array<T>::Array(std::size_t cap) : size_(0), capacity_(cap)
{
    if (cap)
        data_.reset(new T[cap], std::default_delete<T[]>());
}

template <class T>
Array<T>::Array(const Array &o) : size_(o.size_), capacity_(o.capacity_)
{
    data_.reset(new T[capacity_], std::default_delete<T[]>());
    for (size_t i = 0; i < size_; ++i)
        data_[i] = o.data_[i];
}

template <class T>
Array<T> &Array<T>::operator=(const Array &o)
{
    if (this == &o)
        return *this;
    Array tmp(o);
    *this = std::move(tmp);
    return *this;
}

template <class T>
void Array<T>::push_back(const T &v)
{
    ensure_capacity(size_ + 1);
    data_[size_++] = v;
}

template <class T>
void Array<T>::erase(std::size_t i)
{
    if (i >= size_)
        throw std::out_of_range("erase");
    for (size_t j = i; j + 1 < size_; ++j)
        data_[j] = std::move(data_[j + 1]);
    --size_;
}

template <class T>
std::size_t Array<T>::size() const noexcept { return size_; }

template <class T>
std::size_t Array<T>::capacity() const noexcept { return capacity_; }

template <class T>
T &Array<T>::operator[](std::size_t i)
{
    if (i >= size_)
        throw std::out_of_range("[]");
    return data_[i];
}
template <class T>
const T &Array<T>::operator[](std::size_t i) const
{
    if (i >= size_)
        throw std::out_of_range("[]");
    return data_[i];
}

template <class T>
void Array<T>::ensure_capacity(std::size_t newSize)
{
    if (newSize <= capacity_)
        return;
    size_t newCap = capacity_ ? capacity_ * 2 : 1;
    if (newCap < newSize)
        newCap = newSize;
    std::shared_ptr<T[]> newData(new T[newCap], std::default_delete<T[]>());
    for (size_t i = 0; i < size_; ++i)
        newData[i] = std::move(data_[i]);
    data_ = std::move(newData);
    capacity_ = newCap;
}

template <Scalar T>
double total_area(const Array<std::shared_ptr<Figure<T>>> &arr)
{
    double sum = 0;
    for (size_t i = 0; i < arr.size(); ++i)
        if (arr[i])
            sum += static_cast<double>(*arr[i]);
    return sum;
}


template struct Point<int>;
template struct Point<double>;

template class RegularPolygon<double, 5>;
template class RegularPolygon<double, 6>;
template class RegularPolygon<double, 8>;

template class Array<std::shared_ptr<Figure<double>>>;

template class Array<Figure<int> *>;

template double total_area<double>(const Array<std::shared_ptr<Figure<double>>> &);

template std::ostream &operator<< <double>(std::ostream &, const Figure<double> &);
template bool operator== <double>(const Figure<double> &, const Figure<double> &);
template bool operator< <double>(const Figure<double> &, const Figure<double> &);
