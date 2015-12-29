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

// if you're on offense try to lead to a high card in your partner's hand
std::vector<std::pair<Card, double>> heu::offenseForceWins(const History& history, const Player& player) {
	std::vector<std::pair<Card, double>> rtn;
    
    if (history.tricks.back().howManyCardsSoFar() != 0) {
        return rtn;
    }
    if (player.position == left_of_dummy || player.position == right_of_dummy) {
        return rtn;
    }
    
    // find what cards have been played so far
    bool played[numberOfSuits][numberOfCardsPerSuit];
    for (int i = 0; i < numberOfSuits; i++) {
        std::fill(played[i], played[i] + numberOfCardsPerSuit, false);
    }
    for (int i = 0; i < history.tricks.size(); i++) {
        const Card* c;
        c = &history.tricks[i].cards[0];
        played[int(c->suit)][c->value] = true;
        c = &history.tricks[i].cards[1];
        played[int(c->suit)][c->value] = true;
        c = &history.tricks[i].cards[2];
        played[int(c->suit)][c->value] = true;
        c = &history.tricks[i].cards[3];
        played[int(c->suit)][c->value] = true;
    }
    
    // find the highest card in every suit
    int highest[numberOfSuits];
    for (int i = 0; i < numberOfSuits; i++) {
        int j = numberOfCardsPerSuit - 1;
        while (j >= 0 && played[j]) {
            j--;
        }
        highest[i] = j;
    }
    
    // for every suit, check if I or my partner has the highest card
    if (player.position == offense) {
        for (int i = 0; i < numberOfSuits; i++) {
            if (player.hand->cards[i].back().value == highest[i]) {
                rtn.push_back(std::pair<Card, double>(Card(Suit(i), highest[i]), 1.0));
            }
            else if (player.dummyHand->cards[i].back().value == highest[i]) {
                rtn.push_back(std::pair<Card, double>(Card(Suit(i), highest[i]), 1.0));
            }
        }
    }
    else { // dummy
        for (int i = 0; i < numberOfSuits; i++) {
            if (player.hand->cards[i].back().value == highest[i]) {
                rtn.push_back(std::pair<Card, double>(Card(Suit(i), highest[i]), 1.0));
            }
            else if (player.offenseHand->cards[i].back().value == highest[i]) {
                rtn.push_back(std::pair<Card, double>(Card(Suit(i), highest[i]), 1.0));
            }
        }
    }
    
    return rtn;
}