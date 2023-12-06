#include <fstream>
#include <iostream>
#include <vector>

#define MAP_COUNT 7

using namespace std;

//                                    (src, dest), range
long get_dest(long src, vector<pair<pair<long, long>, long>> srcdest_map) {
    for (vector<pair<pair<long, long>, long>>::iterator it =
             srcdest_map.begin();
         it != srcdest_map.end(); it++) {
        if (src >= it->first.first && src < it->first.first + it->second) {
            return it->first.second + (src - it->first.first);
        }
    }
    return src;
}

vector<long> input_nums(string line) {
    vector<long> nums;
    string token;
    long loc;

    while ((loc = line.find(" ")) != string::npos) {
        token = line.substr(0, loc);
        line.erase(0, loc + 1);
        nums.push_back(stol(token));
    }
    nums.push_back(stol(line));
    return nums;
}

long get_location(long seed,
                  vector<vector<pair<pair<long, long>, long>>> srcdest_maps) {
    for (auto i : srcdest_maps) {
        seed = get_dest(seed, i);
    }
    return seed;
}

int main(int argc, char *argv[]) {
    vector<vector<pair<pair<long, long>, long>>> srcdest_maps(MAP_COUNT);
    vector<long> seeds, temp;
    pair<pair<long, long>, long> temp_pair;
    string line;
    ifstream f("input");
    long result = -1, temp_result;

    getline(f, line);
    line.erase(0, 7);
    seeds = input_nums(line);

    for (long i = -1; getline(f, line);) {
        if (line.size() == 0) {
            i++;
            getline(f, line);
            continue;
        }
        temp = input_nums(line);
        temp_pair = pair<pair<long, long>, long>(
            pair<long, long>(temp[1], temp[0]), temp[2]);
        srcdest_maps[i].push_back(temp_pair);
    }

    for (auto i : seeds) {
        temp_result = get_location(i, srcdest_maps);
        if (result == -1 || temp_result < result)
            result = temp_result;
    }

    cout << result << endl;
    return 0;
}
