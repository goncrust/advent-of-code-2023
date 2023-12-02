#include <fstream>
#include <iostream>

#define RED_MAX 12
#define GREEN_MAX 13
#define BLUE_MAX 14

bool check_color(std::string str) {
    std::string color;
    int count;
    size_t loc;

    loc = str.find(" ");
    count = std::stoi(str.substr(0, loc));
    color = str.substr(loc + 1, std::string::npos);

    if (color == "red" && count > RED_MAX)
        return false;
    else if (color == "green" && count > GREEN_MAX)
        return false;
    else if (color == "blue" && count > BLUE_MAX)
        return false;

    return true;
}

bool check_counts(std::string str) {
    std::string token;
    size_t loc;

    while ((loc = str.find(",")) != std::string::npos) {
        token = str.substr(0, loc);
        str.erase(0, loc + 2);
        if (!check_color(token))
            return false;
        ;
    }

    return check_color(str);
}

int main() {
    std::string line, token;
    std::ifstream f = std::ifstream("input");
    size_t loc;
    bool valid;
    int total = 0;

    for (int i = 1; getline(f, line); i++) {
        loc = line.find(":");
        line.erase(0, loc + 2);

        valid = true;
        while ((loc = line.find(";")) != std::string::npos) {
            token = line.substr(0, loc);
            line.erase(0, loc + 2);
            valid = check_counts(token);
            if (!valid)
                break;
        }

        if (valid && check_counts(line))
            total += i;
    }

    std::cout << total << std::endl;
}
