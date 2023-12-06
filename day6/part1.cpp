#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

vector<int> input_nums(string line) {
    vector<int> nums;
    int loc;
    string token;

    while ((loc = line.find(" ")) != string::npos) {
        token = line.substr(0, loc);
        if (line[0] == ' ') {
            line.erase(0, 1);
            continue;
        }
        line.erase(0, loc + 1);
        nums.push_back(stoi(token));
    }
    nums.push_back(stoi(line));

    return nums;
}

int get_sol_count(int time, int distance) {
    int t_holding, temp_distance, total = 0;
    for (t_holding = 0; t_holding <= time; t_holding++) {
        temp_distance = t_holding * (time - t_holding);
        if (temp_distance > distance)
            total++;
    }
    return total;
}

int main(int argc, char *argv[]) {
    vector<int> times;
    vector<int> distances;
    ifstream f("input");
    string line;
    int total = 1;

    getline(f, line);
    line.erase(0, 11);
    times = input_nums(line);

    getline(f, line);
    line.erase(0, 11);
    distances = input_nums(line);

    for (int i = 0; i < times.size(); i++) {
        total *= get_sol_count(times[i], distances[i]);
    }

    cout << total << endl;
    return 0;
}
