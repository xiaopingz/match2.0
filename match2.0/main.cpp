#include"MDriver.h"
#include"PersonInfo.h"
#include<iostream>
#include<time.h>

void showStartInfo()
{
	std::cout<<"\n\n***************数字化婚姻配对2.0****************"<<std::endl;
	std::cout<<"Welcome! Now we begin to make pairs from the exist person informations!"<<std::endl;
}
 
void main()
{
		PersonGroupPtr	pPGMale, pPGFemale;

		showStartInfo();

		pPGMale		=	PersonInfo::readFromFile("../2_male.txt");
		pPGFemale	=	PersonInfo::readFromFile("../2_female.txt");

		BGPairsPtr pPairs	=	MDriver::makeAllPairs(pPGMale,pPGFemale);
		//PersonInfo::showPairs(pPairs);	//	显示主角的配对情况
		PersonInfo::dumpPairsToFile(pPairs,"../matched.txt");
		std::cout<<"Please check the matched pairs in the file \"../matched.txt\"!"<<std::endl;
}