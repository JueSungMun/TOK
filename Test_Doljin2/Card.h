#pragma once

class Card
{
private:
	
public:
	enum ATTACK	 { AP10=10, AP20=20, AP30=30, AACTIVE_20=1, AACTIVE_30=2, AACTIVE_40=3};
	enum DEPENCE { DP10=10, DP20=20, DP30=30, DACTIVE_20=1, DACTIVE_30=2, DACTIVE_40=3};
	enum MAGIC	 { MP10, MP20, MP30};

	Card(void);
	~Card(void);
	int getPassiveCard(char*);
	int getActiveCard(char*);

};

