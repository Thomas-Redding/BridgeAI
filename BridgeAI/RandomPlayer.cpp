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
        return Bid(1, club);
    }
    return Bid(0, null);
}

Card RandomPlayer::play() {
    return Card(null, 0);
}