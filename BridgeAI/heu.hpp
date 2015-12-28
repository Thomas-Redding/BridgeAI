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
#include <vector>
#include "Card.hpp"
#include "History.hpp"
#include "Player.hpp"

namespace heu {
	std::vector<std::pair<Card, double>> playExtremes(const History& history, const Player& player);
	std::vector<std::pair<Card, double>> trumpet(const History& history, const Player& player);
	bool better(const Card& old, const Card& c, Suit trump);
	std::vector<std::pair<Card, double>> mayTheFourthBeWithYou(const History& history, const Player& player);
	std::vector<std::pair<Card, double>> mayTheThirdBeWithYou(const History& history, const Player& player);
}

#endif /* heu_hpp */
