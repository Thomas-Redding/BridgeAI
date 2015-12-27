//
//  Hand.cpp
//  BridgeAI
//
//  Created by Morgan Redding on 12/27/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#include "Hand.hpp"
#include <algorithm>

Hand::Hand(const Card* dealtCards) {
    cards = new Card[handSize];
    for (int i = 0; i < handSize; i++) {
        cards[i] = dealtCards[i];
    }
    std::sort(cards, cards + handSize, [](Card a, Card b) { return a.suit == b.suit ? a.value < b.value : a.suit < b.suit; });
}