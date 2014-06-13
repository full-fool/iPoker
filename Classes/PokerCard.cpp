#include "Poker.h"
void PokerCard::flip()
{
	this->faceUp = !this->faceUp;
}

int PokerCard::compareWithOtherCard(const PokerCard*& otherCard) const
{
	// Different from orginal?
	if (this->rank == otherCard->rank){
		if (this->suit < otherCard->suit)
			return -1;
		else if (this->suit == otherCard->suit)
			return 0;
		else
			return 1;
	} else {
		if (this->rank < otherCard->rank)
			return -1;
		else
			return 1;
	}
}

std::string PokerCard::toJSONString()
{
	// TODO: Format of card representation?
	// TODO: Generate string in C++
	return "";
}

bool PokerCard::isFaceUp(){
	return faceUp;
}

bool comparePointerToCard(const PokerCard* left, const PokerCard* right)
{
	return left->compareWithOtherCard(right) <= 0;
}

