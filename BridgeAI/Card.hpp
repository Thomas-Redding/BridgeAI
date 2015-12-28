//
//  Card.hpp
//  BridgeAI
//
//  Created by Thomas Redding on 12/27/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#ifndef Card_hpp
#define Card_hpp

#include <stdio.h>

#define numberOfCardsInDeck 52
#define numberOfSuits 4
#define numberOfCardsPerSuit 13

enum Suit {
	naught = -1,
	club = 0,
	diamond = 1,
	heart = 2,
	spade = 3,
	notrump = 4
};

/* a "null" card has (suit == value == -1) */
class Card {
public:
	Card() {
		suit = naught;
		value = -1;
	}
	Card(Suit s, int v) {
		suit = s;
		value = v;
	}
	Card(int s, int v) {
		suit = Suit(s);
		value = v;
	}
	Suit suit;
	int value;
	
	bool operator==(const Card &other) const {
		return suit == other.suit && value == other.value;
	}
};

#endif /* Card_hpp */
