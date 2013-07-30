#ifndef MDRIVER_H_
#define MDRIVER_H_
#include "PersonInfo.h"

class MDriver
{
public:
	
	static BGPairsPtr	makeAllPairs(PersonGroupPtr boys, PersonGroupPtr girls);
	
	static BGPair		makeOnePair(PersonGroupPtr boys, PersonGroupPtr girls);
	static	PersonGroupPtr		getHotestGirl(std::shared_ptr<MapGB>	pMapGB);
};//end class MDRIVER_H_
#endif