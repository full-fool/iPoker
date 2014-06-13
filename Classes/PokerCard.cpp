#include "PokerCard.h"

void PokerCard::flip()
{
	this->faceUp = !this->faceUp;
}

int PokerCard::compareWithOtherCard(PokerCard& otherCard)
{
	// Different from orginal?
	if (this->rank == otherCard.rank){
		if (this->suit < otherCard.suit)
			return -1;
		else if (this->suit == otherCard.suit)
			return 0;
		else
			return 1;
	} else {
		if (this->rank < otherCard.rank)
			return -1;
		else
			return 1;
	}
}

std::string PokerCard::toJSONString(){
	// TODO: Format of card representation?
	// TODO: Generate string in C++
}