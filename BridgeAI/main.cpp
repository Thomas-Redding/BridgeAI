//
//  main.cpp
//  BridgeAI
//
//  Created by Thomas Redding on 12/27/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#include <iostream>
#include <time.h>
#include <cmath>
#include "BasicPlayer.hpp"
#include "RandomPlayer.hpp"
#include "Moderator.hpp"

double mean(std::vector<int> &vect) {
	double rtn = 0;
	for (int i=0; i<vect.size(); i++) {
		rtn += vect[i];
	}
	return rtn/vect.size();
}

double stdev(std::vector<int> &vect) {
	double avg = mean(vect);
	double rtn = 0;
	for (int i=0; i<vect.size(); i++) {
		rtn += (vect[i] - avg) * (vect[i] - avg);
	}
	return sqrt(rtn/(vect.size()-1));
}

int main(int argc, const char * argv[]) {
	srand(int(time(NULL)));
	std::vector<int> belowLine;
	std::vector<int> aboveLine;
	int n = 1000;
	for (int i=0; i<n; i++) {
		History history;
		RandomPlayer p1 = RandomPlayer(&history);
		RandomPlayer p2 = RandomPlayer(&history);
		RandomPlayer p3 = RandomPlayer(&history);
		RandomPlayer p4 = RandomPlayer(&history);
		Moderator mod = Moderator(&p1, &p2, &p3, &p4, history);
		std::pair<int, int> result1 = mod.play(false);
		std::pair<int, int> result2 = mod.play(true);
		belowLine.push_back(result1.first + result2.first);
		aboveLine.push_back(result1.second + result2.second);
	}
	std::cout << mean(belowLine) << " ± " << stdev(belowLine)/sqrt(n) << "\n";
	std::cout << mean(aboveLine) << " ± " << stdev(aboveLine)/sqrt(n) << "\n";
    return 0;
}
