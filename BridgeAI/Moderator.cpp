//
//  Moderator.cpp
//  BridgeAI
//
//  Created by Thomas Redding on 12/27/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#include "Moderator.hpp"

Moderator::Moderator(Player* A, Player* B, Player* C, Player* D, History &hist) : history(hist) {
    players[0] = A;
    players[1] = B;
    players[2] = C;
    players[3] = D;
}

std::pair<int, int> Moderator::play() {
	
    // deal cards
    shuffle();
    players[0]->deal(0, &deck[0], &history);
    players[1]->deal(1, &deck[13], &history);
    players[2]->deal(2, &deck[26], &history);
    players[3]->deal(3, &deck[39], &history);
	
	// bid
	int passCount = 0;
	Bid currentBid = Bid(naught, 0);
	Bid lastBid = currentBid;
	int lastBidPerson = 0;
	while (true) {
		if(passCount >= 4)
			break;
		for (int i = 0; i < 4; i++) {
			if(passCount >= 4)
				break;
			Bid bid = players[i]->bid();
			if (bid.level == 0 && bid.suit == naught) {
				passCount++;
				history.bids.push_back(bid);
			}
			else if ((bid.level == currentBid.level && bid.suit > currentBid.suit) || bid.level > currentBid.level) {
				passCount = 0;
				history.bids.push_back(bid);
				lastBidPerson = i;
				lastBid = bid;
			}
			else
				throw std::out_of_range("illegal bid\n");
		}
	}
	
	if(lastBid.suit == naught && lastBid.level == 0)
		return std::pair<int, int>(0, 0); // all passes
	
	// find dummy
	int dummy;
	for (int i = 0; i < history.bids.size(); i++) {
		if (i % 2 == lastBidPerson%2) {
			if(history.bids[i].suit == lastBid.suit) {
				dummy = i % 4;
				break;
			}
		}
	}
	
	int leader = (dummy - 1) % 4;
	if(leader < 0)
		leader += 4;
	int trickCount = 0;
	
	for (int i = 0; i < 13; i++) {
		// set up trick
		history.tricks.push_back(Trick());
		Trick &trick = history.tricks[history.tricks.size()-1];
		trick.leader = leader;
		
		// ask for a lead
		Card card = players[leader]->play();
		int cardIndex = getIndexOfCard(card, leader);
		if(cardIndex == -1) {
			
			throw std::out_of_range("player lead a card not in their hand\n");
		}
		trick.cards[0] = card;
		deck[cardIndex].suit = naught;
		deck[cardIndex].value = 0;
		
		// follow the lead
		for (int j = 1; j < 4; j++) {
			int k = (leader + j) % 4;
			if(k < 0)
				k += 4;
			Card card = players[k]->play();
			cardIndex = getIndexOfCard(card, k);
			if(cardIndex == -1)
				throw std::out_of_range("player played a card not in their hand\n");
			if(card.suit != trick.cards[0].suit) {
				if(!hasVoidInSuit(trick.cards[0].suit, k)) {
					throw std::out_of_range("player did not follow suit\n");
				}
			}
			trick.cards[j] = card;
			deck[cardIndex].suit = naught;
			deck[cardIndex].value = 0;
		}
		
		// determine who won - todo
		int winner = 0;
		int highest = trick.cards[0].value;
		for(int j = 1; j < 4; j++) {
			if(trick.cards[0].suit != trick.cards[0].suit && trick.cards[0].suit == lastBid.suit) {
				// trump
				if(trick.cards[0].value + 100 > highest) {
					highest = trick.cards[0].value + 100;
					winner =  j;
				}
			}
			else {
				if(trick.cards[j].suit == trick.cards[0].suit && trick.cards[j].value > highest) {
					highest = trick.cards[j].value;
					winner = j;
				}
			}
		}
		leader = (winner+leader)%4;
		if(leader%2 == 0)
			trickCount++;
		if(leader < 0)
			leader += 4;
	}
	
	// score game
	if(dummy%2 == 0) {
		// We won the bidding
		if(trickCount >= lastBid.level) {
			// made contract
			if(lastBid.suit == club || lastBid.suit == diamond)
				return std::pair<int, int>(20*lastBid.level, 20*(trickCount-lastBid.level));
			else if(lastBid.suit == heart || lastBid.suit == spade)
				return std::pair<int, int>(30*lastBid.level, 30*(trickCount-lastBid.level));
			else if(lastBid.suit == notrump)
				return std::pair<int, int>(10+30*lastBid.level, 30*(trickCount-lastBid.level));
			else
				throw std::out_of_range("error\n");
		}
		else
			return std::pair<int, int>(0, 50*(trickCount-lastBid.level)); // lost contract
	}
	else {
		// They won the bidding
		// We won the bidding
		if(trickCount >= lastBid.level) {
			// made contract
			if(lastBid.suit == club || lastBid.suit == diamond)
				return std::pair<int, int>(-20*lastBid.level, -20*(trickCount-lastBid.level));
			else if(lastBid.suit == heart || lastBid.suit == spade)
				return std::pair<int, int>(-30*lastBid.level, -30*(trickCount-lastBid.level));
			else if(lastBid.suit == notrump)
				return std::pair<int, int>(-10-30*lastBid.level, -30*(trickCount-lastBid.level));
			else
				throw std::out_of_range("error\n");
		}
		else
			return std::pair<int, int>(0, -50*(trickCount-lastBid.level)); // lost contract
	}
	return std::pair<int, int>(-1, -1);
}

int Moderator::getIndexOfCard(Card &card, int player) {
	for (int i = 0; i < 13; i++) {
		if(deck[i + 13 * player] == card)
			return i + 13 * player;
	}
	return -1;
}

void Moderator::shuffle() {
	std::vector<Card> sortedDeck;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 13; j++) {
			sortedDeck.push_back(Card(i, j));
		}
	}
	for (int i = 0; i < 52; i++) {
		int r = rand() % sortedDeck.size();
        if(r < 0)
			r += sortedDeck.size();
		deck[i] = sortedDeck[r];
		sortedDeck.erase(sortedDeck.begin()+r);
	}
}

int Moderator::hasVoidInSuit(Suit suit, int player) {
	for (int i = 0; i < 13; i++) {
		if(deck[13 * player + i].suit == suit)
			return false;
	}
	return true;
}
