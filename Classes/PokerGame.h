#ifndef __POKER_GAME_H__
#define __POKER_GAME_H__

#include <string>
#include <map>
#include <queue>
#include "PokerBase.h"
#include "json\rapidjson.h"
#include "json\document.h"
#include "json\stringbuffer.h"
#include "json\writer.h"

class PokerCard;
class PokerDeck;
class PokerPlayer;
class ClientManager;
class ServerManager;

class PokerGame{

public:
	std::string ID;
	std::map<std::string, PokerCard*> cards;
	std::map<std::string, PokerDeck*> decks;
	std::map<std::string, PokerPlayer*> players;
	PokerDeck* baseDeck;
	bool isServer;
	PokerPlayer* player;
	
	std::queue<std::string> eventQueue;

	ClientManager* clientManager;
	ServerManager* serverManager;
	int deckCount;

	void initAsServerToHost(bool isServer, std::string host);

	PokerCard* getCardWithID(std::string ID);
	PokerDeck* getDeckWithID(std::string ID);
	PokerPlayer* getPlayerWithID(std::string ID);

	void moveCardToDeckAtIndex(PokerCard* card, PokerDeck* deck, int index);
	void pass();
	void begin();
	void reset();
	void joinGameWithName(std::string name);
	void shuffle(PokerDeck* deck);
	void sort(PokerDeck* deck);

	void didServerReceiveMessage(std::string message);
	void didClientReceiveMessage(std::string message);

	PokerPlayer* allocPlayer();
	bool isValidMove(std::string message);


	void didInitWithDictionary( rapidjson::Value);
	void didAllocPID(std::string message);
	void didPlayerMoveCardToDeckAtIndex(PokerPlayer* player, PokerCard* card, PokerDeck* deck, int index);
	void didPlayerShuffleDeck(PokerPlayer* player, PokerDeck* deck);
	void didPlayerSortDeck(PokerPlayer* player, PokerDeck* deck);

	PokerCard* allocCard();
	PokerDeck* allocDeck();
	int nCard();
	int nDeck();
	int nPlayer();
	void shutConnection();

};

#endif