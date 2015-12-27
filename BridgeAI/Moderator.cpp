//
//  Moderator.cpp
//  BridgeAI
//
//  Created by Thomas Redding on 12/27/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#include "Moderator.hpp"

Moderator::Moderator(Player* A, Player* B, Player* C, Player* D) {
    players[0] = A;
    players[1] = B;
    players[2] = C;
    players[3] = D;
}

void Moderator::shuffle() {
	std::vector<Card> sortedDeck;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 13; j++) {
			sortedDeck.push_back(Card(i, j));
		}
	}
	for (int i = 0; i < 52; i++) {
		int r = rand()%sortedDeck.size();
        if(r < 0) {
			r += sortedDeck.size();
        }
		deck[i] = sortedDeck[r];
		sortedDeck.erase(sortedDeck.begin()+r);
	}
}
