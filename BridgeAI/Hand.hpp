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
#include <vector>
#include <array>
#include "Card.hpp"

class Hand {
public:
    Hand() {};
    Hand(const Card* cards);
private:
    static const size_t handSize = 13;
    static const size_t numberOfSuits = 4;
    std::vector<Card> cards[numberOfSuits];
};

#endif /* Hand_hpp */
