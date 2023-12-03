#include <fstream>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

static map<pair<int, int>, vector<int>> gear_values;

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

void adjacent_gears(pair<int, int> coord, int line, int value,
                    vector<string> lines, int line_count) {

    int x = !coord.first ? 0 : coord.first - 1; // start
    int y = coord.second == lines[line].size() - 1 ? coord.second
                                                   : coord.second + 1; // finish
    if (lines[line][x] == '*') {
        gear_values[pair<int, int>(line, x)].push_back(value);
        cout << "pushed back " << value << " to gear "
             << "(" << line << ", " << x << ")" << endl;
    }
    if (lines[line][y] == '*') {
        cout << "pushed back " << value << " to gear "
             << "(" << line << ", " << y << ")" << endl;
        gear_values[pair<int, int>(line, y)].push_back(value);
    }

    // for the line above
    if (line) {
        for (int i = x; i <= y; i++) {
            if (lines[line - 1][i] == '*') {
                cout << "pushed back " << value << " to gear "
                     << "(" << line - 1 << ", " << i << ")" << endl;
                gear_values[pair<int, int>(line - 1, i)].push_back(value);
            }
        }
    }

    // for the line below
    if (line + 1 < line_count) {
        for (int i = x; i <= y; i++) {
            if (lines[line + 1][i] == '*') {
                cout << "pushed back " << value << " to gear "
                     << "(" << line + 1 << ", " << i << ")" << endl;
                gear_values[pair<int, int>(line + 1, i)].push_back(value);
            }
        }
    }
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
        for (vector<pair<int, pair<int, int>>>::iterator it = coords.begin();
             it != coords.end(); ++it) {

            // update gear values
            adjacent_gears(it->second, i, it->first, lines, line_count);
        }
    }
    // for each gear
    for (map<pair<int, int>, vector<int>>::iterator it = gear_values.begin();
         it != gear_values.end(); it++) {

        if (it->second.size() == 2)
            total += it->second[0] * it->second[1];
    }

    cout << endl << total << endl;
    return 0;
}
