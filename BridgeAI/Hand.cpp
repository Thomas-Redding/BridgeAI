//
//  Hand.cpp
//  BridgeAI
//
//  Created by Morgan Redding on 12/27/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#include "Hand.hpp"
#include <algorithm>

Hand::Hand(const Card* dealt) {
    for (int i = 0; i < handSize; i++) {
        cards[int(dealt[i].suit)].push_back(dealt[i]);
    }
    for (int i = 0; i < numberOfSuits; i++) {
        std::sort(cards[i].begin(), cards[i].end(), [](Card a, Card b) { return a.value < b.value; });
    }
}

const Card& Hand::operator[](size_t i) const {
    if (i < cards[0].size()) {
        return cards[0][i];
    }
    i -= cards[0].size();
    if (i < cards[1].size()) {
        return cards[1][i];
    }
    i -= cards[1].size();
    if (i < cards[2].size()) {
        return cards[2][i];
    }
    i -= cards[2].size();
    if (i < cards[3].size()) {
        return cards[3][i];
    }
    throw std::out_of_range("");
}

size_t Hand::length() const {
    return cards[0].size() + cards[1].size() + cards[2].size() + cards[3].size();
}

bool Hand::play(size_t i) {
    if (i < cards[0].size()) {
        cards[0].erase(cards[0].begin() + i);
        return true;
    }
    i -= cards[0].size();
    if (i < cards[1].size()) {
        cards[1].erase(cards[1].begin() + i);
        return true;
    }
    i -= cards[1].size();
    if (i < cards[2].size()) {
        cards[2].erase(cards[2].begin() + i);
        return true;
    }
    i -= cards[2].size();
    if (i < cards[3].size()) {
        cards[3].erase(cards[3].begin() + i);
        return true;
    }
    return false;
}

bool Hand::play(Card c) {
    int s = int(c.suit);
    size_t i = 0;
    while (i < cards[s].size()) {
        if (cards[s][i].value == c.value) {
            break;
        }
        i++;
    }
    if (i == cards[s].size()) {
        return false;
    }
    cards[s].erase(cards[s].begin() + i);
    return true;
}