#include <iostream>
#include <limits>
#include <memory>
#include "figures.cpp"
#include "figures.hpp"

int main()
{
    using CoordType = double;

    Array<std::shared_ptr<Figure<CoordType>>> figures;

    Array<Figure<int> *> baseArray;
    std::cout << "Пример Array<Figure<int>*>: size = "
              << baseArray.size() << ", capacity = "
              << baseArray.capacity() << "\n\n";

    while (true)
    {
        std::cout << "Меню:\n";
        std::cout << " 1 - Добавить фигуру\n";
        std::cout << " 2 - Напечатать все фигуры\n";
        std::cout << " 3 - Вычислить суммарную площадь\n";
        std::cout << " 4 - Удалить фигуру по индексу\n";
        std::cout << " 0 - Выход\n";
        std::cout << "Выберите пункт: ";

        int cmd = 0;
        if (!(std::cin >> cmd))
        {
            std::cerr << "Ошибка ввода, выходим.\n";
            return 1;
        }

        if (cmd == 0)
        {
            std::cout << "Выход.\n";
            break;
        }

        switch (cmd)
        {
        case 1:
        {
            std::cout << "Тип фигуры:\n";
            std::cout << " 5 - Пятиугольник\n";
            std::cout << " 6 - Шестиугольник\n";
            std::cout << " 8 - Восьмиугольник\n";
            std::cout << "Введите 5/6/8: ";
            int type = 0;
            std::cin >> type;

            std::cout << "Введите центр и радиус (cx cy r): ";
            CoordType cx, cy, r;
            std::cin >> cx >> cy >> r;
            if (!std::cin)
            {
                std::cerr << "Некорректный ввод, операция отменена.\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                break;
            }

            try
            {
                Point<CoordType> c{cx, cy};
                std::shared_ptr<Figure<CoordType>> ptr;

                if (type == 5)
                {
                    ptr = std::make_shared<Pentagon<CoordType>>(c, r);
                }
                else if (type == 6)
                {
                    ptr = std::make_shared<Hexagon<CoordType>>(c, r);
                }
                else if (type == 8)
                {
                    ptr = std::make_shared<Octagon<CoordType>>(c, r);
                }
                else
                {
                    std::cerr << "Неизвестный тип фигуры.\n";
                    break;
                }

                figures.push_back(std::move(ptr));
                std::cout << "Фигура добавлена. Текущее количество: "
                          << figures.size() << "\n\n";
            }
            catch (const std::exception &e)
            {
                std::cerr << "Ошибка при создании фигуры: " << e.what() << "\n";
            }

            break;
        }

        case 2:
        {
            if (figures.size() == 0)
            {
                std::cout << "Массив фигур пуст.\n\n";
                break;
            }

            std::cout << "Фигуры в массиве:\n";
            for (std::size_t i = 0; i < figures.size(); ++i)
            {
                std::cout << "=== Фигура #" << i << " ===\n";
                if (figures[i])
                {
                    std::cout << *figures[i] << "\n";
                }
                else
                {
                    std::cout << "Пустой элемент\n\n";
                }
            }
            break;
        }

        case 3:
        {
            double sum = total_area(figures);
            std::cout << "Суммарная площадь всех фигур: " << sum << "\n\n";
            break;
        }

        case 4:
        {
            if (figures.size() == 0)
            {
                std::cout << "Массив пуст, удалять нечего.\n\n";
                break;
            }

            std::cout << "Введите индекс для удаления (0.." << (figures.size() - 1) << "): ";
            std::size_t idx = 0;
            std::cin >> idx;
            if (!std::cin)
            {
                std::cerr << "Некорректный ввод индекса.\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                break;
            }

            try
            {
                figures.erase(idx);
                std::cout << "Фигура удалена. Новое количество: "
                          << figures.size() << "\n\n";
            }
            catch (const std::exception &e)
            {
                std::cerr << "Ошибка: " << e.what() << "\n\n";
            }

            break;
        }

        default:
            std::cout << "Неизвестная команда.\n\n";
            break;
        }
    }

    return 0;
}
