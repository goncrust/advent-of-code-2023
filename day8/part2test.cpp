#include <fstream>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

vector<pair<string, vector<int>>>
get_starting_nodes(map<string, pair<string, string>> nodes) {
    vector<pair<string, vector<int>>> starting_nodes;

    for (map<string, pair<string, string>>::iterator it = nodes.begin();
         it != nodes.end(); it++) {
        if (it->first[2] == 'A')
            starting_nodes.push_back(
                pair<string, vector<int>>(it->first, vector<int>()));
    }

    return starting_nodes;
}

bool all_finished(vector<pair<string, vector<int>>> curr_nodes) {
    for (auto i : curr_nodes) {
        if (i.second.size() < 2)
            return false;
    }
    return true;
}

int count_steps(string path, map<string, pair<string, string>> nodes) {
    vector<pair<string, vector<int>>> curr_nodes;
    int total = 0, path_size = path.size();

    curr_nodes = get_starting_nodes(nodes);
    while (!all_finished(curr_nodes)) {
        for (int i = 0; i < curr_nodes.size(); i++) {
            if (curr_nodes[i].first[2] == 'Z') {
                cout << curr_nodes[i].first << ": " << total << endl;
                curr_nodes[i].second.push_back(total);
            }

            if (path[total % path_size] == 'R')
                curr_nodes[i].first = nodes[curr_nodes[i].first].second;
            else if (path[total % path_size] == 'L')
                curr_nodes[i].first = nodes[curr_nodes[i].first].first;
        }
        total++;
    }

    for (auto i : curr_nodes) {
        for (auto j : i.second) {
            cout << j << "; ";
        }
        cout << endl;
    }

    return calc_lcm();
}

pair<string, pair<string, string>> read_node(string line) {
    string node, left, right;

    node = line.substr(0, 3);
    left = line.substr(7, 3);
    right = line.substr(12, 3);

    return pair<string, pair<string, string>>(
        node, pair<string, string>(left, right));
}

int main(int argc, char *argv[]) {
    ifstream f("input");
    string line, path;
    map<string, pair<string, string>> nodes;
    pair<string, pair<string, string>> temp;
    int result;

    getline(f, path);

    getline(f, line); // empty line
    while (getline(f, line)) {
        temp = read_node(line);
        nodes[temp.first] = temp.second;
    }

    result = count_steps(path, nodes);
    cout << result << endl;

    return 0;
}
