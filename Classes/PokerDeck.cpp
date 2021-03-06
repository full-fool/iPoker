#include "Poker.h"
#include <algorithm>
#include "json\rapidjson.h"
#include "json\document.h"
#include "json\stringbuffer.h"
#include "json\writer.h"


// Pass
void PokerDeck::shuffle(){
	std::random_shuffle(cards.begin(), cards.end());
}

void PokerDeck::sort(){
	std::sort(cards.begin(), cards.end(), comparePointerToCard);
	return;
}

// Pass
PokerCard* PokerDeck::getCardAtIndex(int index)
{
	int size = cards.size();
	if(index < 0)
		index = size - index;
	if (index < 0 || index >= size)
		return NULL;
	else
		return cards[index];
}

// Pass
bool PokerDeck::insertCardatIndex(PokerCard* card, int index)
{
	int size =cards.size();
	card->deck = this;
	card->faceUp = this->faceUp;

	if (index < 0)
		index = size - index;
	if (index < 0 || index > size)
		return false;
	cards.insert(cards.begin() + index, card);
	return true;

}

// Pass
PokerCard* PokerDeck::remoeCardAtIndex(int index)
{
	int size = cards.size();
	if(index < 0)
		index = size - index;

	if (index < 0 || index >= size)
		return NULL;

	PokerCard* card = getCardAtIndex(index);
	cards.erase(cards.begin() + index);
	return card;
}

// Pass
void PokerDeck::removeCard(PokerCard* card)
{
	std::vector<PokerCard*>::iterator iter = std::find(cards.begin(), cards.end(), card);
	if(iter != cards.end())
		cards.erase(iter);
	card->deck = NULL;
}


// Pass
std::string PokerDeck::toJSONString(){
	rapidjson::Document document;
	rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
	rapidjson::Value dict;
	dict.SetObject();
	dict.AddMember("ID", this->ID.c_str(), allocator);
	dict.AddMember("faceUp", this->faceUp, allocator);
	dict.AddMember("playerID", this->player->ID.c_str(), allocator);

	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	dict.Accept(writer);
	return buffer.GetString();
}

// Pass
bool PokerDeck::isEmpty(){
	return cards.empty();
}

// Pass
bool PokerDeck::isFaceUp(){
	return this->faceUp;
}
