//
//  History.hpp
//  BridgeAI
//
//  Created by Thomas Redding on 12/27/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#ifndef History_hpp
#define History_hpp

#include <vector>
#include "Card.hpp"

struct Bid {
    Bid(Suit suit, int level) : level(level), suit(suit) {};
	int level;
	Suit suit;
};

struct Trick {
	int leader;
	Card cards[4];
    bool isEmpty() const;
};

class History {
public:
	int dealer;
	std::vector<Bid> bids;
	std::vector<Trick> tricks;
};

#endif /* History_hpp */
