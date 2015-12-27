//
//  Moderator.cpp
//  BridgeAI
//
//  Created by Thomas Redding on 12/27/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#include "Moderator.hpp"

Moderator::Moderator(Player* A, Player* B, Player* C, Player* D) : history(new History()) {
    players[0] = A;
    players[1] = B;
    players[2] = C;
    players[3] = D;
}

Moderator::~Moderator() {
	delete history;
}

int Moderator::play() {
	
	delete history;
	history = new History();
	
    // deal cards
    shuffle();
    players[0]->deal(0, &deck[0], history);
    players[1]->deal(1, &deck[13], history);
    players[2]->deal(2, &deck[26], history);
    players[3]->deal(3, &deck[39], history);
	
	// bid
	Bid currentBid = Bid
	while (true) {
		for (int i=0; i<4; i++) {
			Bid bid = players[i]->bid();
			double 0.1f * bid.suit + bid.level
		}
	}
    
    return 0;
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
