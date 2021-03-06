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
	originalHistory = hist;
}

std::pair<int, int> Moderator::play(bool redoAndFlip) {
    // deal cards
	if(redoAndFlip) {
		for (int i=0; i<52; i++) {
			deck[i] = lastDeck[i];
		}
		players[0]->deal(3, &deck[13], &history);
		players[1]->deal(0, &deck[26], &history);
		players[2]->deal(1, &deck[39], &history);
		players[3]->deal(2, &deck[0], &history);
		history = originalHistory;
		history.dealer = 1;
	}
	else {
		shuffle();
		players[0]->deal(0, &deck[0], &history);
		players[1]->deal(1, &deck[13], &history);
		players[2]->deal(2, &deck[26], &history);
		players[3]->deal(3, &deck[39], &history);
		history.dealer = 0;
	}
	
	
	// bid
	int passCount = 0;
	Bid currentBid = Bid(naught, 0);
	int currentBidPerson = 0;
	while (true) {
		if(passCount >= 4)
			break;
		for (int i = 0; i < 4; i++) {
			if(passCount >= 4)
				break;
			int k = (i + history.dealer)%4;
			Bid bid = players[k]->bid();
			if (bid.level == 0 && bid.suit == naught) {
				passCount++;
				history.bids.push_back(bid);
			}
			else if (bid > currentBid) {
				passCount = 0;
				history.bids.push_back(bid);
				currentBidPerson = k;
				currentBid = bid;
			}
			else
				throw std::out_of_range("illegal bid\n");
		}
	}
	
	if(currentBid.suit == naught && currentBid.level == 0)
		return std::pair<int, int>(0, 0); // all passes
	
	history.trump = currentBid.suit;
	
	// find dummy
	int dummyPlayer;
	for (int i = 0; i < history.bids.size(); i++) {
		if ((i + history.dealer) % 2 == currentBidPerson%2) {
			if(history.bids[i].suit == currentBid.suit) {
				dummyPlayer = (i + history.dealer + 2) % 4;
				break;
			}
		}
	}
	
	int leader = (dummyPlayer - 1) % 4;
	if(leader < 0)
		leader += 4;
	int trickCount = 0;
	
	// give players positions
	if (dummyPlayer == 0) {
		players[0]->setPosition(dummy, nullptr, players[2]->hand);
		players[1]->setPosition(right_of_dummy, players[0]->hand, nullptr);
		players[2]->setPosition(offense, players[0]->hand, nullptr);
		players[3]->setPosition(left_of_dummy, players[0]->hand, nullptr);
	}
	else if (dummyPlayer == 1) {
		players[1]->setPosition(dummy, nullptr, players[3]->hand);
		players[2]->setPosition(right_of_dummy, players[1]->hand, nullptr);
		players[3]->setPosition(offense, players[1]->hand, nullptr);
		players[0]->setPosition(left_of_dummy, players[1]->hand, nullptr);
	}
	else if (dummyPlayer == 2) {
		players[2]->setPosition(dummy, nullptr, players[4]->hand);
		players[3]->setPosition(right_of_dummy, players[2]->hand, nullptr);
		players[0]->setPosition(offense, players[2]->hand, nullptr);
		players[1]->setPosition(left_of_dummy, players[2]->hand, nullptr);
	}
	else if (dummyPlayer == 3) {
		players[3]->setPosition(dummy, nullptr, players[1]->hand);
		players[0]->setPosition(right_of_dummy, players[3]->hand, nullptr);
		players[1]->setPosition(offense, players[3]->hand, nullptr);
		players[2]->setPosition(left_of_dummy, players[3]->hand, nullptr);
	}
	else {
		throw std::out_of_range("error");
	}
	
	for (int i = 0; i < 13; i++) {
		// set up trick
		history.tricks.push_back(Trick());
		Trick &trick = history.tricks[history.tricks.size()-1];
		trick.leader = leader;
		
		if(printTricks)
			std::cout << leader << ": ";
		
		// ask for a lead
		Card card = players[leader]->play();
		int cardIndex = getIndexOfCard(card, leader, redoAndFlip);
		if(cardIndex == -1)
			throw std::out_of_range("player lead a card not in their hand\n");
		trick.cards[0] = card;
		if(printTricks)
			std::cout << card;
		deck[cardIndex].suit = naught;
		deck[cardIndex].value = 0;
		
		// follow the lead
		for (int j = 1; j < 4; j++) {
			int k = (leader + j) % 4;
			if(k < 0)
				k += 4;
			Card card = players[k]->play();
			cardIndex = getIndexOfCard(card, k, redoAndFlip);
			if(cardIndex == -1)
				throw std::out_of_range("player played a card not in their hand\n");
			if(card.suit != trick.cards[0].suit) {
				if(!hasVoidInSuit(trick.cards[0].suit, k, redoAndFlip)) {
					throw std::out_of_range("player did not follow suit\n");
				}
			}
			if(printTricks)
				std::cout << ", " << card;
			trick.cards[j] = card;
			deck[cardIndex].suit = naught;
			deck[cardIndex].value = 0;
		}
		
		if(printTricks)
			std::cout << "\n";
		
		// determine who won - todo
		int winner = 0;
		int highest = trick.cards[0].value;
		for(int j = 1; j < 4; j++) {
			if(trick.cards[0].suit != trick.cards[0].suit && trick.cards[0].suit == currentBid.suit) {
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
	int bidLevel = currentBid.level + 6;
	if(dummyPlayer%2 == 0) {
		// We won the bidding
		if(trickCount >= bidLevel) {
			// made contract
			if(currentBid.suit == club || currentBid.suit == diamond)
				return std::pair<int, int>(20*currentBid.level, 20*(trickCount-bidLevel));
			else if(currentBid.suit == heart || currentBid.suit == spade)
				return std::pair<int, int>(30*currentBid.level, 30*(trickCount-bidLevel));
			else if(currentBid.suit == notrump)
				return std::pair<int, int>(10+30*currentBid.level, 30*(trickCount-bidLevel));
			else
				throw std::out_of_range("error\n");
		}
		else
			return std::pair<int, int>(0, 50*(trickCount-bidLevel)); // lost contract
	}
	else {
		// They won the bidding
		// We won the bidding
		trickCount = 13 - trickCount;
		if(trickCount >= bidLevel) {
			// made contract
			if(currentBid.suit == club || currentBid.suit == diamond)
				return std::pair<int, int>(-20*currentBid.level, -20*(trickCount-bidLevel));
			else if(currentBid.suit == heart || currentBid.suit == spade)
				return std::pair<int, int>(-30*currentBid.level, -30*(trickCount-bidLevel));
			else if(currentBid.suit == notrump)
				return std::pair<int, int>(-10-30*currentBid.level, -30*(trickCount-bidLevel));
			else
				throw std::out_of_range("error\n");
		}
		else
			return std::pair<int, int>(0, -50*(trickCount-bidLevel)); // lost contract
	}
	return std::pair<int, int>(-1, -1);
}

int Moderator::getIndexOfCard(Card &card, int player, bool redoAndFlip) {
	if(redoAndFlip)
		player = (player + 1)%4;
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
			sortedDeck.push_back(Card(Suit(i), j));
		}
	}
	for (int i = 0; i < 52; i++) {
		int r = rand() % sortedDeck.size();
        if(r < 0)
			r += sortedDeck.size();
		deck[i] = sortedDeck[r];
		lastDeck[i] = deck[i];
		sortedDeck.erase(sortedDeck.begin()+r);
	}
}

int Moderator::hasVoidInSuit(Suit suit, int player, bool redoAndFlip) {
	if(redoAndFlip)
		player = (player + 1)%4;
	for (int i = 0; i < 13; i++) {
		if(deck[13 * player + i].suit == suit)
			return false;
	}
	return true;
}
