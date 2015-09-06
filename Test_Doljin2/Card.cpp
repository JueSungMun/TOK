#include "Card.h"
#include <time.h>
#include <stdlib.h>

Card::Card(void)
{
}

Card::~Card(void)
{
}

int Card::getPassiveCard(char* str)
{	
	srand(time(NULL)*rand());
	int tmp = rand()%13;

	if(str == "ATTACK")
	{
		if(tmp<=6)
		{
			return AP10;
		}
		else if(7<=tmp && tmp<=9)
		{
			return AP20;
		}
		else 
		{
			return AP30;
		}
	}

	if(str == "DEPENCE")
	{
		if(tmp<=6)
		{
			return DP10;
		}
		else if(7<=tmp && tmp<=9)
		{
			return DP20;
		}
		else 
		{
			return DP30;
		}
	}
}

int Card::getActiveCard(char *str)
{
	srand(time(NULL)*rand());
	int tmp = rand()%13;
	if(str == "ATTACK")
	{
		if(tmp<=6)
		{
			return AACTIVE_20;
		}
		else if(7<=tmp && tmp<=9)
		{
			return AACTIVE_30;
		}
		else 
		{
			return AACTIVE_40;
		}
	}

	if(str == "DEPENCE")
	{
		if(tmp<=6)
		{
			return DACTIVE_20;
		}
		else if(7<=tmp && tmp<=9)
		{
			return DACTIVE_30;
		}
		else 
		{
			return DACTIVE_40;
		}
	}

	if(str == "MAGIC")
	{
		if(tmp<=6)
		{
			return MP10;
		}
		else if(7<=tmp && tmp<=9)
		{
			return MP20;
		}
		else 
		{
			return MP30;
		}
	}
}
