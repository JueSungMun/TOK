#pragma once
class Maps
{
private:
	
public:
	enum DICE {ONE=1, TWO, THREE, FOUR, FIVE, SIX};
	enum MAPS {ATTACK, DEPENCE, MAGIC};
	MAPS maps[10][10];

	Maps(void);
	~Maps(void);
	DICE rollDice();
	MAPS getTypeOftile(int, int);

	
};

