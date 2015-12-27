//
//  Hand.hpp
//  BridgeAI
//
//  Created by Morgan Redding on 12/27/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#ifndef Hand_hpp
#define Hand_hpp

#include <stdio.h>
#include "Card.hpp"

class Hand {
public:
    Hand() : cards(nullptr) {};
    Hand(const Card* cards);
    ~Hand();
private:
    const size_t handSize = 13;
    Card* cards;
};

#endif /* Hand_hpp */
