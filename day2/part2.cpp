#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

#define RED_MAX 12
#define GREEN_MAX 13
#define BLUE_MAX 14

// pair<0:red;1:green;2:blue, count>
std::pair<int, int> get_color_count(std::string str) {
    std::string color;
    int count, color_num = -1;
    size_t loc;

    loc = str.find(" ");
    count = std::stoi(str.substr(0, loc));
    color = str.substr(loc + 1, std::string::npos);

    if (color == "red")
        color_num = 0;
    else if (color == "green")
        color_num = 1;
    else if (color == "blue")
        color_num = 2;

    return std::pair<int, int>(color_num, count);
}

std::vector<int> get_counts(std::string str) {
    std::string token;
    size_t loc;
    std::pair<int, int> color_count;
    std::vector<int> counts = {0, 0, 0};

    while ((loc = str.find(",")) != std::string::npos) {
        token = str.substr(0, loc);
        str.erase(0, loc + 2);

        color_count = get_color_count(token);
        counts[color_count.first] += color_count.second;
    }
    color_count = get_color_count(str);
    counts[color_count.first] += color_count.second;

    return counts;
}

int main() {
    std::string line, token;
    std::ifstream f = std::ifstream("input");
    std::vector<int> counts, max_counts = {0, 0, 0};
    size_t loc;
    int power = 1, total = 0;

    for (int i = 1; getline(f, line); i++) {
        loc = line.find(":");
        line.erase(0, loc + 2);

        max_counts = {0, 0, 0};
        power = 1;
        while ((loc = line.find(";")) != std::string::npos) {
            token = line.substr(0, loc);
            line.erase(0, loc + 2);

            counts = get_counts(token);
            for (int j = 0; j < 3; j++) {
                if (counts[j] > max_counts[j])
                    max_counts[j] = counts[j];
            }
        }
        counts = get_counts(line);
        for (int j = 0; j < 3; j++) {
            if (counts[j] > max_counts[j])
                max_counts[j] = counts[j];
            power *= max_counts[j];
        }

        total += power;
    }
    std::cout << total << std::endl;
}
