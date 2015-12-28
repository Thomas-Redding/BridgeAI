//
//  History.cpp
//  BridgeAI
//
//  Created by Thomas Redding on 12/27/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#include "History.hpp"

int Trick::howManyCardsSoFar() const {
    int count = 0;
    for (int i = 0; i < 4; i++) {
        count += cards[i].suit != naught ? 1 : 0;
    }
    return count;
}

bool History::isTrickEmpty() const {
    return tricks.back().cards[0].suit == naught;
}