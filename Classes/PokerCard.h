#ifndef __POKER_CARD_H__
#define __POKER_CARD_H__

#include <string>
#include "PokerBase.h"



// Different from Original
const int CardSuitDiamond = 0;
const int CardSuitClub = 1;
const int CardSuitHeart = 2;
const int CardSuitSpade = 3;




const int CardRankA = 1;
const int CardRank2 = 2;
const int CardRank3 = 3;
const int CardRank4 = 4;
const int CardRank5 = 5;
const int CardRank6 = 6;
const int CardRank7 = 7;
const int CardRank8 = 8;
const int CardRank9 = 9;
const int CardRank10 =10 ;
const int CardRankJ = 11;
const int CardRankQ = 12;
const int CardRankK = 13;
const int CardRankJokerSmall = 14;
const int CardRankJokerBig = 15;



class PokerDeck;

class PokerCard{
public:
	//////////////////////////////
	// Member Variables
	/////////////////////////////


	// ID of card
	std::string ID;

	// Rank of card
	int rank;

	// Suit of card
	int suit;

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