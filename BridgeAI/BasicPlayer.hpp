//
//  BasicPlayer.hpp
//  BridgeAI
//
//  Created by Morgan Redding on 12/28/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#ifndef BasicPlayer_hpp
#define BasicPlayer_hpp

#include <stdio.h>
#include "Player.hpp"
#include "heu.hpp"

class BasicPlayer : public Player {
public:
    BasicPlayer(History *history) : Player(history) {};
    Bid bid();
    Card play();
private:
	int computeHcp();
	int cachedHcp = -1;
};

#endif /* BasicPlayer_hpp */
