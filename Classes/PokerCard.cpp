#include "Poker.h"
#include "json\rapidjson.h"
#include "json\document.h"
#include "json\stringbuffer.h"
#include "json\writer.h"

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

	rapidjson::Document document;
	rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
	rapidjson::Value dict;
	dict.SetObject();

	// Note: should add int or string?
	dict.AddMember("ID", this->ID.c_str(), allocator);
	dict.AddMember("rank", this->rank, allocator);
	dict.AddMember("suit", this->suit, allocator);
	dict.AddMember("faceup", this->faceUp, allocator);
	dict.AddMember("deckID", this->deck->ID.c_str(), allocator);
	
	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	dict.Accept(writer);
	return buffer.GetString();

}

bool PokerCard::isFaceUp(){
	return faceUp;
}

bool comparePointerToCard(const PokerCard* left, const PokerCard* right)
{
	return left->compareWithOtherCard(right) <= 0;
}

