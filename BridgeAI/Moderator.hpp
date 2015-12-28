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
#include <stdexcept>
#include "Card.hpp"
#include "Player.hpp"

class Moderator {
public:
    Moderator(Player* A, Player* B, Player* C, Player* D, History &hist);
    int play(); // TODO: play a game, return the points
    
private:
    Card deck[52];
    Player *players[4];
    History &history;
	
	void shuffle();
	int getIndexOfCard(Card &card, int player);
};

#endif /* Moderator_hpp */
