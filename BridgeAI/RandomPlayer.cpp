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
    return Bid(null, 0);
}

Card RandomPlayer::play() {
    Card c = (*hand)[0];
    if (!hand->play(0)) {
        throw std::runtime_error("Something went wrong");
    }
    return c;
}