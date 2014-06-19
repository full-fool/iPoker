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
	/*
	Json::Value root;
	Json::Value selectedCardsIDArray;
	Json::Value decksIDArray;

	std::vector<std::string> selectedCardsIDs;
	std::vector<std::string> decksIDs;
	for(std::vector<PokerCard *>::itertor iter = selectedCards.begin() ; iter != selectedCards.end() ; iter++ )
	{
		//selectedCardsIDs.push_back(iter->ID);
		selectedCardsIDArray.append(iter->ID);
	}

	for(std::vector<PokerDeck *>::itertor iter = decks.begin() ; iter != decks.end() ; iter++ )
	{
		//decksIDs.push_back(iter->ID);
		decksIDArray.append(iter->ID);
	}
	root["ID"] = this->ID;
	root["selectedCards"] = selectedCardsIDArray;
	root["decks"] = decksIDArray;
	root["pocket"] = this->pocket->ID;
	return root.toStyledString();

	*/
	return "";
}
