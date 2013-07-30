#include "PersonInfo.h"
#include<fstream>
#include<iostream>

PersonInfo::PersonInfo()
	:m_userID(-2),m_info_wealth(0),m_info_look(0),m_info_health(0),m_info_charactor(0),m_ratio_wealth(0),m_ratio_look(0),m_ratio_charactor(0),m_ratio_health(0),m_gender(0),m_mixExpertation(0)
{
}

PersonInfo::PersonInfo(int uid, int iwealth, int ilook, int icharactor, int ihealth, int rwealth, int rlook, int rcharactor, int rhealth, int igender, int mixExpertation)
	:m_userID(uid),m_info_wealth(iwealth),m_info_look(ilook),m_info_health(ihealth),m_info_charactor(icharactor),m_ratio_wealth(rwealth),m_ratio_look(rlook),m_ratio_charactor(rcharactor),m_ratio_health(rhealth),m_gender(igender),m_mixExpertation(mixExpertation)
{
}

int		PersonInfo::sumOfInfo()
{
	return m_info_charactor+m_info_look+m_info_wealth+m_info_health;
}

int		PersonInfo::getSatDegree(PersonInfoPtr p)
{
	int	sd	=	m_ratio_charactor * p->m_info_charactor + m_ratio_look * p->m_info_look + m_ratio_wealth * p->m_info_wealth + m_ratio_health * p->m_ratio_health;
	return sd;
}

int		PersonInfo::getPersonGenger()
{
	return	m_gender;
}

int		PersonInfo::getUsrid()
{
	return m_userID;
}

PersonInfoPtr 	PersonInfo::selectTheBestOne(PersonGroupPtr group)
{
	if ( m_gender==0 )
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
		int tmpDegree, standard;
		standard	=	m_mixExpertation*1.5;
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
		if ( getSatDegree(*it)>=m_mixExpertation )
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
	PersonGroupPtr	pPersonGroup	=	std::shared_ptr<PersonGroup>(new PersonGroup());
	std::ifstream	fRead;
	fRead.open(file);
	if( !fRead.good() )
	{
		std::cout<<"Open file: "<<file<<" failed!"<<std::endl;
		return NULL;
	}
	int gender,id,w,l,c,h,rw,rl,rc,rh,me=0;
	char t;		//	读取符号','

	if( file.find("2_female.txt")!=std::string::npos )
		gender	=	0;		// female
	else if( file.find("2_male.txt")!=std::string::npos )
		gender	=	1;		//male

	while( !fRead.eof() )
	{
		if( gender==1 )
			fRead>>id>>t>>w>>t>>l>>t>>c>>t>>h>>t>>rw>>t>>rl>>t>>rc>>t>>rh;
		else
			fRead>>id>>t>>w>>t>>l>>t>>c>>t>>h>>t>>rw>>t>>rl>>t>>rc>>t>>rh>>t>>me;

		if(fRead.bad()||fRead.fail())
			continue;
		PersonInfoPtr	pPerson	=	std::shared_ptr<PersonInfo>(new PersonInfo(id,w,l,c,h,rw,rl,rc,rh,gender,me));
		pPersonGroup->push_back(pPerson);
	}
	fRead.close();
	return	pPersonGroup;
}

void			PersonInfo::showPairs(BGPairsPtr ps)
{
	std::vector<BGPair>::iterator itPair;
	for( itPair=ps->begin();itPair != ps->end();++itPair )
	{
		PersonInfoPtr pBoy	=	(*itPair).first;
		PersonInfoPtr pGirl	=	(*itPair).second;
		if ( pGirl->getUsrid()==-1 || pBoy->getUsrid()==-1 )
		{	//此处加了if条件判断，则只显示主角的配对情况。
			std::cout<<"主角配对 M:"<<pBoy->m_userID<<" INFO:"<<pBoy->m_info_wealth<<","<<pBoy->m_info_look<<","<<pBoy->m_info_charactor<<","<<pBoy->m_info_health<<","<<pBoy->m_ratio_wealth<<","<<pBoy->m_ratio_look<<","<<pBoy->m_ratio_charactor<<","<<pBoy->m_ratio_health<<"<--->";
			std::cout<<" F:"<<pGirl->m_userID<<" INFO:"<<pGirl->m_info_wealth<<","<<pGirl->m_info_look<<","<<pGirl->m_info_charactor<<","<<pGirl->m_info_health<<","<<pGirl->m_ratio_wealth<<","<<pGirl->m_ratio_look<<","<<pGirl->m_ratio_charactor<<","<<pGirl->m_ratio_health<<std::endl;
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
			fWrite<<"M:"<<pBoy->m_userID<<" INFO:"<<pBoy->m_info_wealth<<","<<pBoy->m_info_look<<","<<pBoy->m_info_charactor<<","<<pBoy->m_info_health<<","<<pBoy->m_ratio_wealth<<","<<pBoy->m_ratio_look<<","<<pBoy->m_ratio_charactor<<","<<pBoy->m_ratio_health<<"<--->";
			fWrite<<" F:"<<pGirl->m_userID<<" INFO:"<<pGirl->m_info_wealth<<","<<pGirl->m_info_look<<","<<pGirl->m_info_charactor<<","<<pGirl->m_info_health<<","<<pGirl->m_ratio_wealth<<","<<pGirl->m_ratio_look<<","<<pGirl->m_ratio_charactor<<","<<pGirl->m_ratio_health<<std::endl;
		}
		else if( !pBoy )
			fWrite<<"NONE"<<"<--->"<<" F:"<<pGirl->m_userID<<" INFO:"<<pGirl->m_info_wealth<<","<<pGirl->m_info_look<<","<<pGirl->m_info_charactor<<","<<pGirl->m_info_health<<","<<pGirl->m_ratio_wealth<<","<<pGirl->m_ratio_look<<","<<pGirl->m_ratio_charactor<<","<<pGirl->m_ratio_health<<std::endl;
		else
			fWrite<<"M:"<<pBoy->m_userID<<" INFO:"<<pBoy->m_info_wealth<<","<<pBoy->m_info_look<<","<<pBoy->m_info_charactor<<","<<pBoy->m_info_health<<","<<pBoy->m_ratio_wealth<<","<<pBoy->m_ratio_look<<","<<pBoy->m_ratio_charactor<<","<<pBoy->m_ratio_health<<"<--->"<<" NONE"<<std::endl;
	}
	fWrite.close();
}
