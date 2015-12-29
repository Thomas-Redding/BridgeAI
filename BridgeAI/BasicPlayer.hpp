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
#include <limits>

#include "Player.hpp"
#include "heu.hpp"

class BasicPlayer : public Player {
public:
    BasicPlayer(History *history) : Player(history) {};
    Bid bid();
    Card play();
private:
	int computeHcp();
	Suit computeLongestSuit();
	int findTeamOpen(int team);
	int indexOfLastBid(int player);
	int numberOfBids(int player);
	Bid mostRecentBid();
};

#endif /* BasicPlayer_hpp */
