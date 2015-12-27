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
    for (int i = 0; i < handSize; i++) {
        std::sort(cards[i].begin(), cards[i].end(), [](Card a, Card b) { return a.value < b.value; });
    }
}