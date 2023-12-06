#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

long input_nums(string line) {
    vector<long> nums;
    long loc;
    string token, final_num = "";

    while ((loc = line.find(" ")) != string::npos) {
        token = line.substr(0, loc);
        if (line[0] == ' ') {
            line.erase(0, 1);
            continue;
        }
        line.erase(0, loc + 1);
        final_num += token;
    }
    final_num += line;
    return stol(final_num);
}

long get_sol_count(long time, long distance) {
    long t_holding, temp_distance, total = 0;
    for (t_holding = 0; t_holding <= time; t_holding++) {
        temp_distance = t_holding * (time - t_holding);
        if (temp_distance > distance)
            total++;
    }
    return total;
}

int main(int argc, char *argv[]) {
    ifstream f("input");
    string line;
    long time, distance, total = 1;

    getline(f, line);
    line.erase(0, 11);
    time = input_nums(line);

    getline(f, line);
    line.erase(0, 11);
    distance = input_nums(line);

    cout << get_sol_count(time, distance) << endl;
    return 0;
}
