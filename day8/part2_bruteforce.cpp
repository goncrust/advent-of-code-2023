#include <fstream>
#include <iostream>
#include <map>
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

bool all_finished(vector<string> curr_nodes) {
    for (auto i : curr_nodes) {
        if (i[2] != 'Z')
            return false;
    }
    return true;
}

int count_steps(string path, map<string, pair<string, string>> nodes) {
    vector<string> curr_nodes;
    int total = 0, path_size = path.size();

    curr_nodes = get_starting_nodes(nodes);
    while (!all_finished(curr_nodes)) {
        for (int i = 0; i < curr_nodes.size(); i++) {
            if (path[total % path_size] == 'R')
                curr_nodes[i] = nodes[curr_nodes[i]].second;
            else if (path[total % path_size] == 'L')
                curr_nodes[i] = nodes[curr_nodes[i]].first;
            cout << curr_nodes[i] << "; ";
        }
        cout << endl << endl;
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
