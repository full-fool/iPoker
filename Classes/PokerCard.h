#ifndef __POKER_CARD_H__
#define __POKER_CARD_H__

#include <string>
#include "PokerBase.h"


enum PokerCardSuit: public PokerBase{
	// Different from Original
	CardSuitDiamond = 0,
    CardSuitClub,
	CardSuitHeart,
    CardSuitSpade

};


enum PokerCardRank{
    CardRankA = 1,
    CardRank2,
    CardRank3,
    CardRank4,
    CardRank5,
    CardRank6,
    CardRank7,
    CardRank8,
    CardRank9,
    CardRank10,
    CardRankJ,
    CardRankQ,
    CardRankK,
    CardRankJokerSmall,
    CardRankJokerBig
} ;


class PokerDeck;

class PokerCard{
public:
	//////////////////////////////
	// Member Variables
	/////////////////////////////


	// ID of card
	std::string ID;

	// Rank of card
	PokerCardRank rank;

	// Suit of card
	PokerCardSuit suit;

	// True for face up, false for down
	bool faceUp;

	// Deck that the card belongs to. CANNOT be null.
	PokerDeck *deck;
	

	//////////////////////////////////////
	// Member Function
	////////////////////////////////////


	bool isFaceUp();

	void flip();

	// -1 = NSOrderedAscending = this card lower
	// 0  = NSOrderedSame = same
	// 1  = NSOrderedDescending = this card higher
	int compareWithOtherCard(const PokerCard*& otherCard) const;
	std::string toJSONString();
	
};

bool comparePointerToCard(const PokerCard* left, const PokerCard* right);

#endif