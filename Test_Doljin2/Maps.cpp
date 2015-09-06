#include "Maps.h"
#include <time.h>
#include <stdlib.h>
#include <string>
#include <iostream>

Maps::Maps(void)
{
	memset(&maps, 0, sizeof(maps));
	//������
	maps[0][0] = ATTACK; 	maps[0][1] = DEPENCE;	maps[0][2] = ATTACK;	maps[0][3] = DEPENCE;	maps[0][4] = ATTACK; 	
	maps[0][5] = DEPENCE;	maps[0][6] = ATTACK;	maps[0][7] = DEPENCE;	maps[0][8] = ATTACK;	maps[0][9] = DEPENCE;

	//��������
	maps[1][9] = ATTACK;	maps[2][9] = DEPENCE;	maps[3][9] = ATTACK;	maps[4][9] = DEPENCE;	maps[5][9] = ATTACK;
	maps[6][9] = DEPENCE;	maps[7][9] = ATTACK;	maps[8][9] = DEPENCE;	maps[9][9] = ATTACK;

	//�Ʒ���
	maps[9][8] = DEPENCE;	maps[9][7] = ATTACK;	maps[9][6] = DEPENCE;	maps[9][5] = ATTACK;	maps[9][4] = DEPENCE;
	maps[9][3] = ATTACK;	 maps[9][2] = DEPENCE;	maps[9][1] = ATTACK;	maps[9][0] = DEPENCE;
	
	//������
	maps[8][0] = ATTACK;	maps[7][0] = DEPENCE;	maps[6][0] = ATTACK;	maps[5][0] = DEPENCE;	maps[4][0] = ATTACK;
	maps[3][0] = DEPENCE;	maps[2][0] = ATTACK;	maps[1][0] = DEPENCE;
}


Maps::~Maps(void)
{
}

Maps::DICE Maps::rollDice()
{
	srand(time(NULL));
	int tmp = rand();
	tmp = tmp%6;
	if(tmp==0)
	{
		std::cout<<"�ֻ��� �� : "<<ONE<<std::endl;
		return ONE;
	}
	else if(tmp==1)
	{
		std::cout<<"�ֻ��� �� : "<<TWO<<std::endl;
		return TWO;
	}
	else if(tmp==2)
	{
		std::cout<<"�ֻ��� �� : "<<THREE<<std::endl;
		return THREE;
	}
	else if(tmp==3)
	{
		std::cout<<"�ֻ��� �� : "<<FOUR<<std::endl;
		return FOUR;
	}
	else if(tmp==4)
	{
		std::cout<<"�ֻ��� �� : "<<FIVE<<std::endl;
		return FIVE;
	}
	else if(tmp==5)
	{
		std::cout<<"�ֻ��� �� : "<<SIX<<std::endl;
		return SIX;
	}
}

Maps::MAPS Maps::getTypeOftile(int idxA, int idxB)
{
	return maps[idxA][idxB];
}