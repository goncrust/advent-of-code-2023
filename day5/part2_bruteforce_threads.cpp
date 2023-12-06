#include <fstream>
#include <future>
#include <iostream>
#include <thread>
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

vector<pair<long, long>> calc_seeds(vector<long> temp) {
    vector<pair<long, long>> seeds;

    for (int i = 0; i < temp.size(); i += 2) {
        seeds.push_back(pair<long, long>(temp[i], temp[i + 1]));
    }

    return seeds;
}

long seed_range(long base_seed, long range,
                vector<vector<pair<pair<long, long>, long>>> srcdest_maps,
                int thread_num) {
    long result = -1, temp_result;
    double percentage;
    for (int j = 0; j < range; j++) {
        if (j % 1000000 == 0) {
            percentage = ((double)j / (double)range) * 100;
            cout << "thread " << thread_num << ": " << j << "/" << range << "("
                 << percentage << "%)" << endl;
        }
        temp_result = get_location(base_seed + j, srcdest_maps);
        if (result == -1 || temp_result < result)
            result = temp_result;
    }
    return result;
}

int main(int argc, char *argv[]) {
    vector<vector<pair<pair<long, long>, long>>> srcdest_maps(MAP_COUNT);
    vector<long> temp_seeds, temp;
    vector<pair<long, long>> seeds;
    pair<pair<long, long>, long> temp_pair;
    vector<future<long>> threads;
    string line;
    ifstream f("input");
    long result = -1, temp_result, total_seeds = 0, finished_seeds = 0;

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

    // debug
    for (auto i : seeds)
        total_seeds += i.second;
    cout << "total seeds:\t" << total_seeds << endl;

    for (int i = 0; i < seeds.size(); i++) {
        threads.push_back(async(seed_range, seeds[i].first, seeds[i].second,
                                srcdest_maps, i));
        cout << "created " << i << " threads" << endl;
    }

    for (int i = 0; i < threads.size(); i++) {
        temp_result = threads[i].get();
        if (result == -1 || temp_result < result)
            result = temp_result;
        cout << "thread " << i << " finished" << endl;
        cout << "current result: " << result << endl;
    }

    cout << result << endl;
    return 0;
}
