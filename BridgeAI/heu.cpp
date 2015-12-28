//
//  heu.cpp
//  BridgeAI
//
//  Created by Thomas Redding on 12/28/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#include "heu.hpp"

std::vector<std::pair<Card, double>> heu::playExtremes(const History& history, const Player& player) {
	std::vector<std::pair<Card, double>> rtn;
	for (int i = 0; i < numberOfSuits; i++) {
		if(player.hand->cards[i].size() >= 2) {
			rtn.push_back(std::pair<Card, double>(player.hand->cards[i].front(), 1.0));
			rtn.push_back(std::pair<Card, double>(player.hand->cards[i].back(), 1.0));
		}
	}
	return rtn;
}

std::vector<std::pair<Card, double>> heu::trumpet(const History& history, const Player& player) {
	std::vector<std::pair<Card, double>> rtn;
	if (history.isTrickEmpty()) {
		return rtn;
	}
	Suit suit = history.tricks.back().cards[0].suit;
	for (int i = 0; i < numberOfCardsPerSuit; i++) {
		rtn.push_back(std::pair<Card, double>(Card(suit, i), 1.0));
	}
	return rtn;
}

bool heu::better(const Card& old, const Card& c, Suit trump) {
	if (old.suit == trump) {
		return c.suit == trump && c.value > old.value;
	}
	return c.suit == trump || (c.suit == old.suit && c.value > old.value);
}

// fourth hand high
std::vector<std::pair<Card, double>> heu::mayTheFourthBeWithYou(const History& history, const Player& player) {
	std::vector<std::pair<Card, double>> rtn;
	if (history.tricks.back().howManyCardsSoFar() != 3) {
		return rtn;
	}
	
	Card currentlyWinning = history.tricks.back().winning(history.trump);
	
	for (int i = 0; i < numberOfCardsInDeck; i++) {
		Card c(Suit(i / numberOfCardsPerSuit), i % numberOfCardsPerSuit);
		if (better(currentlyWinning, c, history.trump)) {
			rtn.push_back(std::pair<Card, double>(c, 1.0));
		}
	}
	return rtn;
}

std::vector<std::pair<Card, double>> heu::mayTheThirdBeWithYou(const History& history, const Player& player) {
	std::vector<std::pair<Card, double>> rtn;
	if (history.tricks.back().howManyCardsSoFar() != 2) {
		return rtn;
	}
	
	Card currentlyWinning = history.tricks.back().winning(history.trump);
	
	for (int i = 0; i < numberOfCardsInDeck; i++) {
		Card c(Suit(i / numberOfCardsPerSuit), i % numberOfCardsPerSuit);
		if (better(currentlyWinning, c, history.trump)) {
			rtn.push_back(std::pair<Card, double>(c, 1.0));
		}
	}
	return rtn;
}