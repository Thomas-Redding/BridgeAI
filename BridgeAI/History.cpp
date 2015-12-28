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

Card Trick::winning(Suit trump) const {
    Card rtn = cards[0];
    Suit suit = cards[0].suit;
    
    for (int i = 1; i < 3; i++) {
        if (cards[i].suit == naught) {
            return rtn;
        }
        if (cards[i].suit != suit && cards[i].suit != trump) {
            continue;
        }
        if (rtn.suit == trump) {
            if (cards[i].suit == trump && cards[i].value > rtn.value) {
                rtn = cards[i];
            }
        }
        else {
            if (cards[i].suit == trump || (cards[i].suit == suit && cards[i].value > rtn.value)) {
                rtn = cards[i];
            }
        }
    }
    return rtn;
}

bool History::isTrickEmpty() const {
    return tricks.back().cards[0].suit == naught;
}