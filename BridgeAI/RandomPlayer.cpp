//
//  RandomPlayer.cpp
//  BridgeAI
//
//  Created by Morgan Redding on 12/27/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#include "RandomPlayer.hpp"

Bid RandomPlayer::bid() {
    if (history->bids.size() == 0) {
        return Bid(club, 1);
    }
    return Bid(naught, 0);
}

Card RandomPlayer::play() {
    
    if (history->isTrickEmpty()) {
        // play first card
        Card c = (*hand)[0];
        if (!hand->play(0)) {
            throw std::runtime_error("Something went wrong");
        }
        return c;
    }
    
    // try to follow suit
    Suit suit = history->tricks.back().cards[0].suit;
    if (hand->cards[int(suit)].size() == 0) {
        // play first card
        Card c = (*hand)[0];
        if (!hand->play(0)) {
            throw std::runtime_error("Something went wrong");
        }
        return c;
    }
    
    Card c = hand->cards[int(suit)][0];
    if (!hand->play(c)) {
        throw std::runtime_error("Something went wrong");
    }
    return c;
}