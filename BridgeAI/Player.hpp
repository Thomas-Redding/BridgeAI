//
//  Player.hpp
//  BridgeAI
//
//  Created by Thomas Redding on 12/27/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#ifndef Player_hpp
#define Player_hpp

#include "History.hpp"
#include "Hand.hpp"

class Player {
public:
    Player(History *history) : history(history), hand(nullptr) {};
    ~Player() { if (hand != nullptr) delete hand; }
    virtual void deal(const Card*);
    virtual Bid bid() = 0;
    virtual Card play() = 0;
private:
    Hand* hand;
    History* history;
};

#endif /* Player_hpp */
