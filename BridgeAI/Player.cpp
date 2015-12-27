//
//  Player.cpp
//  BridgeAI
//
//  Created by Thomas Redding on 12/27/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#include "Player.hpp"

void Player::deal(const Card* dealtCards) {
    if (hand != nullptr) {
        delete hand;
    }
    hand = new Hand(dealtCards);
}