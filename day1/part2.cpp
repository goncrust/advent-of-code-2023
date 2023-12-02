#include <cctype>
#include <fstream>
#include <iostream>
#include <string>

int found_spelled(std::string str) {
    size_t pos;

    pos = str.find("one");
    if (!pos)
        return 1;

    pos = str.find("two");
    if (!pos)
        return 2;

    pos = str.find("three");
    if (!pos)
        return 3;

    pos = str.find("four");
    if (!pos)
        return 4;

    pos = str.find("five");
    if (!pos)
        return 5;

    pos = str.find("six");
    if (!pos)
        return 6;

    pos = str.find("seven");
    if (!pos)
        return 7;

    pos = str.find("eight");
    if (!pos)
        return 8;

    pos = str.find("nine");
    if (!pos)
        return 9;

    return -1;
}

int main() {
    int temp, spelled, total = 0;
    std::string line;
    std::ifstream f = std::ifstream("input");

    for (; getline(f, line);) {
        for (int i = 0; i < line.length(); i++) {
            if (std::isdigit(line[i])) {
                temp = line[i] - '0';
                temp *= 10;
                break;
            } else if ((spelled = found_spelled(
                            line.substr(i, std::string::npos))) != -1) {
                temp = spelled;
                temp *= 10;
                break;
            }
        }

        for (int i = line.length() - 1; i >= 0; i--) {
            if (std::isdigit(line[i])) {
                temp += line[i] - '0';
                break;
            } else if ((spelled = found_spelled(
                            line.substr(i, std::string::npos))) != -1) {
                temp += spelled;
                break;
            }
        }

        total += temp;
    }

    std::cout << total << std::endl;
}
