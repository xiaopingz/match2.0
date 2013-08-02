#ifndef PERSON_INFO_H_
#define PERSON_INFO_H_
#include <vector>
#include <map>
#include <memory>
#include <string>


class PersonInfo;
typedef std::shared_ptr<PersonInfo> PersonInfoPtr;
typedef std::vector<PersonInfoPtr> PersonGroup;
typedef std::shared_ptr<PersonGroup> PersonGroupPtr;
typedef std::map<PersonInfoPtr,PersonGroupPtr>	MapGB;	//存放女性候选人信息（给女性投票过的男性）
typedef std::pair<PersonInfoPtr, PersonInfoPtr> BGPair; //<Boy, Girl>
typedef std::vector<BGPair>	 BGPairs;
typedef std::shared_ptr<BGPairs>	BGPairsPtr;


class PersonInfo
{
public:
	PersonInfo();
	PersonInfo(int uid, int iwealth, int ilook, int icharactor, int ihealth, int rwealth, int rlook, int rcharactor, int rhealth, int igender, int mixExpertation);
	
	int		sumOfInfo();
	int		getSatDegree(PersonInfoPtr p);		//计算一个人对另一个人的满意度
	int		getPersonGenger();
	int		getUsrid();
	
	PersonInfoPtr 	selectTheBestOne(PersonGroupPtr group);	//选择另一性别组中最满意的人
	PersonInfoPtr	selectSatBiggerThanExp(PersonGroupPtr group);	//男性候选人中降序，有满意度大于等于女性期望的1.5倍，则选择该男性
	int				isNoBestOne(PersonGroupPtr group);	//是否，男性候选人的所有满意度都小于女性期望值
	PersonGroupPtr	selectMaxSatDegree(PersonGroupPtr group);
	static	PersonGroupPtr	selectMaxSum(PersonGroupPtr group);
	static	PersonInfoPtr	selectMinId(PersonGroupPtr group);
	
	
	static PersonGroupPtr	readFromFile(const std::string & file);	//从文件中读取用户信息
	static PersonGroupPtr	generateRandomPersons(int num, int gender);	//产生随机信息的用户，num为需产生的个数，gender为性别
	static PersonInfoPtr	generateOnePerson(int id, int gender);

	static void			showPairs(BGPairsPtr ps);
	static void			dumpPairsToFile(BGPairsPtr ps, const std::string & file);
	
protected:
	int m_userID;
	int m_info_wealth;		//本人属性
	int m_info_look;		
	int m_info_charactor;	
	int m_info_health;		
	int m_ratio_wealth;
	int m_ratio_look;
	int m_ratio_charactor;
	int m_ratio_health;		//对配偶四项指标的期望百分比，四者和为100，各自取值1~97
	int m_gender;			//1:male; 0:female
	int m_mixExpertation;	//对异性满意度的最低期望值( 男性用户则为0 ）
};//end class PersonInfo;
#endif