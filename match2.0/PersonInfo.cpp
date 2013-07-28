#include "PersonInfo.h"
#include<fstream>
#include<iostream>
#include <sstream>

PersonInfo::PersonInfo()
{
	memset(m_arrDetails, 0, sizeof(int) * ITEM_LEN);
	at(user_id) = -2;
}

PersonInfo::PersonInfo(int * items)
{
	memcpy((void *)m_arrDetails, items, sizeof(int) * ITEM_LEN);
}

int		PersonInfo::sumOfInfo()
{
	return at(info_charactor)+at(info_look)+at(info_wealth)+at(info_health);
}

int		PersonInfo::getSatDegree(PersonInfoPtr p)
{
	int	sd	=	at(ratio_charactor) * p->at(info_charactor) + at(ratio_look) * p->at(info_look) + at(ratio_wealth) * p->at(info_wealth) + at(ratio_health) * p->at(ratio_health);
	return sd;
}

int		PersonInfo::getPersonGenger()
{
	return	at(gender);
}

int		PersonInfo::getUsrid()
{
	return at(user_id);
}

PersonInfoPtr 	PersonInfo::selectTheBestOne(PersonGroupPtr group)
{
	if ( at(gender)==0 )
	{
		PersonInfoPtr	p	=	selectSatBiggerThanExp(group);
		if ( p )
			return p;
		else if( isNoBestOne(group) )
			return NULL;
	}
	PersonGroupPtr pPGMaxSatDegree	=	selectMaxSatDegree(group);
	if( pPGMaxSatDegree->size()==1 )
	{
		return	*(pPGMaxSatDegree->begin());
	}
	else
	{
		PersonGroupPtr	pPGMaxSum	=	selectMaxSum(pPGMaxSatDegree);
		if ( pPGMaxSum->size()==1 )
		{
			return	*(pPGMaxSum->begin());
		}
		else
		{
			return	selectMinId(pPGMaxSum);
		}
	}
}

PersonInfoPtr	PersonInfo::selectSatBiggerThanExp(PersonGroupPtr group)
{
	PersonGroup::size_type ix;
	for ( ix=group->size();ix>0;--ix )
	{
		double tmpDegree, standard;
		standard	=	at(min_expertation)*1.5;
		tmpDegree	=	getSatDegree((*group)[ix-1]);
		if ( tmpDegree>=standard )
		{
			return (*group)[ix-1];
		}
	}
	if ( ix==0 )
		return NULL;
}

int				PersonInfo::isNoBestOne(PersonGroupPtr group)
{
	for ( PersonGroup::iterator it = group->begin();it!=group->end();++it )
	{
		if ( getSatDegree(*it)>=at(min_expertation) )
			return 0;
	}
	return 1;
}

PersonGroupPtr	PersonInfo::selectMaxSatDegree(PersonGroupPtr group)
{
	PersonGroup::iterator	itNow,itMax;
	PersonGroupPtr	pPGMSD	=	std::make_shared<PersonGroup>();
	int highestDegree=0, tmpDegree=0;

	for ( itNow=group->begin();itNow!=group->end();++itNow )
	{
		tmpDegree	=	getSatDegree(*itNow);
		if ( tmpDegree>highestDegree || tmpDegree==highestDegree )
		{
			if ( tmpDegree>highestDegree )
			{
				highestDegree	=	tmpDegree;
				pPGMSD->clear();
			}
			pPGMSD->push_back(*itNow);
		}
	}
	return	pPGMSD;
}

PersonGroupPtr	PersonInfo::selectMaxSum(PersonGroupPtr group)
{
	PersonGroup::iterator	itNow,itMax;
	PersonGroupPtr	pPGMS	=	std::make_shared<PersonGroup>();
	int iSumNow=0, iSumMax=0;

	for ( itNow=group->begin();itNow!=group->end();++itNow )
	{
		iSumNow	=	(*itNow)->sumOfInfo();
		if ( iSumNow>iSumMax || iSumNow==iSumMax )
		{
			if ( iSumNow>iSumMax )
			{
				iSumMax	=	iSumNow;
				pPGMS->clear();
			}
			pPGMS->push_back(*itNow);
		}
	}
	return	pPGMS;
}

PersonInfoPtr	PersonInfo::selectMinId(PersonGroupPtr group)
{
	PersonGroup::iterator	itNow, itBest;
	int	iIdBest=200, iIdNow=200;

	for ( itNow=group->begin();itNow!=group->end();++itNow )
	{
		iIdNow	=	(*itNow)->getUsrid();
		if ( iIdNow<iIdBest )
		{
			iIdBest	=	iIdNow;
			itBest	=	itNow;
		}
	}
	return *itBest;
}

