#include <bits/stdc++.h>
#include <string>
#include "../include/lab1.h"
using namespace std;

int lab1(std::string line) {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    vector<char> vovels{'a', 'o', 'e', 'u', 'i', 'y'};
    int count = 0;
    for (int i = 0; i<line.length(); i++){
        if (std::find(vovels.begin(), vovels.end(), line[i]) != vovels.end()) {
            count++;
        }
    }
    return count;
}

bool only_letters_input(std::string s) {
    for (int i=0; i<s.length(); i++){
        if (!std::isalpha(s[i]) && s[i] != ' '){
            return false;
        }
    }
    return true;
}