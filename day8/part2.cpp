#include <fstream>
#include <iostream>
#include <map>
#include <numeric>
#include <vector>

using namespace std;

vector<string> get_starting_nodes(map<string, pair<string, string>> nodes) {
    vector<string> starting_nodes;

    for (map<string, pair<string, string>>::iterator it = nodes.begin();
         it != nodes.end(); it++) {
        if (it->first[2] == 'A')
            starting_nodes.push_back(it->first);
    }

    return starting_nodes;
}

int count_steps(string path, map<string, pair<string, string>> nodes,
                string starting_node) {
    string curr_node = starting_node;
    int total = 0, path_size = path.size();

    while (curr_node[2] != 'Z') {
        if (path[total % path_size] == 'R')
            curr_node = nodes[curr_node].second;
        else if (path[total % path_size] == 'L')
            curr_node = nodes[curr_node].first;
        total++;
    }

    return total;
}

pair<string, pair<string, string>> read_node(string line) {
    string node, left, right;

    node = line.substr(0, 3);
    left = line.substr(7, 3);
    right = line.substr(12, 3);

    return pair<string, pair<string, string>>(
        node, pair<string, string>(left, right));
}

long calc_lcm(vector<int> values) {
    long result = 1;

    for (int i = 0; i < values.size(); i++) {
        for (int j = i + 1; j < values.size(); j++)
            values[j] = values[j] / gcd(values[i], values[j]);
        result *= values[i];
    }
    return result;
}

int main(int argc, char *argv[]) {
    ifstream f("input");
    string line, path;
    map<string, pair<string, string>> nodes;
    pair<string, pair<string, string>> temp;
    vector<string> starting_nodes;
    vector<int> results;
    long final_result;

    getline(f, path);

    getline(f, line); // empty line
    while (getline(f, line)) {
        temp = read_node(line);
        nodes[temp.first] = temp.second;
    }

    starting_nodes = get_starting_nodes(nodes);

    for (auto i : starting_nodes)
        results.push_back(count_steps(path, nodes, i));

    final_result = calc_lcm(results);
    cout << final_result << endl;

    return 0;
}
