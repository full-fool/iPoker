#include "Poker.h"
#include "cocos2d.h"
#include <stdio.h>

USING_NS_CC;

void PokerGame::initAsServerToHost(bool isServer, std::string host)
{
		if(isServer)
		{
			this->isServer = TRUE;
			serverManager = new ServerManager;
			//serverManager->serverInitWithGame(this);
			//serverManager->serverListen();
		}
		else
		{
			this->isServer = FALSE;
		}
		clientManager = new ClientManager;
		//clientManager->clientTnitWithGame(this);
		//bool result = clientManager->clientConectToHost(host);
		//ASSERT(result);
		reset();
}

PokerCard* PokerGame::getCardWithID(std::string ID)
{
	 return cards[ID];
}
	
PokerDeck* PokerGame::getDeckWithID(std::string ID)
{
	return decks[ID];
}

PokerPlayer* PokerGame::getPlayerWithID(std::string ID)
{
	return players[ID];
}

void PokerGame::moveCardToDeckAtIndex(PokerCard* card, PokerDeck* deck, int index)
{
	//this map's values contain two types, int and string, so I use PokerBase
	//point to represent these two types
	std::map<std::string, PokerBase *> dict;
	dict.insert(std::pair<std::string, PokerBase *>("action", new PokerString("moveCard")));
	dict.insert(std::pair<std::string, PokerBase *>("playerID", new PokerString(this->player->ID)));
	dict.insert(std::pair<std::string, PokerBase *>("cardID", new PokerString(card->ID)));
	dict.insert(std::pair<std::string, PokerBase *>("deckID", new PokerString(deck->ID)));
	dict.insert(std::pair<std::string, PokerBase *>("index", new PokerInteger(index)));

	//std::string msg = toJSONString(dict);
	//clientmanager->clientSend(msg);
}
	
void PokerGame::pass()
{
	std::map<std::string, std::string> dict;
	dict.insert(std::pair<std::string, std::string>("action", "pass"));
	dict.insert(std::pair<std::string, std::string>("playerID", player->ID));
	//std::string msg = toJSONString(dict);
	//clientManager->clientSend(msg);
}

void PokerGame::begin()

{
	std::string msg;
	std::map<std::string, PokerBase *>dict;
	//try PokerBase for these three arrays, may be dangerous
	std::vector<PokerBase *>decks;
	std::vector<PokerBase *>cards;
	std::vector<PokerBase *>players;

	dict.insert(std::pair<std::string, PokerBase *>("baseDeck", new PokerString(baseDeck->ID)));
	
	for(std::map<std::string, PokerDeck *>::iterator iter  = this->decks.begin(); iter!= this->decks.end(); )  
    {  
		decks.push_back(iter->second);
	}  
    
	for(std::map<std::string, PokerPlayer *>::iterator iter = this->players.begin(); iter!= this->players.end();)
	{
		players.push_back(iter->second);
	}

	for(std::map<std::string, PokerCard *>::iterator iter = this->cards.begin(); iter != this->cards.end();)
	{
		cards.push_back(iter->second);
	}
	//stores the pointer which points to the vector array at dict
	dict.insert(std::pair<std::string, PokerBase *>("players", new PokerVectorPoint(&players)));
	dict.insert(std::pair<std::string, PokerBase *>("decks", new PokerVectorPoint(&decks)));
	dict.insert(std::pair<std::string, PokerBase *>("cards", new PokerVectorPoint(&cards)));
	dict.insert(std::pair<std::string, PokerBase *>("action", new PokerString("init")));
	//msg = toJSONString(dict);
	//serverManager->serverBroadcast(msg);
}
	
void PokerGame::reset()
{
	cards.clear();
	players.clear();
	decks.clear();
	while(!eventQueue.empty())
		eventQueue.pop();
	//joinGameWithName(player->name);
    
  
	if(isServer)
	{
		baseDeck = allocDeck();
		baseDeck->faceUp = FALSE;
		deckCount = 1;
		for(int i=0; i<deckCount; i++)
		{
			for(int rank = CardRankA; rank<=CardRankK; rank++)
			{
				for(int suit = CardSuitDiamond; suit<=CardSuitSpade; suit++)
				{
					PokerCard *card = allocCard();
					card->suit = suit;
					card->rank = rank;
					baseDeck->insertCardatIndex(card, -1);
				}
			}
		}
		PokerCard *joker1 = allocCard();
		joker1->suit = CardSuitSpade;
		joker1->rank = CardRankJokerSmall;
		baseDeck->insertCardatIndex(joker1, -1);
		
		PokerCard *joker2 = allocCard();
		joker2->suit = CardSuitSpade;
		joker2->rank = CardRankJokerBig;
		baseDeck->insertCardatIndex(joker2, -1);
	}

}
	

void PokerGame::joinGameWithName(std::string name)
{
	std::map<std::string, std::string>dict;
	dict.insert(std::pair<std::string, std::string>("action", "join"));
	dict.insert(std::pair<std::string, std::string>("name", name));
	//std::string msg = toJSONString(dict);
	//clientManager->clientSend(msg);
}
	
void PokerGame::shuffle(PokerDeck* deck)
{
	std::map<std::string, std::string>dict;
	dict.insert(std::pair<std::string, std::string>("action", "shuffle"));
	dict.insert(std::pair<std::string, std::string>("deckID", deck->ID));
	//std::string msg = toJSONString(dict);
	//clientManager->clientSend(msg);
}
	
void PokerGame::sort(PokerDeck* deck)
{
	std::map<std::string, std::string>dict;
	dict.insert(std::pair<std::string, std::string>("action", "sort"));
	dict.insert(std::pair<std::string, std::string>("deckID", deck->ID));
	//std::string msg = toJSONString(dict);
	//clientManager->clientSend(msg);
}

void PokerGame::didServerReceiveMessage(std::string message)
{
	std::map<std::string, std::string>dict;
	//dict = dictionaryWithString(message);
	std::string action = dict["action"];
	if(action == "moveCard")
	{
		if(!isValidMove(message))
			return;
	}
	//serverManager->serverBroadcast(message);
}
	
void PokerGame::didClientReceiveMessage(std::string message)
{
	eventQueue.push(message);
}

PokerPlayer* PokerGame::allocPlayer()
{
	PokerPlayer *player = new PokerPlayer;
	PokerDeck *deck = allocDeck();
	player->pocket = deck;
	char tempPlayer[20];
	for(int i=0; i<20; i++)
		tempPlayer[i] = 0;

	sprintf(tempPlayer, "player-%lu", nPlayer());
	player->ID = tempPlayer;
	players.insert(std::pair<std::string, PokerPlayer *>(player->ID, player));
	return player;

}

bool PokerGame::isValidMove(std::string message)
{
	std::map<std::string, std::string>dict;
	//dict = dictionaryWithString(message);
	std::string action = dict["action"];
	assert(action == "moveCard");

	std::string cardID = dict["cardID"];
	std::string srcDeckID = dict["srcDeckID"];

	PokerCard *card = getCardWithID(cardID);
	if(card->deck->ID == srcDeckID)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}



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
	return card;
}

PokerDeck* PokerGame::allocDeck()
{
	std::stringstream ss;
	int id = this->decks.size();
	ss << id;
	PokerDeck* deck = new PokerDeck();
	deck->ID = std::string("deck-") + ss.str();

	decks.insert(std::pair<std::string, PokerDeck*>(deck->ID, deck));
	return deck;
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