#include "Hero.h"
#include "Card.h"
#include "Maps.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <algorithm>

Hero::Hero(void)
{
}

Hero::~Hero(void)
{
}

Hero::Hero(char* heroName)
{
	if(heroName == "One")
	{
		name = "One";
		attackPoint = 75;
		healthPoint = 300;
		memset(&locationOnTheMap, 0, sizeof(locationOnTheMap));
		locationOnTheMap[0][0] = 1;
		indexA=0;
		indexB=0;
	}
	else if(heroName == "Two")
	{
		name = "Two";
		attackPoint = 100;
		healthPoint = 250;
		memset(&locationOnTheMap, 0, sizeof(locationOnTheMap));
		locationOnTheMap[0][0] = 1;
		indexA=0;
		indexB=0;
	}
	else
	{
		std::cout << "잘못된 이름입니다" << endl;
		getchar();
		exit(1);
	}
}

int Hero::getAp() { return attackPoint; }

int Hero::getHp() { return healthPoint; }

int Hero::getIndexA() {	return indexA;}

int Hero::getIndexB() {	return indexB;}

char* Hero::getName() { return name; }

void Hero::setAp(int tmp) {	attackPoint = tmp; }

void Hero::setHp(int tmp) { 
	if(tmp<0)
		healthPoint=0;
	else
		healthPoint = tmp; 
}

void Hero::GetAttackCard()
{
	Card tmp;
	srand((unsigned int)time(NULL));
	int randNum = rand();
	if(randNum%2==0)
	{
		//패시브카드 획득
		int getCard = tmp.getPassiveCard("ATTACK");
		attackPassiveCard.push_back(getCard);
		attackPoint += getCard;
	}
	else
	{
		//액티브카드 획득
		int getCard = tmp.getActiveCard("ATTACK");
		attackActiveCard.push_back(getCard);
	}
}

void Hero::GetDepenceCard()
{
	Card tmp;
	srand((unsigned int)time(NULL));
	int randNum = rand();
	if(randNum%2==0)
	{
		//패시브카드 획득
		int getCard = tmp.getPassiveCard("DEPENCE");
		depencePassiveCard.push_back(getCard);
		healthPoint += getCard;
	}
	else
	{
		//액티브카드 획득
		int getCard = tmp.getActiveCard("DEPENCE");
		depenceActiveCard.push_back(getCard);
	}
}

void Hero::GetMagicCard()
{
	Card tmp;
	magicActiveCard.push_back(tmp.getActiveCard("MAGIC"));
}

void Hero::rolling(Maps* m, Hero* enemy)
{
	int dice = m->rollDice();
	preIndexA = indexA;
	preIndexB = indexB;
	
	for(int i=0; i<dice; i++)
	{
		if(indexA==0 && indexB!=9)
			indexB++;
		else if(indexB==9 && indexA!=9)
			indexA++;
		else if(indexA==9 && indexB!=0)
			indexB--;
		else if(indexA!=0 && indexB==0)
			indexA--;
	}
	locationOnTheMap[preIndexA][preIndexB] = 0;
	locationOnTheMap[indexA][indexB] = 1;

	if(m->getTypeOftile(indexA, indexB) == Maps::ATTACK)
	{
		GetAttackCard();
	}
	else if(m->getTypeOftile(indexA, indexB) == Maps::DEPENCE)
	{
		GetDepenceCard();
	}
	else if(m->getTypeOftile(indexA, indexB) == Maps::MAGIC)
	{
		GetMagicCard();
	}
	if(checkMeet(enemy))
		this->Fight(enemy);
}

bool Hero::checkMeet(Hero* enemy)
{
	if((indexA==enemy->getIndexA()) && (indexB==enemy->getIndexB()))
		return true;
	else 
		return false;
}

void Hero::ShowStat()
{
	std::cout << "Name : " << name << endl; 
	std::cout << "Attack Point : "<< attackPoint << endl;
	std::cout << "Health Point : "<< healthPoint << endl;
	std::cout << "Location : " << indexA << ", " << indexB << endl;
}

void Hero::Fight(Hero* enemy)
{
	healthPoint -= enemy->getAp();
	enemy->setHp(enemy->getHp()-attackPoint);

	if(healthPoint <= 0 && enemy->getHp() > 0)
		std::cout << enemy->getName() << "이 이겼습니다!" << endl;
	else if(healthPoint > 0 && enemy->getHp() <= 0 )
		std::cout << name << "이 이겼습니다!" << endl;
	else
		std::cout << "무승부입니다!" << endl;
}

void Hero::ShowActiveCards()
{
	Card tmp;
	for(int i=0; i<attackActiveCard.size(); i++)
	{
		if(attackActiveCard.at(i) == Card::AACTIVE_20)
			std::cout<<i<<".공격력+20"<<" ";
		else if(attackActiveCard.at(i)  == Card::AACTIVE_30)
			std::cout<<i<<".공격력+30"<<" ";
		else if(attackActiveCard.at(i) == Card::AACTIVE_40)
			std::cout<<i<<".공격력+40"<<" ";
	}
	std::cout<<std::endl;
	for(int i=1; i<=depenceActiveCard.size(); i++)
	{
		if(depenceActiveCard.at(i) == Card::DACTIVE_20)
			std::cout<<i<<".체력+20"<<" ";
		else if(depenceActiveCard.at(i) == Card::DACTIVE_30)
			std::cout<<i<<".체력+30"<<" ";
		else if(depenceActiveCard.at(i) == Card::DACTIVE_40)
			std::cout<<i<<".체력+40"<<" ";
	}
	std::cout<<std::endl;
}

void Hero::UseActiveAttack(int card)
{
	Card tmp;
	vector<int>::iterator i = find(attackActiveCard.begin(), attackActiveCard.end(), card);
	if(*i == Card::AACTIVE_20)
		attackPoint += 20;
	if(*i == Card::AACTIVE_30)
		attackPoint += 30;
	if(*i == Card::AACTIVE_40)
		attackPoint += 40;
}

void Hero::UseActiveDepence(int card)
{
	Card tmp;
	vector<int>::iterator i = find(depenceActiveCard.begin(), depenceActiveCard.end(), card);
	if(*i == Card::DACTIVE_20)
		healthPoint += 20;
	if(*i == Card::DACTIVE_30)
		healthPoint += 30;
	if(*i == Card::DACTIVE_40)
		healthPoint += 40;
}