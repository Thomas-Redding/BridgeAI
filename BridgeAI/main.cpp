//
//  main.cpp
//  BridgeAI
//
//  Created by Thomas Redding on 12/27/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#include <iostream>
#include "heu.hpp"
#include "RandomPlayer.hpp"
#include "Moderator.hpp"

int main(int argc, const char * argv[]) {
	// insert code here...
	History history;
	RandomPlayer p1 = RandomPlayer(&history);
	RandomPlayer p2 = RandomPlayer(&history);
	RandomPlayer p3 = RandomPlayer(&history);
	RandomPlayer p4 = RandomPlayer(&history);
	Moderator mod = Moderator(&p1, &p2, &p3, &p4, history);
    int result = mod.play();
    
    std::cout << "Result: " << result << std::endl;
	
    return 0;
}
