//
//  main.cpp
//  BridgeAI
//
//  Created by Thomas Redding on 12/27/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#include <iostream>
#include "RandomPlayer.hpp"
#include "Moderator.hpp"
#include <time.h>

int main(int argc, const char * argv[]) {

	srand(int(time(NULL)));
	
    History history;
	RandomPlayer p1 = RandomPlayer(&history);
	RandomPlayer p2 = RandomPlayer(&history);
	RandomPlayer p3 = RandomPlayer(&history);
	RandomPlayer p4 = RandomPlayer(&history);
	Moderator mod = Moderator(&p1, &p2, &p3, &p4, history);
	std::pair<int, int> result = mod.play(false);
    std::cout << "Result A: " << result.first << ", " << result.second << std::endl;
	result = mod.play(true);
	std::cout << "Result B: " << result.first << ", " << result.second << std::endl;
	
    return 0;
}
