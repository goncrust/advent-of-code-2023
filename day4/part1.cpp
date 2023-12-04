#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int get_points(vector<int> winning_nums, vector<int> your_nums) {
    int points = 0;

    for (auto i : your_nums) {
        if (find(winning_nums.begin(), winning_nums.end(), i) !=
            winning_nums.end()) {
            if (!points)
                points = 1;
            else
                points *= 2;
        }
    }

    return points;
}

vector<int> get_nums(string str) {
    vector<int> nums;
    string token;
    int loc;

    while ((loc = str.find(" ")) != string::npos) {
        // more than one space
        if (str[0] == ' ') {
            str.erase(0, 1);
            continue;
        }

        token = str.substr(0, loc);
        str.erase(0, loc + 1);
        nums.push_back(stoi(token));
    }
    nums.push_back(stoi(str));

    return nums;
}

int main(int argc, char *argv[]) {
    ifstream f("input");
    vector<int> winning_nums, your_nums;
    string line;
    int pos, total = 0;

    for (; getline(f, line);) {
        pos = line.find(":");
        line.erase(0, pos + 2);

        pos = line.find("|");
        winning_nums = get_nums(line.substr(0, pos - 1));
        your_nums = get_nums(line.substr(pos + 2, string::npos));

        total += get_points(winning_nums, your_nums);
    }

    cout << total << endl;
    return 0;
}
