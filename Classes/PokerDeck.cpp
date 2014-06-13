#include "PokerDeck.h"
#include <algorithm>

void PokerDeck::shuffle(){
	std::random_shuffle(cards.begin, cards.end);
}

void PokerDeck::sort(){
	std::sort(cards.begin, cards.end, [=](const PokerCard*& left, const PokerCard*& right){
		return left->compareWithOtherCard(right) <= 0;
	});
	return;
}

PokerCard* PokerDeck::getCardAtIndex(int index)
{
	if(index < 0)
		index = cards.size - index;
	if (index < 0 || index >= cards.size)
		return NULL;
	else
		return cards[index];
}

bool PokerDeck::insertCardatIndex(PokerCard* card, int index)
{

	card->deck = this;
	card->faceUp = this->faceUp;

	if (index < 0)
		index = cards.size - index;
	if (index < 0 || index > cards.size)
		return false;
	cards.insert(cards.begin() + index, card);
	return true;

}

PokerCard* PokerDeck::remoeCardAtIndex(int index)
{
	if(index < 0)
		index = cards.size - index;

	if (index < 0 || index >= cards.size())
		return NULL;

	PokerCard* card = getCardAtIndex(index);
	cards.erase(cards.begin() + index);
	return card;
}

void PokerDeck::removeCard(PokerCard* card)
{
	std::vector<PokerCard*>::iterator iter = std::find(cards.begin(), cards.end(), card);
	if(iter != cards.end())
		cards.erase(iter);
}

std::string toJSONString(){
	//TODO: here
	return "";
};

bool PokerDeck::isEmpty(){
	return cards.empty();
}

bool PokerDeck::isFaceUp(){
	return this->faceUp;
}