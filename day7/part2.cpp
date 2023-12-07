#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>

#define HAND_SIZE 5

#define FiveOAK 6
#define FourOAK 5
#define FH 4
#define ThreeOAK 3
#define TP 2
#define OP 1
#define HC 0

#define AC 14
#define KC 13
#define QC 12
#define TC 10
#define JC 1

using namespace std;

// CARDS: A, K, Q, T, 9, 8, 7, 6, 5, 4, 3, 2, J (13)
int card_id(char card) {
    if (isdigit(card))
        return card - '0';

    if (card == 'A')
        return AC;
    if (card == 'K')
        return KC;
    if (card == 'Q')
        return QC;
    if (card == 'T')
        return TC;
    if (card == 'J')
        return JC;
    return -1;
}

map<char, int> count_cards(string hand) {
    map<char, int> card_count;
    for (auto i : hand) {
        card_count[i]++;
    }
    return card_count;
}

int classify_type(string hand) {
    map<char, int> card_count;
    card_count = count_cards(hand);
    vector<int> multiples_count(6, 0);
    int joker_count;

    joker_count = card_count['J'];
    card_count['J'] = 0;

    for (map<char, int>::iterator it = card_count.begin();
         it != card_count.end(); ++it) {
        multiples_count[it->second]++;
    }

    if (multiples_count[5] == 1)
        return FiveOAK;
    if (multiples_count[4] == 1) {
        if (joker_count == 1)
            return FiveOAK;
        return FourOAK;
    }
    if (multiples_count[3] == 1 && multiples_count[2] == 1)
        return FH;
    if (multiples_count[3] == 1) {
        if (joker_count == 1)
            return FourOAK;
        if (joker_count == 2)
            return FiveOAK;
        return ThreeOAK;
    }
    if (multiples_count[2] == 2) {
        if (joker_count == 1)
            return FH;
        return TP;
    }
    if (multiples_count[2] == 1) {
        if (joker_count == 1)
            return ThreeOAK;
        if (joker_count == 2)
            return FourOAK;
        if (joker_count == 3)
            return FiveOAK;
        return OP;
    }
    if (joker_count == 1)
        return OP;
    if (joker_count == 2)
        return ThreeOAK;
    if (joker_count == 3)
        return FourOAK;
    if (joker_count == 4 || joker_count == 5)
        return FiveOAK;
    return HC;
}

// returns 0 if hand1 stronger, 1 if hand2 stronger
int compare_hands(string hand1, string hand2) {
    int type1 = classify_type(hand1);
    int type2 = classify_type(hand2);

    if (type1 != type2)
        return type2 > type1;

    for (int i = 0; i < HAND_SIZE; i++) {
        if (hand1[i] != hand2[i])
            return card_id(hand2[i]) > card_id(hand1[i]);
    }
    return -1;
}

int main(int argc, char *argv[]) {
    ifstream f("input");
    string line, hand;
    int bid, total = 0;
    vector<pair<string, int>> hands;

    while (getline(f, line)) {
        hand = line.substr(0, 5);
        line.erase(0, 6);
        bid = stoi(line);
        hands.push_back(pair<string, int>(hand, bid));
    }

    sort(hands.begin(), hands.end(), [](auto &left, auto &right) {
        return compare_hands(left.first, right.first);
    });

    for (int i = 0; i < hands.size(); i++)
        total += (i + 1) * hands[i].second;

    cout << total << endl;
    return 0;
}
