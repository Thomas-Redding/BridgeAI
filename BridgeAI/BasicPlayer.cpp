//
//  BasicPlayer.cpp
//  BridgeAI
//
//  Created by Morgan Redding on 12/28/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#include "BasicPlayer.hpp"

Bid BasicPlayer::bid() {
	const std::vector<Bid> &bids = history->bids;
	Bid lastBid = mostRecentBid();
	int hcp = computeHcp();
	int myBids = numberOfBids(id);
	int partnersBids = numberOfBids((id+2)%4);
	
	if (myBids == 0) {
		if (partnersBids == 0) {
			// my team hasn't opened
			if (hcp >= 16 && hand->cards[computeLongestSuit()].size() <= 4) {
				Bid rtn = Bid(notrump, 1);
				while (rtn < lastBid)
					rtn.level++;
				if (hcp >= 16 + 2*(rtn.level-1))
					return rtn;
				else
					return Bid(naught, 0);
			}
			else if (hcp >= 13) {
				Suit longestSuit = computeLongestSuit();
				Bid rtn = Bid(longestSuit, 1);
				while (rtn <= lastBid)
					rtn.level++;
				if (hcp >= 13 + 2*(rtn.level-1))
					return rtn;
				else
					return Bid(naught, 0);
			}
			else
				return Bid(naught, 0); // insufficient material to open
		}
		else if (partnersBids == 1) {
			// my partner has opened, but I haven't
			Suit longestSuit = computeLongestSuit();
			Bid partnersOpen = bids[indexOfLastBid((id+2)%4)];
			if (partnersOpen.suit == notrump && hcp >= 6) {
				// responding to no trump
				Bid rtn = Bid(longestSuit, 2);
				while (rtn <= lastBid)
					rtn.level++;
				if (hcp >= 6 + 2*(rtn.level-2))
					return rtn;
				else
					return Bid(naught, 0);
			}
			else {
				// responding to suit open
				double lengthDiff = hand->cards[longestSuit].size() - hand->cards[partnersOpen.suit].size();
				lengthDiff += double(longestSuit - partnersOpen.suit)/4;
				if (hcp <= 6)
					return Bid(naught, 0);
				else if (hcp <= 12) {
					// raise partner or shift
					if (lengthDiff >= 2) {
						Bid rtn = Bid(longestSuit, 2);
						while (rtn <= lastBid)
							rtn.level++;
						if (hcp >= 7 + 3*(rtn.level-2))
							return rtn;
						else
							return Bid(naught, 0);
					}
					else {
						// raise
						Bid rtn = Bid(longestSuit, 2);
						while (rtn <= lastBid)
							rtn.level++;
						if (hcp >= 13 + 3*(rtn.level-2))
							return rtn;
						else
							return Bid(naught, 0);
					}
				}
				else {
					// raise partner by 2 or jump-shift
					if (lengthDiff >= 2) {
						// jump-shift
						Bid rtn = Bid(longestSuit, 3);
						while (rtn <= lastBid)
							rtn.level++;
						if (hcp >= 13 + 3*(rtn.level-3))
							return rtn;
						else
							return Bid(naught, 0);
					}
					else {
						// raise partner by 2
						Bid rtn = Bid(longestSuit, 3);
						while (rtn <= lastBid)
							rtn.level++;
						if (hcp >= 13 + 3*(rtn.level-3))
							return rtn;
						else
							return Bid(naught, 0);
					}
				}
			}
		}
	}
	else if (myBids == 1) {
		if (partnersBids == 0) {
			// I've opened, but my partner hasn't
			return Bid(naught, 0);
		}
		else if (partnersBids == 1) {
			// Both my partner and I have bid once
			return Bid(naught, 0);
		}
	}
	
	// If I've reached here, someone on my team has bid more than once
	return Bid(naught, 0);
}

template<class F>
size_t find(const std::vector<F>& A, const F& x) {
    for (size_t i = 0; i < A.size(); i++) {
        if (A[i] == x) {
            return i;
        }
    }
    return 0xffffffffffffffff;
}

