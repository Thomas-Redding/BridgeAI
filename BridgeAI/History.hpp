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
	
	bool operator<(const Bid& other) const {
		if (level < other.level) {
			return true;
		}
		else if (level > other.level) {
			return false;
		}
		else
			return suit < other.suit;
	}
	
	bool operator>(const Bid& other) const {
		if (level > other.level) {
			return true;
		}
		else if (level < other.level) {
			return false;
		}
		else
			return suit > other.suit;
	}
	
	bool operator==(const Bid& other) const {
		return level == other.level && suit == other.suit;
	}
	
	bool operator<=(const Bid& other) const {
		if (level < other.level)
			return true;
		else if (level > other.level)
			return false;
		else
			return suit <= other.suit;
	}
	
	bool operator>=(const Bid& other) const {
		if (level > other.level)
			return true;
		else if (level < other.level)
			return false;
		else
			return suit >= other.suit;
	}
};

struct Trick {
	int leader;
	Card cards[numberOfSuits];
    int howManyCardsSoFar() const;
    Card winning(Suit trump) const;
};

class History {
public:
	Suit trump = naught;
	int dealer;
	std::vector<Bid> bids;
	std::vector<Trick> tricks;
    bool isTrickEmpty() const;
};

#endif /* History_hpp */
