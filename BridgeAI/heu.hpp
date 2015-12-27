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
	std::vector<Card> playExtremes(const History& history, const Hand& hand) {
		return std::vector<Card>();
	}
}

#endif /* heu_hpp */
