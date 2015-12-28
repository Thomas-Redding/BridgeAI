//
//  History.cpp
//  BridgeAI
//
//  Created by Thomas Redding on 12/27/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#include "History.hpp"

bool Trick::isEmpty() const {
    return cards[0].suit == naught;
}