#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

vector<pair<int, pair<int, int>>> get_num_coords(string line) {
    vector<pair<int, pair<int, int>>> result;
    pair<int, pair<int, int>> new_pair;
    int temp_num, num_count = 0;
    bool in_number = false;

    for (int i = 0; i < line.size(); i++) {
        if (isdigit(line[i])) {
            temp_num = line[i] - '0';
            if (!in_number) {
                new_pair =
                    pair<int, pair<int, int>>(temp_num, pair<int, int>(i, i));
                result.push_back(new_pair);
                in_number = true;
            } else {
                result[num_count].first *= 10;
                result[num_count].first += temp_num;
                result[num_count].second.second++;
            }
        } else {
            if (in_number) {
                num_count++;
                in_number = false;
            }
        }
    }
    return result;
}

bool adjacent_symbol(pair<int, int> coord, int line, vector<string> lines,
                     int line_count) {

    int x = !coord.first ? 0 : coord.first - 1; // start
    int y = coord.second == lines[line].size() - 1 ? coord.second
                                                   : coord.second + 1; // finish
    if (lines[line][x] != '.' && !isdigit(lines[line][x]))
        return true;
    if (lines[line][y] != '.' && !isdigit(lines[line][y]))
        return true;

    // for the line above
    if (line) {
        for (int i = x; i <= y; i++) {
            if (lines[line - 1][i] != '.' && !isdigit(lines[line - 1][i]))
                return true;
        }
    }

    // for the line below
    if (line + 1 < line_count) {
        for (int i = x; i <= y; i++) {
            if (lines[line + 1][i] != '.' && !isdigit(lines[line + 1][i]))
                return true;
        }
    }

    return false;
}

int main(int argc, char *argv[]) {
    vector<string> lines(1);
    ifstream f("input");
    vector<pair<int, pair<int, int>>> coords;
    int total = 0, line_count = 0;
    bool adjacent;

    for (int i = 0; getline(f, lines[i]); i++) {
        // fill lines
        lines.push_back("");
        line_count++;
    }

    // for each line
    for (int i = 0; i < line_count; i++) {
        // get coords of all numbers in the line
        coords = get_num_coords(lines[i]);

        // for each number in the line
        cout << lines[i] << ":" << endl;
        for (vector<pair<int, pair<int, int>>>::iterator it = coords.begin();
             it != coords.end(); ++it) {

            cout << it->first << ": (" << it->second.first << ", "
                 << it->second.second << ") ";

            // if there is adjacent symbol, add number to total
            if ((adjacent = adjacent_symbol(it->second, i, lines, line_count)))
                total += it->first;

            cout << (adjacent ? "true" : "false") << endl;
        }
        cout << endl;
    }

    cout << total << endl;
    return 0;
}
