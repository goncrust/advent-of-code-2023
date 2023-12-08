#include <fstream>
#include <iostream>
#include <map>

using namespace std;

int count_steps(string path, map<string, pair<string, string>> nodes) {
    string curr_node = "AAA";
    int total = 0, path_size = path.size();

    while (curr_node != "ZZZ") {
        cout << "current: " << curr_node << endl;
        cout << path[total % path_size] << endl;
        if (path[total % path_size] == 'R')
            curr_node = nodes[curr_node].second;
        else if (path[total % path_size] == 'L')
            curr_node = nodes[curr_node].first;
        cout << "new: " << curr_node << endl << endl;
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
