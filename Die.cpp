
#include "stdafx.h"

#include <cstdlib> 
#include <ctime>
#include<iostream>
using namespace std;

class Die
{
private:
	int sides;
	int value;

public:
	Die(int = 6);
	int roll();
};

Die::Die(int numSides)
{
	unsigned seed = time(0);
	srand(seed);
	sides = numSides;
	roll();
}

int Die::roll()
{
	const int MIN_VALUE = 1;
	value = (rand() % (sides - MIN_VALUE + 1) + MIN_VALUE);
	return value;
}

int main()
{
	Die die1;
	int choice = 1;
	int totalUser = die1.roll();
	int totalComp = die1.roll();


	while (choice == 1)
	{
		cout << "Roll: " << totalUser << endl;
		cout << "Type 1 to roll." << endl;
		cout << "Type 2 to hold." << endl;
		totalComp = totalComp + die1.roll();
		cin >> choice;

		if (choice == 1)
		{
			totalUser = totalUser + die1.roll();
		}

		if (totalUser > 21)
		{
			cout << "Roll: " << totalUser << endl;
			cout << "Over 21! You lose." << endl;
			return 0;
		}
	}

	if (totalUser > totalComp || totalComp > 21)
	{
		cout << "Computer rolled: " << totalComp << "." << endl;
		cout << "You win!" << endl;
	}

	else if (totalComp > totalUser)
	{
		cout << "Computer rolled: " << totalComp << "." << endl;
		cout << "You lose!" << endl;
	}

    return 0;
}

