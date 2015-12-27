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
    virtual void deal(int id, const Card*, const History* history);
    virtual Bid bid() = 0;
    virtual Card play() = 0;
protected:
    Hand* hand;
    const History* history;
    int id;
};

#endif /* Player_hpp */
