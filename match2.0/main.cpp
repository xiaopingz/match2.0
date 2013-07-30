#include"MDriver.h"
#include"PersonInfo.h"
#include<iostream>
#include<stdlib.h>	//srand,rand
#include<time.h>

void showStartInfo()
{
	std::cout<<"\n\n***************数字化婚姻配对2.0****************"<<std::endl;
	std::cout<<"Welcome! Please choose the mode:\n1. Manual input;\n2. Auto generate:\n0. Exit!"<<std::endl;
}
 
void main()
{
	while(1)
	{
		srand(time(NULL));
		PersonGroupPtr	pPGMale	=	std::shared_ptr<PersonGroup>(new PersonGroup());
		PersonGroupPtr	pPGFemale	=	std::shared_ptr<PersonGroup>(new PersonGroup());
		int input;

		showStartInfo();
		std::cin>>input;
		/*if( input==1 )
		{
			pPlayer	=	PersonInfo::inputOnePerson();
			if( !pPlayer )
			{
				std::cout<<"You input of the personInfo is illegal!"<<std::endl;
				continue;
			}
			if(pPlayer->getPersonGenger()==1)
			{
				pPGMale		=	PersonInfo::generateRandomPersons(99,1);
				pPGFemale	=	PersonInfo::generateRandomPersons(100,0);
			}
			else
			{
				pPGMale		=	PersonInfo::generateRandomPersons(100,1);
				pPGFemale	=	PersonInfo::generateRandomPersons(99,0);
			}
			
		}
		else*/ if( input==2 )
		{
			pPGMale		=	PersonInfo::readFromFile("../2_male.txt");
			pPGFemale	=	PersonInfo::readFromFile("../2_female.txt");
			if( !pPGFemale || !pPGMale )
				continue;
			int iNum;
		}
		else if( input==0 )
			break;
		else
		{
			std::cout<<"Illegal input! Please choose again!"<<std::endl;
			continue;
		}

		BGPairsPtr pPairs	=	MDriver::makeAllPairs(pPGMale,pPGFemale);
		//PersonInfo::showPairs(pPairs);	//	显示主角的配对情况
		PersonInfo::dumpPairsToFile(pPairs,"../matched.txt");
		std::cout<<"Please check the matched pairs in the file \"../matched.txt\"!"<<std::endl;
	}
}