#include "Poker.h"
#include "cocos2d.h"
#include <stdio.h>
#include <string>
#include <sstream>
#include "json\rapidjson.h"
#include "json\document.h"
#include "json\stringbuffer.h"
#include "json\writer.h"


USING_NS_CC;

void PokerGame::initAsServerToHost(bool isServer, std::string host)
{
		if(isServer)
		{
			this->isServer = true;
			serverManager = new ServerManager;
			//serverManager->serverInitWithGame(this);
			//serverManager->serverListen();
		}
		else
		{
			this->isServer = false;
		}
		clientManager = new ClientManager;
		//clientManager->clientTnitWithGame(this);
		//bool result = clientManager->clientConectToHost(host);
		//ASSERT(result);
		reset();
}
//pass
PokerCard* PokerGame::getCardWithID(std::string ID)
{
	 return cards[ID];
}
//pass
PokerDeck* PokerGame::getDeckWithID(std::string ID)
{
	return decks[ID];
}
//pass
PokerPlayer* PokerGame::getPlayerWithID(std::string ID)
{
	return players[ID];
}
//pass
void PokerGame::moveCardToDeckAtIndex(PokerCard* card, PokerDeck* deck, int index)
{

	rapidjson::Document document;     
    rapidjson::Document::AllocatorType& allocator = document.GetAllocator();  
	rapidjson::Value dict;
	dict.SetObject();
	dict.AddMember("action", "moveCard", allocator);
	dict.AddMember("playerID", (this->player->ID).c_str(), allocator);
	dict.AddMember("cardID", (card->ID).c_str(), allocator);
	dict.AddMember("deckID", (deck->ID).c_str(), allocator);
	dict.AddMember("index", index, allocator);
	rapidjson::StringBuffer buffer;  
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);  
    dict.Accept(writer);  
	std::string msg = buffer.GetString();
	//clientManager->clientSend(msg);
	
}
//pass
void PokerGame::pass()
{


	rapidjson::Document document;     
    rapidjson::Document::AllocatorType& allocator = document.GetAllocator();  
	rapidjson::Value dict;
	dict.SetObject();
	dict.AddMember("action", "pass", allocator);
	dict.AddMember("playerID", (player->ID).c_str(), allocator);
	rapidjson::StringBuffer buffer;  
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);  
    dict.Accept(writer);  
	std::string msg = buffer.GetString();
	//clientManager->clientSend(msg);
	
}

//pass
void PokerGame::begin()

{
	rapidjson::Document document;     
    rapidjson::Document::AllocatorType& allocator = document.GetAllocator();  
	rapidjson::Value dict;
	rapidjson::Value decks(rapidjson::kArrayType);
	rapidjson::Value players(rapidjson::kArrayType);
	rapidjson::Value cards(rapidjson::kArrayType);
	dict.SetObject();
	dict.AddMember("baseDeck", (this->baseDeck->ID).c_str(), allocator);

	/*
	std::map<std::string, PokerDeck *>::iterator iter1;
	iter1 = this->decks.begin();
	int deckNum = this->decks.size();
	for(int i=0; i<deckNum; i++)
	{
		PokerDeck *tempDeck = iter1->second;
		std::string *tempMessage = new std::string(tempDeck->toJSONString());
		decks.PushBack((*tempMessage).c_str(), allocator);
		++iter1;
	}
	*/


	std::map<std::string, PokerPlayer *>::iterator iter2;
	iter2 = this->players.begin();
	int playerNum = this->players.size();
	for(int i=0; i<playerNum; i++)
	{
		PokerPlayer *tempPlayer = iter2->second;
		std::string *tempMessage = new std::string(tempPlayer->toJSONString());
		players.PushBack((*tempMessage).c_str(), allocator);
		++iter2;
	}
    /*
	std::map<std::string, PokerCard *>::iterator iter3;
	iter3 = this->cards.begin();
	int cardNum = this->cards.size();
	for(int i=0; i<cardNum; i++)
	{
		PokerCard *tempCard = iter3->second;
		std::string *tempMessage = new std::string(tempCard->toJSONString());
		cards.PushBack((*tempMessage).c_str(), allocator);
		++iter3;
	}
	*/

	dict.AddMember("players", players, allocator);
	//dict.AddMember("decks", decks, allocator);
	//dict.AddMember("cards", cards, allocator);
	dict.AddMember("action", "init", allocator);
	
	rapidjson::StringBuffer buffer;  
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);  
    dict.Accept(writer);  
	std::string msg = buffer.GetString();
	//ServerManager->serverBroadcast(msg);
}

