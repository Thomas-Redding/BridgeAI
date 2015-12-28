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
#include <iostream>
#include "Card.hpp"
#include "Player.hpp"

class Moderator {
public:
    Moderator(Player* A, Player* B, Player* C, Player* D, History& history);
    std::pair<int, int> play(bool redoAndFlip);
    
private:
    Card deck[52];
	Card lastDeck[52];
    Player *players[4];
    History &history;
	History originalHistory;
	bool printTricks = false;
	
	void shuffle();
	int getIndexOfCard(Card &card, int player, bool redoAndFlip);
	int hasVoidInSuit(Suit suit, int player, bool redoAndFlip);
};

#endif /* Moderator_hpp */
