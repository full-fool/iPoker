#ifndef __POKER_PLAYER_H__
#define __POKER_PLAYER_H__

#include <string>
#include <vector>
#include "PokerBase.h"

class PokerDeck;

class PokerPlayer: public PokerBase{

public:

	PokerPlayer();

	PokerPlayer(std::string ID, std::string name);
	//ID of player
	std::string ID;

	//Name of player
	std::string name;

	//cards selected by the player
	std::vector<PokerCard*> selectedCards;

	//player's decks
	std::vector<PokerDeck*> decks;

	//player's base cards
	PokerDeck *pocket;

	void selectCards(PokerCard *card);

	void moveCardToDeckAtIndex(PokerCard *card, PokerDeck *deck, int index);

	std::string toJSONString();

};

#endif