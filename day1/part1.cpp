#include <cctype>
#include <fstream>
#include <iostream>
#include <string>

int main() {
    int temp, total = 0;
    std::string line;
    std::ifstream f = std::ifstream("input");

    for (; getline(f, line);) {
        for (std::string::iterator i = line.begin(); i != line.end(); i++) {
            if (std::isdigit(*i)) {
                temp = *i - '0';
                temp *= 10;
                break;
            }
        }
        for (std::string::reverse_iterator i = line.rbegin(); i != line.rend();
             i++) {
            if (std::isdigit(*i)) {
                temp += *i - '0';
                break;
            }
        }
        total += temp;
    }

    std::cout << total << std::endl;
}
