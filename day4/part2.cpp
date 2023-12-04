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
            points++;
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

int get_match_count(string line) {
    vector<int> winning_nums, your_nums;
    int pos, total = 0;

    pos = line.find(":");
    line.erase(0, pos + 2);

    pos = line.find("|");
    winning_nums = get_nums(line.substr(0, pos - 1));
    your_nums = get_nums(line.substr(pos + 2, string::npos));

    total += get_points(winning_nums, your_nums);
    return total;
}

int main(int argc, char *argv[]) {
    ifstream f("input");
    vector<int> cards;
    vector<string> lines;
    string line;
    int match_count, total = 0;

    for (; getline(f, line);) {
        lines.push_back(line);
        total++;
        cards.push_back(total);
    }

    for (int i = 0; i < cards.size(); i++) {
        match_count = get_match_count(lines[cards[i] - 1]);
        cout << match_count << endl;
        total += match_count;
        for (int j = 1; j <= match_count; j++) {
            cards.push_back(cards[i] + j);
        }
    }

    cout << total << endl;
    return 0;
}