Card BasicPlayer::play() {
	
    std::vector<std::pair<Card, double>> a;
    a.resize(numberOfCardsInDeck);
    for (int i = 0; i < numberOfCardsInDeck; i++) {
        a[i].first = Card(Suit(i / numberOfCardsPerSuit), i % numberOfCardsPerSuit);
        a[i].second = 0.0;
    }

	std::vector<std::pair<Card, double>> b;
    b = heu::playExtremes(*history, *this);
    for (int i = 0; i < b.size(); i++) {
        a[b[i].first.toIndex()].second += b[i].second;
    }
    
    b = heu::trumpet(*history, *this);
    for (int i = 0; i < b.size(); i++) {
        a[b[i].first.toIndex()].second += b[i].second;
    }
	
	b = heu::mayTheFourthBeWithYou(*history, *this);
	for (int i = 0; i < b.size(); i++) {
		a[b[i].first.toIndex()].second += b[i].second;
	}
	
	b = heu::mayTheThirdBeWithYou(*history, *this);
	for (int i = 0; i < b.size(); i++) {
		a[b[i].first.toIndex()].second += b[i].second;
	}
    
    b = heu::offenseForceWins(*history, *this);
    for (int i = 0; i < b.size(); i++) {
        a[b[i].first.toIndex()].second += b[i].second;
    }
	
    // find "best" card in my hand that is ALSO legal
    
    Suit suit = history->tricks.back().cards[0].suit;
    if (suit != naught) { // if suit == naught then I am leading and I don't need to make sure I follow suit
        if(hand->cards[int(suit)].size() != 0) {
            for (int i = 0; i < a.size(); i++) {
                if (a[i].first.suit != suit) {
                    a[i].second = std::numeric_limits<double>::lowest();
                }
            }
        }
    }
    std::sort(a.begin(), a.end(), []( const std::pair<Card, double>& a, const std::pair<Card, double>& b) {
        return a.second > b.second;
    });
    for (int i = 0; i < a.size(); i++) {
        if (a[i].second == std::numeric_limits<double>::lowest()) {
            throw std::runtime_error("I really really REALLY don't want to play this card");
        }
        int s = int(a[i].first.suit);
        size_t j = find(hand->cards[s], a[i].first);
        if (j < hand->cards[s].size()) {
            Card c = hand->cards[s][j];
            hand->play(c);
            return c;
        }
    }
    
    throw std::runtime_error("Could not find a card");
    
    return Card(naught, 0);
}

int BasicPlayer::computeHcp() {
	int rtn = 0;
	for (int i=0; i<4; i++) {
		for (int j=0; j<hand->cards[i].size(); j++) {
			if (hand->cards[i][j].value == 12)
				rtn += 4;
			else if (hand->cards[i][j].value == 11)
				rtn += 3;
			else if (hand->cards[i][j].value == 11)
				rtn += 2;
			else if (hand->cards[i][j].value == 11)
				rtn++;
		}
	}
	return rtn;
}

int BasicPlayer::findTeamOpen(int team) {
	const std::vector<Bid> &bids = history->bids;
	for (int i=team; i<bids.size(); i += 2) {
		if (bids[i].suit != naught) {
			return i;
		}
	}
	return -1;
}

Suit BasicPlayer::computeLongestSuit() {
	unsigned long clubs = hand->cards[0].size();
	unsigned long diamonds = hand->cards[1].size();
	unsigned long hearts = hand->cards[2].size();
	unsigned long spades = hand->cards[3].size();
	if (clubs > diamonds && clubs > hearts && clubs > spades)
		return club;
	else if (diamonds > hearts && diamonds > spades)
		return diamond;
	else if (hearts > spades)
		return heart;
	else
		return spade;
}

int BasicPlayer::indexOfLastBid(int player) {
	const std::vector<Bid> &bids = history->bids;
	for (int i=int(bids.size()-1); i>=0; i--) {
		if (i%4 == player && bids[i].suit != naught) {
			return i;
		}
	}
	return -1;
}

int BasicPlayer::numberOfBids(int player) {
	int rtn = 0;
	const std::vector<Bid> &bids = history->bids;
	for (int i=0; i<bids.size(); i++) {
		if (i%4 == player && bids[i].suit != naught) {
			rtn++;
		}
	}
	return rtn;
}

Bid BasicPlayer::mostRecentBid() {
	const std::vector<Bid> &bids = history->bids;
	Bid lastBid = Bid(naught, 0);
	for (int i=0; i<bids.size(); i++) {
		if (bids[i].suit != naught) {
			lastBid = bids[i];
		}
	}
	return lastBid;
}
