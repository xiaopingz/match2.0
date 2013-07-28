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
	enum ptem_t{
		user_id = 0,
		info_wealth,
		info_look,
		info_charactor,
		info_health,
		ratio_wealth,
		ratio_look,
		ratio_charactor,
		ratio_health,  //对配偶四项指标的期望百分比，四者和为100，各自取值1~97
		gender,   //1:male; 0:female
		min_expertation, //对异性满意度的最低期望值( 男性用户则为0 ）
		ITEM_LEN
	};

public:
	PersonInfo();
	PersonInfo(int * items);
	
	int		sumOfInfo();
	int		getSatDegree(PersonInfoPtr p);		//计算一个人对另一个人的满意度
	int		getPersonGenger();
	int		getUsrid();
	
	//关于选择最优对象的一组函数，下面几个函数都是来支持第一个函数的，细分一下，使得逻辑更清晰，调试更方便。
	PersonInfoPtr 	selectTheBestOne(PersonGroupPtr group);	
	PersonInfoPtr	selectSatBiggerThanExp(PersonGroupPtr group);	//男性候选人中降序，有满意度大于等于女性期望的1.5倍，则选择该男性
	int				isNoBestOne(PersonGroupPtr group);	//是否，男性候选人的所有满意度都小于女性期望值
	PersonGroupPtr	selectMaxSatDegree(PersonGroupPtr group);
	static	PersonGroupPtr	selectMaxSum(PersonGroupPtr group);
	static	PersonInfoPtr	selectMinId(PersonGroupPtr group);
	
	//快速获得用户各种属性（封装和复用）
	inline int &     at(ptem_t i){return m_arrDetails[i];}
	inline const int &     at(ptem_t i)const {return m_arrDetails[i];}
	
	//针对初赛代码的优化：对于多次重复的代码，进行了简单的封装。
	std::string			to_string() const ;

	static PersonGroupPtr	readFromFile(const std::string & file);	//从文件中读取用户信息
	static PersonGroupPtr	generateRandomPersons(int num, int gender);	//产生随机信息的用户，num为需产生的个数，gender为性别
	static PersonInfoPtr	generateOnePerson(int id, int gender);


	static void			showPairs(BGPairsPtr ps);
	static void			dumpPairsToFile(BGPairsPtr ps, const std::string & file);
	
	
protected:
	int m_arrDetails[ITEM_LEN];
};//end class PersonInfo;
#endif