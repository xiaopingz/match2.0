#include"MDriver.h"
#include"PersonInfo.h"
#include<iostream>
#include <stdlib.h>	//srand, rand
#include<time.h>

void showStartInfo()
{
	std::cout<<"\n\n***************数字化婚姻配对2.0****************"<<std::endl;
	std::cout<<"Welcome! Please choose the mode:\n1. User-defined specimen;\n2. Read from files:\n0. Exit!"<<std::endl;
}
 
void main()
{
	while(1)	
	{	
		srand(time(NULL));
		PersonGroupPtr	pPGMale, pPGFemale;
		std::string		input;
		
		showStartInfo();
		std::cin>>input;
		if( input=="1" )
		{
			int nMale, nFemale;
			std::cout<<"Please input the numbers of Male & Female to match:"<<std::endl;
			std::cin>>nMale>>nFemale;
			pPGMale    =  PersonInfo::generateRandomPersons(nMale,1);
			pPGFemale  =  PersonInfo::generateRandomPersons(nFemale,0);
		}
		else if( input=="2" )
		{
			pPGMale		=	PersonInfo::readFromFile("../2_male.txt");
			pPGFemale	=	PersonInfo::readFromFile("../2_female.txt");
		}
		else if( input=="0" )
			break;
		else
		{
			std::cout<<"Illegal input! Please choose again!"<<std::endl;
			continue;
		}
		
		BGPairsPtr pPairs	=	MDriver::makeAllPairs(pPGMale,pPGFemale);
		//PersonInfo::showPairs(pPairs);	//	显示配对成功的情况
		PersonInfo::dumpPairsToFile(pPairs,"../matched.txt");	//将配对情况存入文件
		std::cout<<"Please check the matched pairs in the file \"../matched.txt\"!"<<std::endl;
	}
}