#ifndef MDRIVER_H_
#define MDRIVER_H_
#include "PersonInfo.h"

class MDriver
{
public:
	
	//make pairs for all boys and girls;
	static BGPairsPtr	makeAllPairs(PersonGroupPtr boys, PersonGroupPtr girls);
	
	//select the first pair for the boys and girls;
	static BGPair		makeOnePair(PersonGroupPtr boys, PersonGroupPtr girls);
	static	PersonGroupPtr		getHotestGirl(std::shared_ptr<MapGB>	pMapGB);
};//end class MDRIVER_H_
#endif