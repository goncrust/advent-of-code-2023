#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

#define MAP_COUNT 7

using namespace std;

//                                                                          range_dest
// range1: (77, 100)
// range2: (74, 88)
pair<long, long> get_interception(pair<long, long> range1,
                                  pair<long, long> range2) {
    long range1_x1 = range1.first;
    long range1_x2 = range1.first + range1.second;
    long range2_x1 = range2.first;
    long range2_x2 = range2.first + range2.second;
    pair<long, long> result;

    cout << "************** interception ************" << endl;
    cout << "range1: "
         << "(" << range1.first << ", " << range1.second + range1.first << ")"
         << endl;
    cout << "range2: "
         << "(" << range2.first << ", " << range2.second + range2.first << ")"
         << endl;
    if ((range2_x1 < range1_x1 && range2_x2 < range1_x1) ||
        (range2_x1 > range1_x2 && range2_x2 > range1_x2)) {
        cout << "********** no *****************" << endl;
        return pair<long, long>(-1, -1);
    }

    if (range1_x1 < range2_x1)
        result.first = range2_x1;
    else
        result.first = range1_x1;

    if (range1_x2 > range2_x2)
        result.second = range2_x2 - result.first;
    else
        result.second = range1_x2 - result.first;

    cout << "interception: "
         << "(" << result.first << ", " << result.second + result.first << ")"
         << endl;
    cout << "*****************************" << endl;

    return result;
}

vector<pair<long, long>>
get_not_intercepted(pair<long, long> range,
                    vector<pair<long, long>> intercepted) {

    vector<pair<long, long>> result;
    long last_finish, curr_begin;

    sort(intercepted.begin(), intercepted.end(),
         [](auto &left, auto &right) { return left.first < right.first; });

    for (int i = 0; i < intercepted.size() + 1; i++) {
        last_finish =
            i == 0 ? range.first
                   : intercepted[i - 1].first + intercepted[i - 1].second;
        curr_begin = i < intercepted.size() ? intercepted[i].first
                                            : range.first + range.second;
        if (last_finish == curr_begin)
            continue;
        result.push_back(
            pair<long, long>(last_finish, curr_begin - last_finish));
    }

    return result;
}

//                       (src, dest), range
vector<pair<long, long>>
get_dests(pair<long, long> src_range,
          vector<pair<pair<long, long>, long>> srcdest_map) {

    // debug
    cout << "(" << src_range.first << ", " << src_range.first + src_range.second
         << "):" << endl;
    for (auto i : srcdest_map) {
        cout << "(" << i.first.first << ", " << i.first.first + i.second << ")"
             << " : ";
        cout << "(" << i.first.second << ", " << i.first.second + i.second
             << ");" << endl;
    }

    // code
    vector<pair<long, long>> ranges, intercepted, not_intercepted;
    pair<long, long> temp_range;

    for (vector<pair<pair<long, long>, long>>::iterator it =
             srcdest_map.begin();
         it != srcdest_map.end(); it++) {

        temp_range = get_interception(
            pair<long, long>(it->first.first, it->second), src_range);
        if (temp_range.first != -1) {
            intercepted.push_back(temp_range);
            temp_range.first += it->first.second - it->first.first;
            ranges.push_back(temp_range);
        }
    }

    cout << "-------------------- NOT INTERCEPTED --------------------" << endl;
    for (auto i : intercepted)
        cout << "(" << i.first << ", " << i.first + i.second << ")" << endl;
    not_intercepted = get_not_intercepted(src_range, intercepted);
    cout << endl;
    for (auto i : not_intercepted)
        cout << "(" << i.first << ", " << i.first + i.second << ")" << endl;
    cout << "---------------------------------------------------------" << endl;
    ranges.insert(ranges.end(), not_intercepted.begin(), not_intercepted.end());
    for (auto i : ranges)
        cout << "(" << i.first << ", " << i.first + i.second << ")" << endl;
    cout << endl;
    return ranges;
}

vector<pair<long, long>>
get_dests_for_srcs(vector<pair<long, long>> srcs,
                   vector<pair<pair<long, long>, long>> srcdest_map) {
    vector<pair<long, long>> dests, result;
    for (auto i : srcs) {
        dests = get_dests(i, srcdest_map);
        result.insert(result.end(), dests.begin(), dests.end());
    }
    return result;
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

vector<pair<long, long>>
get_locations(vector<pair<long, long>> srcs,
              vector<vector<pair<pair<long, long>, long>>> srcdest_maps) {
    for (auto i : srcdest_maps) {
        srcs = get_dests_for_srcs(srcs, i);
    }
    return srcs;
}

vector<pair<long, long>> calc_seeds(vector<long> temp) {
    vector<pair<long, long>> seeds;

    for (int i = 0; i < temp.size(); i += 2) {
        seeds.push_back(pair<long, long>(temp[i], temp[i + 1]));
    }

    return seeds;
}

int main(int argc, char *argv[]) {
    vector<vector<pair<pair<long, long>, long>>> srcdest_maps(MAP_COUNT);
    vector<pair<long, long>> seeds, locations;
    vector<long> temp, temp_seeds;
    pair<pair<long, long>, long> temp_pair;
    string line;
    ifstream f("input");
    long result = -1, temp_result;

    getline(f, line);
    line.erase(0, 7);
    temp_seeds = input_nums(line);
    seeds = calc_seeds(temp_seeds);

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

    locations = get_locations(seeds, srcdest_maps);
    for (auto i : locations) {
        if (result == -1 || i.first < result)
            result = i.first;
    }

    cout << result << endl;
    return 0;
}
