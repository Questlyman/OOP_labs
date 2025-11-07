#include <gtest/gtest.h>
#include <cmath>
#include <numbers>

#include "figures.hpp"

// Удобный epsilon для сравнения double
constexpr double EPS = 1e-6;

// ------------------------------
// Тесты для Point
// ------------------------------

TEST(PointTest, ConstructAndAssign)
{
    Point<double> p1; // по умолчанию
    EXPECT_DOUBLE_EQ(p1.x, 0.0);
    EXPECT_DOUBLE_EQ(p1.y, 0.0);

    Point<double> p2(3.5, -1.2);
    EXPECT_DOUBLE_EQ(p2.x, 3.5);
    EXPECT_DOUBLE_EQ(p2.y, -1.2);

    p1 = p2;
    EXPECT_DOUBLE_EQ(p1.x, 3.5);
    EXPECT_DOUBLE_EQ(p1.y, -1.2);
}

// ------------------------------
// Вспомогательная функция: площадь правильного n-угольника радиуса r
// ------------------------------
double regular_polygon_area_formula(std::size_t n, double r)
{
    // A = 1/2 * n * r^2 * sin(2π/n)
    return 0.5 * static_cast<double>(n) * r * r *
           std::sin(2.0 * std::numbers::pi_v<double> / static_cast<double>(n));
}

// ------------------------------
// Тесты для Pentagon<double>
// ------------------------------

TEST(PentagonTest, AreaMatchesFormula)
{
    Point<double> c{0.0, 0.0};
    double r = 2.0;
    Pentagon<double> p(c, r);

    double expected = regular_polygon_area_formula(5, r);
    EXPECT_NEAR(p.area(), expected, EPS);
}

TEST(PentagonTest, CenterIsCorrect)
{
    Point<double> c{1.0, -2.0};
    double r = 3.0;
    Pentagon<double> p(c, r);

    Point<double> center = p.center();
    EXPECT_NEAR(center.x, c.x, EPS);
    EXPECT_NEAR(center.y, c.y, EPS);
}

TEST(PentagonTest, CastToDoubleReturnsArea)
{
    Point<double> c{0.0, 0.0};
    double r = 1.5;
    Pentagon<double> p(c, r);

    Figure<double> &f = p;
    double area_direct = f.area();
    double area_cast = static_cast<double>(f);

    EXPECT_NEAR(area_cast, area_direct, EPS);
}

TEST(PentagonTest, ComparisonOperators)
{
    Point<double> c{0.0, 0.0};

    Pentagon<double> p1(c, 1.0);
    Pentagon<double> p2(c, 1.0);
    Pentagon<double> p3(c, 2.0);

    Figure<double> &f1 = p1;
    Figure<double> &f2 = p2;
    Figure<double> &f3 = p3;

    EXPECT_TRUE(f1 == f2);
    EXPECT_FALSE(f1 < f2);
    EXPECT_TRUE(f1 < f3);
}

// ------------------------------
// Тесты для Hexagon<double>
// ------------------------------

TEST(HexagonTest, AreaMatchesFormula)
{
    Point<double> c{0.0, 0.0};
    double r = 4.0;
    Hexagon<double> h(c, r);

    double expected = regular_polygon_area_formula(6, r);
    EXPECT_NEAR(h.area(), expected, EPS);
}

TEST(HexagonTest, CenterIsCorrect)
{
    Point<double> c{2.0, 3.0};
    double r = 5.0;
    Hexagon<double> h(c, r);

    Point<double> center = h.center();
    EXPECT_NEAR(center.x, c.x, EPS);
    EXPECT_NEAR(center.y, c.y, EPS);
}

// ------------------------------
// Тесты для Octagon<double>
// ------------------------------

TEST(OctagonTest, AreaMatchesFormula)
{
    Point<double> c{0.0, 0.0};
    double r = 1.0;
    Octagon<double> o(c, r);

    double expected = regular_polygon_area_formula(8, r);
    EXPECT_NEAR(o.area(), expected, EPS);
}

TEST(OctagonTest, CenterIsCorrect)
{
    Point<double> c{-3.0, 7.0};
    double r = 2.5;
    Octagon<double> o(c, r);

    Point<double> center = o.center();
    EXPECT_NEAR(center.x, c.x, EPS);
    EXPECT_NEAR(center.y, c.y, EPS);
}

// ------------------------------
// Тесты для Array<std::shared_ptr<Figure<double>>>
// ------------------------------

TEST(ArrayTest, PushBackAndSize)
{
    Array<std::shared_ptr<Figure<double>>> arr;

    EXPECT_EQ(arr.size(), 0u);

    auto p1 = std::make_shared<Pentagon<double>>(Point<double>{0.0, 0.0}, 1.0);
    auto p2 = std::make_shared<Hexagon<double>>(Point<double>{1.0, 1.0}, 2.0);

    arr.push_back(p1);
    EXPECT_EQ(arr.size(), 1u);
    EXPECT_EQ(arr[0], p1);

    arr.push_back(p2);
    EXPECT_EQ(arr.size(), 2u);
    EXPECT_EQ(arr[1], p2);
}

