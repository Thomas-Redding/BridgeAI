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

enum Position {
	offense,
	dummy,
	left_of_dummy,
	right_of_dummy
};

class Player {
public:
    Player(History *history) : history(history), hand(nullptr) {};
    ~Player() { if (hand != nullptr) delete hand; }
    virtual void deal(int id, const Card*, const History* history);
    virtual Bid bid() = 0;
    virtual Card play() = 0;
	void setPosition(Position pos) { position = pos;}
protected:
    Hand* hand;
    const History* history;
    int id;
	Position position;
};

#endif /* Player_hpp */