PersonGroupPtr  PersonInfo::readFromFile(const std::string & file)
{
	PersonGroupPtr	pPersonGroup	=	std::make_shared<PersonGroup>();
	std::ifstream	fRead;
	fRead.open(file);
	if( !fRead.good() )
	{
		std::cout<<"Open file: "<<file<<" failed!"<<std::endl;
		return NULL;
	}
	char t;		//	读取符号','
	int info[ITEM_LEN];
	info[min_expertation]	=	0;

	if( file.find("2_female.txt")!=std::string::npos )
		info[gender]	=	0;		// female
	else if( file.find("2_male.txt")!=std::string::npos )
		info[gender]	=	1;		//male

	
	while( !fRead.eof() )
	{
		fRead>>info[user_id] >> t >> 
			info[info_wealth] >> t>>
			info[info_look] >>t >>
			info[info_charactor] >> t >>
			info[info_health] >> t >>
			info[ratio_wealth] >> t >>
			info[ratio_look] >> t >>
			info[ratio_charactor] >> t >>
			info[ratio_health];
		
		if( info[gender]!=1 )
		{
			fRead>>t>>info[min_expertation];
		}
		if(fRead.bad()||fRead.fail())
			continue;
		
		PersonInfoPtr	pPerson	=	std::shared_ptr<PersonInfo>(new PersonInfo(info));
		pPersonGroup->push_back(pPerson);
	}
	fRead.close();
	return	pPersonGroup;
}

PersonGroupPtr	PersonInfo::generateRandomPersons(int num,int gender)
{
	PersonGroupPtr	pPersonGroup	=	std::make_shared<PersonGroup>();
	for( int i = 0;i<num;++i )
	{
		PersonInfoPtr	pPerson	=	generateOnePerson(i,gender);
		pPersonGroup->push_back(pPerson);
	}
	return	pPersonGroup;
}

PersonInfoPtr	PersonInfo::generateOnePerson(int id, int gd)
{
	int info[ITEM_LEN];
	info[user_id] = id;
	info[gender] = gd;
	for(int i = info_wealth; i <= info_health; ++i)
		info[i] = rand() % 100 + 1;
	
	info[ratio_wealth]	=	rand()%97  + 1;	//生成1~97的随机数
	info[ratio_look]	=	rand()%(98-info[ratio_wealth]) + 1;
	info[ratio_charactor]	=	rand()%(99-info[ratio_wealth]-info[ratio_look]) + 1;
	info[ratio_health]	=	100 - info[ratio_wealth] - info[ratio_look] - info[ratio_charactor];
	if ( gd==0 )
	{
		info[min_expertation]	=	rand()%10000 + 1;
	}
	else		info[min_expertation] = 0;
	PersonInfoPtr	pPerson	=	std::shared_ptr<PersonInfo>(new PersonInfo(info));
	return	pPerson;
}

std::string PersonInfo::to_string() const
{
	std::stringstream ss;
	if(at(gender))
		ss<< "M:";
	else
		ss<<"F:";
	for(int i = 0; i < gender; ++i)
	{
			ss<<m_arrDetails[i];
			if ( i==0 )
				ss<<" INFO:";
			if(i != gender -1)
				ss<<",";
	}
	return ss.str();
}
void			PersonInfo::showPairs(BGPairsPtr ps)
{
	std::vector<BGPair>::iterator itPair;
	for( itPair=ps->begin();itPair != ps->end();++itPair )
	{
		PersonInfoPtr pBoy	=	(*itPair).first;
		PersonInfoPtr pGirl	=	(*itPair).second;
		if ( pGirl && pBoy )
		{	//此处加了if条件判断，则只显示主配对成功的情况。
			std::cout<<pBoy->to_string()<<"<--->";
			std::cout<<pGirl->to_string()<<std::endl;
		}
	}
}

void			PersonInfo::dumpPairsToFile(BGPairsPtr ps, const std::string & file)
{
	std::ofstream	fWrite(file);
	std::vector<BGPair>::iterator itPair;
	for( itPair=ps->begin();itPair != ps->end();++itPair )
	{
		PersonInfoPtr pBoy	=	(*itPair).first;
		PersonInfoPtr pGirl	=	(*itPair).second;
		if( pBoy && pGirl )
		{
			fWrite<<pBoy->to_string()<<"<--->";
			fWrite<<pGirl->to_string()<<std::endl;
		}
		else if( !pBoy )
			fWrite<<"NONE"<<"<--->"<<pGirl->to_string()<<std::endl;
		else
			fWrite<<pBoy->to_string()<<"<--->"<<" NONE"<<std::endl;
	}
	fWrite.close();
}
