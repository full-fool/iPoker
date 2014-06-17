#ifndef __POKER_VECTORPOINT_H__
#define __POKER_VECTORPOINT_H__

#include "PokerBase.h"
#include <vector>

class PokerVectorPoint: public PokerBase{
public:
	std::vector<PokerBase *> *pokerVectorPoint;
	
	PokerVectorPoint(std::vector<PokerBase *> * );
};

#endif