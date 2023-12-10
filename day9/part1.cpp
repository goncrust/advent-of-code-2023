#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> calc_diff_vectors(vector<int> original) {
    vector<vector<int>> result;
    result.push_back(original);
    int l = 0;

    while (!(result[l][0] == 0 && equal(result[l].begin() + 1, result[l].end(),
                                        result[l].begin()))) {

        result.push_back(vector<int>());
        l++;
        for (int i = 1; i < result[l - 1].size(); i++) {
            result[l].push_back(result[l - 1][i] - result[l - 1][i - 1]);
        }
    }

    return result;
}

int get_result(vector<vector<int>> diff_vectors) {
    diff_vectors[diff_vectors.size() - 1].push_back(0);

    for (int i = diff_vectors.size() - 2; i >= 0; i--) {
        diff_vectors[i].push_back(
            diff_vectors[i + 1][diff_vectors[i + 1].size() - 1] +
            diff_vectors[i][diff_vectors[i].size() - 1]);
    }

    return diff_vectors[0][diff_vectors[0].size() - 1];
}

vector<int> read_nums(string line) {
    vector<int> result;
    string token;
    int pos;

    while ((pos = line.find(" ")) != string::npos) {
        token = line.substr(0, pos);
        line.erase(0, pos + 1);
        result.push_back(stoi(token));
    }
    result.push_back(stoi(line));
    return result;
}

int main(int argc, char *argv[]) {
    ifstream f("input");
    string line;
    vector<int> line_nums;
    vector<vector<int>> diff_vectors;
    int total = 0;

    while (getline(f, line)) {
        line_nums = read_nums(line);
        diff_vectors = calc_diff_vectors(line_nums);
        total += get_result(diff_vectors);
    }
    cout << total << endl;

    return 0;
}
