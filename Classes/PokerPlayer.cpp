#include "Poker.h"
#include <iostream>
#include <string>
#include "json\rapidjson.h"
#include "json\document.h"
#include "json\stringbuffer.h"
#include "json\writer.h"

PokerPlayer::PokerPlayer()
{
}

//pass
PokerPlayer::PokerPlayer(std::string _ID, std::string _name)
{
	this->ID = _ID;
	this->name = _name;
}

//pass 
void PokerPlayer::selectCards(PokerCard *card)
{
	selectedCards.insert(selectedCards.end(), card);
}

//pass
void PokerPlayer::moveCardToDeckAtIndex(PokerCard *card, PokerDeck *deck, int index)
{
	card->deck->removeCard(card);
	deck->insertCardatIndex(card, index);
}

//pass
std::string PokerPlayer::toJSONString()
{

	rapidjson::Document document;     
    rapidjson::Document::AllocatorType& allocator = document.GetAllocator();  
	rapidjson::Value dict;
	dict.SetObject();
	rapidjson::Value selectedCardsIDs;
	rapidjson::Value decksIDs;
	selectedCardsIDs.SetArray();
	decksIDs.SetArray();
	for(std::vector<PokerCard *>::iterator iter = selectedCards.begin() ; iter != selectedCards.end() ; iter++ )
	{
		selectedCardsIDs.PushBack(((*iter)->ID).c_str(), allocator);
	}
	for(std::vector<PokerDeck *>::iterator iter = decks.begin() ; iter != decks.end() ; iter++ )
	{
		decksIDs.PushBack(((*iter)->ID).c_str(), allocator);
	}
	
	dict.AddMember("ID", (this->ID).c_str(), allocator);
	dict.AddMember("selectedCards", selectedCardsIDs, allocator);
	dict.AddMember("decks", decksIDs, allocator);
	dict.AddMember("pocket", (this->pocket->ID).c_str(), allocator);
	rapidjson::StringBuffer buffer;  
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);  
    dict.Accept(writer);  
	return buffer.GetString();

}
