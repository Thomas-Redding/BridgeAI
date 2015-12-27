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
	std::pair<std::vector<Card>, std::vector<double>> playExtremes(const History& history, const Hand& hand) {
		std::pair<std::vector<Card>, std::vector<double>> rtn;
		if(hand.cards[0].size() > 0) {
			rtn.push_back(hands.cards[0][0]);
			rtn.push_back(hands.cards[0][0]);
		}
		return rtn;
	}
}

#endif /* heu_hpp */
