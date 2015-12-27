//
//  Moderator.hpp
//  BridgeAI
//
//  Created by Thomas Redding on 12/27/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#ifndef Moderator_hpp
#define Moderator_hpp

#include <vector>
#include "Card.hpp"

class Moderator {
	std::vector<std::vector<Card>> hands;
	void shuffle();
};

#endif /* Moderator_hpp */
