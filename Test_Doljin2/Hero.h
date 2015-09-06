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

	//���� ��ġ ������ �������
	int locationOnTheMap[10][10];
	int preIndexA;
	int preIndexB;
	int indexA;
	int indexB;

public:
	Hero(void);
	~Hero(void);
	Hero(char*);

	//Get&Set�Լ�
	int getIndexA();
	int getIndexB();
	int getHp();
	int getAp();
	char* getName();
	void setHp(int);
	void setAp(int);
	
	//���� ���� ��Ƽ��ī�� ������
	void ShowActiveCards();

	//��Ƽ�� ī�� ���
	void UseActiveAttack(int);
	void UseActiveDepence(int);
	void UseActiveMagic(int);

	//���� ����â ������
	void ShowStat();

	//�������� ī�带 ȹ��
	void GetAttackCard();
	void GetDepenceCard();
	void GetMagicCard();

	//���� ����
	void Fight(Hero*);

	//�ֻ��� ����
	void rolling(Maps*, Hero*);

	//���� �������� üũ
	bool checkMeet(Hero*);
};

