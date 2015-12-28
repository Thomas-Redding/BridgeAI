//
//  BasicPlayer.cpp
//  BridgeAI
//
//  Created by Morgan Redding on 12/28/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#include "BasicPlayer.hpp"

Bid BasicPlayer::bid() {
	if (history->bids.size() == 0) {
		return Bid(club, 1);
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