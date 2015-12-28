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
    const size_t handSize = 13;
    std::vector<Card> cards[numberOfSuits];
    
    bool play(size_t i);
    bool play(Card c);
    
    const Card& operator[](size_t i) const;
    size_t length() const;
    
    friend std::ostream& operator<<(std::ostream& o, const Hand& h);
};

#endif /* Hand_hpp */
