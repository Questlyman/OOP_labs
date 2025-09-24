#include <bits/stdc++.h>
#include <string>
#include "include/lab1.h"
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    vector<char> vovels{'a', 'o', 'e', 'u', 'i', 'y'};
    string line;
    std::getline(cin, line);
    if (only_letters_input(line)){
        cout << lab1(line) << '\n';
    } else {
        cout << "Ошибка ввода" <<  '\n';
    }
    return 0;
}