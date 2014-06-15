#include "Poker.h"


PokerPlayer::PokerPlayer()
{
}

PokerPlayer::PokerPlayer(std::string _ID, std::string _name)
{
	this->ID = _ID;
	this->name = _name;
}

void PokerPlayer::selectCards(PokerCard *card)
{
	selectedCards.insert(selectedCards.end()-1, card);
}

void PokerPlayer::moveCardToDeckAtIndex(PokerCard *card, PokerDeck *deck, int index)
{
	card->deck->removeCard(card);
	deck->insertCardatIndex(card, index);
}

std::string PokerPlayer::toJSONString()
{
	std::string a = "yes";
	return a;
}
