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
typedef std::map<PersonInfoPtr,PersonGroupPtr>	MapGB;	//���Ů�Ժ�ѡ����Ϣ����Ů��ͶƱ�������ԣ�
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
		ratio_health,  //����ż����ָ��������ٷֱȣ����ߺ�Ϊ100������ȡֵ1~97
		gender,   //1:male; 0:female
		min_expertation, //����������ȵ��������ֵ( �����û���Ϊ0 ��
		ITEM_LEN
	};

public:
	PersonInfo();
	PersonInfo(int * items);
	
	int		sumOfInfo();
	int		getSatDegree(PersonInfoPtr p);		//����һ���˶���һ���˵������
	int		getPersonGenger();
	int		getUsrid();
	
	//����ѡ�����Ŷ����һ�麯�������漸������������֧�ֵ�һ�������ģ�ϸ��һ�£�ʹ���߼������������Ը����㡣
	PersonInfoPtr 	selectTheBestOne(PersonGroupPtr group);	
	PersonInfoPtr	selectSatBiggerThanExp(PersonGroupPtr group);	//���Ժ�ѡ���н���������ȴ��ڵ���Ů��������1.5������ѡ�������
	int				isNoBestOne(PersonGroupPtr group);	//�Ƿ����Ժ�ѡ�˵���������ȶ�С��Ů������ֵ
	PersonGroupPtr	selectMaxSatDegree(PersonGroupPtr group);
	static	PersonGroupPtr	selectMaxSum(PersonGroupPtr group);
	static	PersonInfoPtr	selectMinId(PersonGroupPtr group);
	
	//���ٻ���û��������ԣ���װ�͸��ã�
	inline int &     at(ptem_t i){return m_arrDetails[i];}
	inline const int &     at(ptem_t i)const {return m_arrDetails[i];}
	
	//��Գ���������Ż������ڶ���ظ��Ĵ��룬�����˼򵥵ķ�װ��
	std::string			to_string() const ;

	static PersonGroupPtr	readFromFile(const std::string & file);	//���ļ��ж�ȡ�û���Ϣ
	static PersonGroupPtr	generateRandomPersons(int num, int gender);	//���������Ϣ���û���numΪ������ĸ�����genderΪ�Ա�
	static PersonInfoPtr	generateOnePerson(int id, int gender);


	static void			showPairs(BGPairsPtr ps);
	static void			dumpPairsToFile(BGPairsPtr ps, const std::string & file);
	
	
protected:
	int m_arrDetails[ITEM_LEN];
};//end class PersonInfo;
#endif