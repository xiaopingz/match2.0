#include "MDriver.h"
#include<algorithm>	//std::find
#include<iostream>

BGPairsPtr	MDriver::makeAllPairs(PersonGroupPtr boys, PersonGroupPtr girls)
{
	BGPairsPtr	pBGPairs	=	std::make_shared<BGPairs>();
	while( boys->size() && girls->size() )
	{
		BGPair	onePair	=	makeOnePair(boys,girls);	//	一次配对
		pBGPairs->push_back(onePair);					//将结果放入BGPairs当中
		PersonGroup::iterator	it	=	std::find(boys->begin(),boys->end(),onePair.first);	//查找已配对的男性的位置
		if(it!=boys->end())
			boys->erase(it);		//删除该男性信息
		it	=	std::find(girls->begin(),girls->end(),onePair.second);		//查找已配对的女性的位置
		if( it!=girls->end() )
			girls->erase(it);		//	删除该女性信息
	}
	return	pBGPairs;
}
	
BGPair		MDriver::makeOnePair(PersonGroupPtr boys, PersonGroupPtr girls)
{
	std::shared_ptr<MapGB>	pMapGB	=	std::make_shared<MapGB>();
	PersonInfoPtr	girlMatched, boyMatched;

	for( PersonGroup::size_type ixTmp=0;ixTmp!=(*girls).size();++ixTmp )
	{
		PersonGroupPtr	pPG	=	std::make_shared<PersonGroup>();
		PersonInfoPtr	pGirl	=	(*girls)[ixTmp];
		(*pMapGB)[pGirl]	=	pPG;
	}
	for( PersonGroup::iterator itBoys = boys->begin(); itBoys!=boys->end(); ++itBoys )
	{
		//遍历男性，给女士投票
		PersonInfoPtr	girlToVote	=	(*itBoys)->selectTheBestOne(girls);
		(*pMapGB)[girlToVote]->push_back(*itBoys);	
	}
	
	do 
	{
		PersonGroupPtr	pPGHotGirls	=	getHotestGirl(pMapGB);
		if ( pPGHotGirls->size()==1 )
		{
			girlMatched	=	*(pPGHotGirls->begin());
		}
		else
		{
			PersonGroupPtr	pPGMSGirls	=	PersonInfo::selectMaxSum(pPGHotGirls);
			if ( pPGMSGirls->size()==1 )
			{
				girlMatched	=	*(pPGMSGirls->begin());
			}
			else
			{
				girlMatched	=	PersonInfo::selectMinId(pPGMSGirls);
			}
		}
		boyMatched	=	girlMatched->selectTheBestOne((*pMapGB)[girlMatched]);	
		if (!boyMatched)
		{	//配对失败
			(*pMapGB)[girlMatched]->clear();
			pMapGB->erase(girlMatched);		
		}
	} while (!boyMatched && pMapGB->size());	//配对失败，则进行下一个。直到配对成功或map为空（所有候选女性都不能配对）
	
	return std::make_pair(boyMatched,girlMatched);
}

PersonGroupPtr		MDriver::getHotestGirl(std::shared_ptr<MapGB>	pMapGB)
{
	PersonGroupPtr	pPGHotGirls	=	std::make_shared<PersonGroup>();
	MapGB::iterator	it, itBest;
	PersonGroup::size_type	ixMax	=	0, ixTmp;

	for ( it=pMapGB->begin();it!=pMapGB->end();++it )
	{
		ixTmp	=	(it->second)->size();
		if ( ixTmp>ixMax || ixMax==ixTmp )
		{
			if ( ixTmp>ixMax )
			{
				ixMax	=	ixTmp;
				pPGHotGirls->clear();
			}
			pPGHotGirls->push_back(it->first);
		}
	}
	return	pPGHotGirls;
}