//pass
void PokerGame::reset()
{
	cards.clear();
	players.clear();
	decks.clear();
	while(!eventQueue.empty())
		eventQueue.pop();
	joinGameWithName(player->name);
    
  
	if(isServer)
	{
		baseDeck = allocDeck();
		baseDeck->faceUp = false;
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
	
//pass
void PokerGame::joinGameWithName(std::string name)
{

	rapidjson::Document document;     
    rapidjson::Document::AllocatorType& allocator = document.GetAllocator();  
	rapidjson::Value dict;
	dict.SetObject();
	dict.AddMember("action", "join", allocator);
	dict.AddMember("name", name.c_str(), allocator);
	rapidjson::StringBuffer buffer;  
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);  
    dict.Accept(writer);  
	std::string msg = buffer.GetString();
	//clientManager->clientSend(msg);
}
//pass
void PokerGame::shuffle(PokerDeck* deck)
{
	rapidjson::Document document;     
    rapidjson::Document::AllocatorType& allocator = document.GetAllocator();  
	rapidjson::Value dict;
	dict.SetObject();
	dict.AddMember("action", "shuffle", allocator);
	dict.AddMember("deckID", (deck->ID).c_str(), allocator);
	rapidjson::StringBuffer buffer;  
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);  
    dict.Accept(writer);  
	std::string msg = buffer.GetString();
	//clientManager->clientSend(msg);
}
//pass
void PokerGame::sort(PokerDeck* deck)
{
	rapidjson::Document document;     
    rapidjson::Document::AllocatorType& allocator = document.GetAllocator();  
	rapidjson::Value dict;
	dict.SetObject();
	dict.AddMember("action", "sort", allocator);
	dict.AddMember("deckID", (deck->ID).c_str(), allocator);
	rapidjson::StringBuffer buffer;  
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);  
    dict.Accept(writer);  
	std::string msg = buffer.GetString();
	//clientManager->clientSend(msg);
}

//pass
void PokerGame::didServerReceiveMessage(std::string message)
{
	/*
	rapidjson::Document d;
	d.Parse<0>(message.c_str());
	std::string action = d["action"].GetString();
	
	if(action == "moveCard")
	{
		if(!isValidMove(message))
			return;
	}
	*/
	//serverManager->serverBroadcast(message);
}
//pass
void PokerGame::didClientReceiveMessage(std::string message)
{
	eventQueue.push(message);
}

//pass
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
//deprecated
bool PokerGame::isValidMove(std::string message)
{
	rapidjson::Document d;
	d.Parse<0>(message.c_str());
	std::string action = d["action"].GetString();
	assert(action == "moveCard");

	std::string cardID = d["cardID"].GetString();
	std::string srcDeckID = d["srcDeckID"].GetString();

	PokerCard *card = getCardWithID(cardID);
	if(card->deck->ID == srcDeckID)
	{
		return true;
	}
	else
	{
		return false;
	}
}