TEST(ArrayTest, DynamicGrowthAndMoveOnRealloc)
{
    // Специально начинаем с маленькой capacity, чтобы проверить расширение
    Array<std::shared_ptr<Figure<double>>> arr;

    auto p1 = std::make_shared<Pentagon<double>>(Point<double>{0.0, 0.0}, 1.0);
    auto p2 = std::make_shared<Hexagon<double>>(Point<double>{0.0, 0.0}, 2.0);
    auto p3 = std::make_shared<Octagon<double>>(Point<double>{0.0, 0.0}, 3.0);

    arr.push_back(p1);
    arr.push_back(p2);
    arr.push_back(p3);

    EXPECT_EQ(arr.size(), 3u);
    // Проверяем, что элементы на месте и не потерялись при расширении
    EXPECT_EQ(arr[0], p1);
    EXPECT_EQ(arr[1], p2);
    EXPECT_EQ(arr[2], p3);
}

TEST(ArrayTest, EraseByIndex)
{
    Array<std::shared_ptr<Figure<double>>> arr;

    auto p1 = std::make_shared<Pentagon<double>>(Point<double>{0.0, 0.0}, 1.0);
    auto p2 = std::make_shared<Hexagon<double>>(Point<double>{0.0, 0.0}, 2.0);
    auto p3 = std::make_shared<Octagon<double>>(Point<double>{0.0, 0.0}, 3.0);

    arr.push_back(p1);
    arr.push_back(p2);
    arr.push_back(p3);

    ASSERT_EQ(arr.size(), 3u);

    // Удаляем средний элемент
    arr.erase(1);
    EXPECT_EQ(arr.size(), 2u);

    // Теперь на позиции 1 должен быть ранее последний (p3)
    EXPECT_EQ(arr[0], p1);
    EXPECT_EQ(arr[1], p3);

    // Проверяем, что удаление вне диапазона кидает исключение
    EXPECT_THROW(arr.erase(10), std::out_of_range);
}

TEST(ArrayTest, IndexOperatorThrowsOnOutOfRange)
{
    Array<std::shared_ptr<Figure<double>>> arr;
    auto p1 = std::make_shared<Pentagon<double>>(Point<double>{0.0, 0.0}, 1.0);
    arr.push_back(p1);

    EXPECT_NO_THROW(arr[0]);
    EXPECT_THROW(arr[1], std::out_of_range);
}

// ------------------------------
// Тест total_area
// ------------------------------

TEST(TotalAreaTest, SumOfAllFigures)
{
    Array<std::shared_ptr<Figure<double>>> arr;

    auto p = std::make_shared<Pentagon<double>>(Point<double>{0.0, 0.0}, 1.0);
    auto h = std::make_shared<Hexagon<double>>(Point<double>{0.0, 0.0}, 2.0);
    auto o = std::make_shared<Octagon<double>>(Point<double>{0.0, 0.0}, 3.0);

    double area_p = p->area();
    double area_h = h->area();
    double area_o = o->area();

    arr.push_back(p);
    arr.push_back(h);
    arr.push_back(o);

    double sum = total_area(arr);
    double expected = area_p + area_h + area_o;

    EXPECT_NEAR(sum, expected, EPS);
}

// ------------------------------
// Тест на полиморфизм через Figure<double>
// ------------------------------

TEST(PolymorphismTest, DifferentFiguresThroughBasePointer)
{
    Array<std::shared_ptr<Figure<double>>> arr;

    std::shared_ptr<Figure<double>> f1 =
        std::make_shared<Pentagon<double>>(Point<double>{0.0, 0.0}, 1.0);
    std::shared_ptr<Figure<double>> f2 =
        std::make_shared<Hexagon<double>>(Point<double>{1.0, 1.0}, 1.5);
    std::shared_ptr<Figure<double>> f3 =
        std::make_shared<Octagon<double>>(Point<double>{-2.0, 0.5}, 0.5);

    arr.push_back(f1);
    arr.push_back(f2);
    arr.push_back(f3);

    EXPECT_EQ(arr.size(), 3u);

    // Проверяем, что вызов area() виртуальный и не падает
    for (std::size_t i = 0; i < arr.size(); ++i)
    {
        ASSERT_NE(arr[i], nullptr);
        double a = arr[i]->area();
        EXPECT_GT(a, 0.0);
    }
}

// ------------------------------
// Пример теста на Array<Figure<int>*>, как в ТЗ
// (без владения памятью, просто проверяем, что компилируется и работает)
// ------------------------------

TEST(ArrayRawPointerTest, WorksWithBasePointerType)
{
    Array<Figure<int> *> arr;

    EXPECT_EQ(arr.size(), 0u);

    Figure<int> *ptr1 = nullptr;
    Figure<int> *ptr2 = nullptr;

    arr.push_back(ptr1);
    arr.push_back(ptr2);

    EXPECT_EQ(arr.size(), 2u);
    EXPECT_EQ(arr[0], ptr1);
    EXPECT_EQ(arr[1], ptr2);

    arr.erase(0);
    EXPECT_EQ(arr.size(), 1u);
    EXPECT_EQ(arr[0], ptr2);
}

// ------------------------------
// Точка входа для тестов
// ------------------------------

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
