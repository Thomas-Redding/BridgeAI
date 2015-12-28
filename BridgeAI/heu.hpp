//
//  heu.hpp
//  BridgeAI
//
//  Created by Thomas Redding on 12/28/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#ifndef heu_hpp
#define heu_hpp

#include <stdio.h>

#define Heu_return std::vector<std::pair<Card, double>>

namespace heu {
	// Tend to play the highest or lowest card in a suit
	Heu_return playExtremes(const History& history, const Player& player) {
		Heu_return rtn;
		for (int i = 0; i < numberOfSuits; i++) {
			if(player.hand->cards[i].size() >= 2) {
				rtn.push_back(std::pair<Card, double>(player.hand->cards[i].front(), 1.0));
				rtn.push_back(std::pair<Card, double>(player.hand->cards[i].back(), 1.0));
			}
		}
		return rtn;
	}
	
	// Trump tricks if possible
	Heu_return trumpet(const History& history, const Player& player) {
		Heu_return rtn;
		if (history.isTrickEmpty()) {
			return rtn;
		}
		Suit suit = history.tricks.back().cards[0].suit;
		for (int i = 0; i < numberOfCardsPerSuit; i++) {
			rtn.push_back(std::pair<Card, double>(Card(suit, i), 1.0));
		}
		return rtn;
	}
}

#endif /* heu_hpp */
