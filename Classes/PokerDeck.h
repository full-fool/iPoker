#ifndef __POKER_DECK_H__
#define __POKER_DECK_H__

#include <string>
#include <vector>

class PokerPlayer;

class PokerDeck{
public:
	//////////////////////////////
	// Member Variables
	/////////////////////////////

	// Cards in the deck
	std::vector<PokerCard*> cards;

	// ID of the deck
	std::string ID;

	// Umm.. Self explained
	bool faceUp;

	// Player the deck belongs to, if player is set to NULL, this deck
	// is public to all players
	PokerPlayer* player;

	//////////////////////////////////////
	// Member Function
	////////////////////////////////////
	void shuffle();
	void sort();
	PokerCard* getCardAtIndex(int index);
	bool insertCardatIndex(PokerCard* card, int index);
	PokerCard* remoeCardAtIndex(int index);
	void removeCard(PokerCard* card);
	std::string toJSONString();
	bool isEmpty();
	bool isFaceUp();
};

#endif