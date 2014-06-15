#include "Poker.h"
#include "cocos2d.h"

USING_NS_CC;


// TODO: msg -> <string, vector<string>>
void PokerGame::didInitWithDictionary( std::map<std::string, std::vector<std::string>> entities)
{
	if(!this->isServer)
	{
		std::vector<std::string> decks = entities["decks"];
		std::vector<std::string> cards = entities["cards"];
		std::vector<std::string> players = entities["players"];
		std::vector<std::string> baseDeckID = entities["baseDeckID"];

		int i, j, k;
		// Init decks
		for(i = 0; i < decks.size(); i++)
		{
			std::string deckStr = decks[i];
			// TODO: msg -> <string, string>
			std::map<std::string, std::string> info;
			// info = toMap(deckStr);
			PokerDeck* newDeck = new PokerDeck();
			newDeck->ID = info["ID"];
			newDeck->faceUp = info["faceUp"] == "1" ? true : false;
			this->decks.insert(std::pair<std::string, PokerDeck*>(info["ID"], newDeck));
		}

		// Init cards
		for(i = 0; i < cards.size(); i++)
		{
			std::string cardStr = cards[i];
			std::map<std::string, std::string> info;
			// info = toMap(deckStr);
			std::string ID = info["ID"];
			std::string rank = info["rank"];
			std::string suit = info["suit"];
			std::string faceUp = info["faceUp"];
			std::string deckID = info["deckID"];

			PokerCard* newCard = new PokerCard();
			newCard->ID = ID;
			newCard->rank = atoi(rank.c_str());
			newCard->suit = atoi(suit.c_str());
			newCard->faceUp = info["faceUp"] == "1" ? true : false;
			newCard->deck = this->decks[deckID];
			this->cards.insert(std::pair<std::string, PokerCard*>(ID, newCard));
		}

		// Init players

		// Update decks

		// Init base deck
		this->baseDeck = this->decks[baseDeckID[0]];
	}
}

void PokerGame::didAllocPID(std::string message)
{
	//TODO ! How to construct a map from string?

	if(this->isServer)
		return;
	std::map<std::string, std::string> dict;
	// dict = dictionaryWithString(message);
	std::string name = dict["name"];
	std::string PID= dict["PID"];




	PokerPlayer *player = new PokerPlayer(PID, name);

	this->players.insert( std::pair<std::string, PokerPlayer*>(PID, player));
}

void PokerGame::didPlayerMoveCardToDeckAtIndex(PokerPlayer* player, PokerCard* card, PokerDeck* deck, int index)
{
	player->moveCardToDeckAtIndex(card, deck, index);
}

void PokerGame::didPlayerShuffleDeck(PokerPlayer* player, PokerDeck* deck)
{
	deck->shuffle();
}

void PokerGame::didPlayerSortDeck(PokerPlayer* player, PokerDeck* deck)
{
	deck->sort();
}

PokerCard* PokerGame::allocCard()
{
	std::stringstream ss;
	int id = this->cards.size();
	ss << id;
	PokerCard* card = new PokerCard();
	card->ID = std::string("card-") + ss.str();

	cards.insert(std::pair<std::string, PokerCard *>(card->ID, card));
}

PokerDeck* PokerGame::allocDeck()
{
	std::stringstream ss;
	int id = this->decks.size();
	ss << id;
	PokerDeck* deck = new PokerDeck();
	deck->ID = std::string("deck-") + ss.str();

	decks.insert(std::pair<std::string, PokerDeck*>(deck->ID, deck));
}


int PokerGame::nCard()
{
	return cards.size();
}


int PokerGame::nDeck()
{
	return decks.size();
}

int PokerGame::nPlayer()
{
	return players.size();
}



void PokerGame::shutConnection()
{
	// TODO! Communication part!


	if(this->isServer){
		// this->serverManager
		log("Server connection shut");
	}
	//this->clientManager
}