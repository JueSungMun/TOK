#pragma once
#include <vector>
#include "Maps.h"
#include "Card.h"
using namespace std;

class Hero
{
private:
	vector<int> attackPassiveCard;
	vector<int> depencePassiveCard;
	vector<int> attackActiveCard;
	vector<int> depenceActiveCard;
	vector<int> magicActiveCard;
	char* name;
	int healthPoint;
	int attackPoint;

	//현재 위치 관련한 멤버변수
	int locationOnTheMap[10][10];
	int preIndexA;
	int preIndexB;
	int indexA;
	int indexB;

public:
	Hero(void);
	~Hero(void);
	Hero(char*);

	//Get&Set함수
	int getIndexA();
	int getIndexB();
	int getHp();
	int getAp();
	char* getName();
	void setHp(int);
	void setAp(int);
	
	//현재 가진 액티브카드 보여줌
	void ShowActiveCards();

	//액티브 카드 사용
	void UseActiveAttack(int);
	void UseActiveDepence(int);
	void UseActiveMagic(int);

	//현재 상태창 보여줌
	void ShowStat();

	//종류별로 카드를 획득
	void GetAttackCard();
	void GetDepenceCard();
	void GetMagicCard();

	//상대와 대전
	void Fight(Hero*);

	//주사위 굴림
	void rolling(Maps*, Hero*);

	//상대와 만났는지 체크
	bool checkMeet(Hero*);
};