// TODO: msg -> <string, vector<string>>
void PokerGame::didInitWithDictionary( rapidjson::Value entities)
{
	if(!this->isServer)
	{
		rapidjson::Value& decks = entities["decks"];
		rapidjson::Value& cards = entities["cards"];
		rapidjson::Value& players = entities["players"];
		rapidjson::Value& baseDeckID = entities["baseDeckID"];

		int i, j, k;

		// Init decks
		for(i = 0; i < decks.Size(); i++)
		{

			rapidjson::Value& info = decks[i];
			PokerDeck* newDeck = new PokerDeck();
			newDeck->ID = info["ID"].GetString();
			newDeck->faceUp = info["faceUp"].GetString() == "1" ? true : false;
			this->decks.insert(std::pair<std::string, PokerDeck*>(info["ID"].GetString(), newDeck));
		}

		// Init cards
		for(i = 0; i < cards.Size(); i++)
		{
			rapidjson::Value& info = cards[i];
			std::string ID = info["ID"].GetString();
			std::string rank = info["rank"].GetString();
			std::string suit = info["suit"].GetString();
			std::string faceUp = info["faceUp"].GetString();
			std::string deckID = info["deckID"].GetString();

			PokerCard* newCard = new PokerCard();
			newCard->ID = ID;
			newCard->rank = atoi(rank.c_str());
			newCard->suit = atoi(suit.c_str());
			newCard->faceUp = info["faceUp"].GetString() == "1" ? true : false;
			newCard->deck = this->decks[deckID];
			this->cards.insert(std::pair<std::string, PokerCard*>(ID, newCard));
		}

		// Init players
		for(i = 0; i < players.Size(); i++)
		{
			rapidjson::Value& info = players[i];
			std::string ID = info["ID"].GetString();
			std::string name = info["name"].GetString();
			rapidjson::Value& selectedCardIDs = info["selectedCards"];
			rapidjson::Value& deckIDs = info["decks"];


			std::string pocketID = info["pocket"].GetString();

			std::vector<PokerCard*> selectedCardObjects;
			std::vector<PokerDeck*> deckObjects;

			for(j = 0; j < selectedCardIDs.Size(); j++)
			{
				selectedCardObjects.push_back(this->cards[selectedCardIDs[j].GetString()]);
			}

			for(j = 0; j < deckIDs.Size(); j++ )
			{
				deckObjects.push_back(this->decks[deckIDs[j].GetString()]);
			}
			PokerDeck* pocketDeck = this->decks[pocketID];

			if (ID != this->ID)
			{
				PokerPlayer *newPlayer = new PokerPlayer();
				newPlayer->ID = ID;
				newPlayer->name = name;
				newPlayer->selectedCards = selectedCardObjects;
				newPlayer->decks = deckObjects;
				newPlayer->pocket = pocketDeck;

				this->players.insert(std::pair<std::string, PokerPlayer*>(newPlayer->ID, newPlayer));
			}
			else
			{
				this->player->name = name;
				this->player->selectedCards = selectedCardObjects;
				this->player->decks = deckObjects;
				this->player->pocket = pocketDeck;
			}
		}
		
		// Update decks
		for(i = 0; i < decks.Size(); i++)
		{
			rapidjson::Value& info = decks[i];
			std::string ID = info["ID"].GetString();
			std::string playerID = info["playerID"].GetString();

			PokerDeck* deckObject = this->decks[ID];
			deckObject->player = this->players[playerID];
		}

		// Init base deck
		this->baseDeck = this->decks[baseDeckID.GetString()];
	}
}

void PokerGame::didAllocPID(std::string message)
{


	if(this->isServer)
		return;

	rapidjson::Document dict;
	dict.Parse<0>(message.c_str());

	std::string name = dict["name"].GetString();
	std::string PID= dict["PID"].GetString();




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

//pass
PokerCard* PokerGame::allocCard()
{
	std::stringstream ss;
	int id = this->cards.size();
	ss << id;
	PokerCard* card = new PokerCard();
	card->ID = std::string("card-") + ss.str();
	card->deck = NULL;
	cards.insert(std::pair<std::string, PokerCard *>(card->ID, card));
	return card;
}

//pass
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