#include <bits/stdc++.h>
#include <string>
#include "include/lab1.h"

int main() {
    std::vector<char> vovels{'a', 'o', 'e', 'u', 'i', 'y'};
    std::string line;
    std::getline(std::cin, line);
    if (only_letters_input(line)){
        std::cout << lab1(line) << '\n';
    } else {
        std::cout << "Ошибка ввода" <<  '\n';
    }
    return 0;
}