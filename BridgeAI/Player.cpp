//
//  Player.cpp
//  BridgeAI
//
//  Created by Thomas Redding on 12/27/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#include "Player.hpp"

void Player::deal(int givenId, const Card* dealtCards, const History* givenHistory) {
    id = givenId;
    if (hand != nullptr) {
        delete hand;
    }
    hand = new Hand(dealtCards);
    history = givenHistory;
}