//
//  BasicPlayer.cpp
//  BridgeAI
//
//  Created by Morgan Redding on 12/28/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#include "BasicPlayer.hpp"

Bid BasicPlayer::bid() {
	const std::vector<Bid> &bids = history->bids;
	if (bids.size() < 4) {
		// first round of bidding
		for (int i=0; i<bids.size(); i++) {
			if (bids[i].suit != naught) {
				return Bid(naught, 0);
			}
		}
		// no one has bid
		if (computeHcp() >= 13) {
			unsigned long clubs = hand->cards[0].size();
			unsigned long diamonds = hand->cards[1].size();
			unsigned long hearts = hand->cards[2].size();
			unsigned long spades = hand->cards[3].size();
			if (clubs > diamonds && clubs > hearts && clubs > spades) {
				return Bid(club, 1);
			}
			else if (diamonds > hearts && diamonds > spades) {
				return Bid(diamond, 1);
			}
			else if (hearts > spades) {
				return Bid(heart, 1);
			}
			else {
				return Bid(spade, 1);
			}
		}
	}
    return Bid(naught, 0);
}

template<class F>
size_t find(const std::vector<F>& A, const F& x) {
    for (size_t i = 0; i < A.size(); i++) {
        if (A[i] == x) {
            return i;
        }
    }
    return 0xffffffffffffffff;
}

Card BasicPlayer::play() {
    
    Heu_return a;
    a.resize(numberOfCardsInDeck);
    for (int i = 0; i < numberOfCardsInDeck; i++) {
        a[i].first = Card(Suit(i / numberOfCardsPerSuit), i % numberOfCardsPerSuit);
        a[i].second = 0.0;
    }
    
    Heu_return b;
    
    b = heu::playExtremes(*history, *this);
    for (int i = 0; i < b.size(); i++) {
        a[b[i].first.toIndex()].second += b[i].second;
    }
    
    b = heu::trumpet(*history, *this);
    for (int i = 0; i < b.size(); i++) {
        a[b[i].first.toIndex()].second += b[i].second;
    }
    
    // find "best" card in my hand
    std::sort(a.begin(), a.end(), []( const std::pair<Card, double>& a, const std::pair<Card, double>& b) {
        return a.second > b.second;
    });
    for (int i = 0; i < a.size(); i++) {
        int s = int(a[i].first.suit);
        size_t j = find(hand->cards[s], a[i].first);
        if (j < hand->cards[s].size()) {
            Card c = hand->cards[s][j];
            hand->play(c);
            return c;
        }
    }
    
    throw std::runtime_error("Could not find a card");
    
    return Card(naught, 0);
}

int BasicPlayer::computeHcp() {
	if(cachedHcp == -1) {
		cachedHcp = 0;
		for (int i=0; i<4; i++) {
			for (int j=0; j<hand->cards[i].size(); j++) {
				if (hand->cards[i][j].value == 12) {
					cachedHcp += 4;
				}
				else if (hand->cards[i][j].value == 11) {
					cachedHcp += 3;
				}
				else if (hand->cards[i][j].value == 11) {
					cachedHcp += 2;
				}
				else if (hand->cards[i][j].value == 11) {
					cachedHcp++;
				}
			}
		}
	}
	return cachedHcp;
}
