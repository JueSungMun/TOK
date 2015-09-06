#include <iostream>
#include <string>
#include <ctime>
#include <stdlib.h>
#include "Maps.h"
#include "Hero.h"
using namespace std;

int main()
{
	Hero* one = new Hero("One");
	Hero* two = new Hero("Two");
	Maps* map = new Maps;
	
	while(true)
	{
		string inputData;
		std::getline(std::cin, inputData);

		if(inputData == "exit")
		{
			exit(1);
		}
		if(inputData == "show")
		{
			one->ShowStat();
			two->ShowStat();
		}
		if(inputData == "one roll")
		{
			one->rolling(map, two);
		}
		if(inputData == "two roll")
		{
			two->rolling(map, one);
		}
		if(inputData == "one attack")
		{
			one->Fight(two);
		}
		if(inputData == "two attack")
		{
			two->Fight(one);
		}
		if(inputData == "one active")
		{
			one->ShowActiveCards();
			std::cout << "Attack Or Depence : ";
			string selectCard;
			std::getline(std::cin, selectCard);
			int num;
			std::cout << "select number : ";
			cin>>num;
			if(selectCard == "attack")
				one->UseActiveAttack(num);
			else if(selectCard == "depence") 
				one->UseActiveDepence(num);
		}
		if(inputData == "two active")
		{
			two->ShowActiveCards();
			std::cout << "Attack Or Depence : ";
			string selectCard;
			std::getline(std::cin, selectCard);
			int num;
			std::cout << "select number : ";
			cin>>num;
			if(selectCard == "attack")
				one->UseActiveAttack(num);
			else if(selectCard == "depence") 
				one->UseActiveDepence(num);
		}
	}

	delete one, two;
	return 0;
}