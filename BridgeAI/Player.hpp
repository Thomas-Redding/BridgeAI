//
//  Player.hpp
//  BridgeAI
//
//  Created by Thomas Redding on 12/27/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#ifndef Player_hpp
#define Player_hpp

#include "History.hpp"

class Player {
	Player(History *history);
	void newGame();
	void bid();
};

#endif /* Player_hpp */
