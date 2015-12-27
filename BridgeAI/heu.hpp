//
//  heu.hpp
//  BridgeAI
//
//  Created by Thomas Redding on 12/27/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#ifndef heu_hpp
#define heu_hpp

#include "History.hpp"
#include "Hand.hpp"

/* heuristics */
namespace heu {
	// Tend to play the highest or lowest card in a suit
	std::pair<std::vector<Card>, std::vector<double>> playExtremes(const History& history, const Hand& hand) {
		std::pair<std::vector<Card>, std::vector<double>> rtn;
		for (int i=0; i<hand.numberOfSuits; i++) {
			if(hand.cards[i].size() >= 2) {
				rtn.first.push_back(hand.cards[i][0]);
				rtn.second.push_back(1);
				rtn.first.push_back(hand.cards[i][1]);
				rtn.second.push_back(1);
			}
		}
		return rtn;
	}
}

#endif /* heu_hpp */
