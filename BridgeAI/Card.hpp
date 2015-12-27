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

enum Suit {
	club = 0,
	diamond = 1,
	heart = 2,
	spade = 3,
	notrump = 4
};

struct Card {
	Suit suit;
	int value;
};

#endif /* Card_hpp */
