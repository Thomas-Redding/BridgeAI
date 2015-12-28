//
//  heu.hpp
//  BridgeAI
//
//  Created by Thomas Redding on 12/27/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#ifndef heu_hpp
#define heu_hpp

#define Heu_return std::pair<std::vector<Card>, std::vector<double>>

#include "History.hpp"
#include "Hand.hpp"

/* heuristics */
namespace heu {
	// Tend to play the highest or lowest card in a suit
    Heu_return playExtremes(const History& history, const Hand& hand) {
		Heu_return rtn;
		for (int i = 0; i < numberOfSuits; i++) {
			if(hand.cards[i].size() >= 2) {
				rtn.first.push_back(hand.cards[i][0]);
				rtn.second.push_back(1);
				rtn.first.push_back(hand.cards[i][1]);
				rtn.second.push_back(1);
			}
		}
		return rtn;
	}
    
    // Trump tricks if possible
    Heu_return trumpet(const History& history, const Hand& hand) {
        Heu_return rtn;
        if (history.isTrickEmpty()) {
            return rtn;
        }
        Suit suit = history.tricks.back().cards[0].suit;
        for (int i = 0; i < numberOfCardsPerSuit; i++) {
            rtn.first.push_back(Card(suit, i));
            rtn.second.push_back(1.0);
        }
        return rtn;
    }
}

#endif /* heu_hpp */
