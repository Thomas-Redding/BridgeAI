//
//  RandomPlayer.hpp
//  BridgeAI
//
//  Created by Morgan Redding on 12/27/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#ifndef RandomPlayer_hpp
#define RandomPlayer_hpp

#include <stdio.h>
#include "Player.hpp"

class RandomPlayer : public Player {
    virtual Bid bid();
    virtual Card play();
};

#endif /* RandomPlayer_hpp */