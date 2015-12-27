//
//  Moderator.hpp
//  BridgeAI
//
//  Created by Thomas Redding on 12/27/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#ifndef Moderator_hpp
#define Moderator_hpp

#include <cstdlib>
#include <vector>
#include "Card.hpp"

class Moderator {
	Card deck[52];
	void shuffle();
};

#endif /* Moderator_hpp */
