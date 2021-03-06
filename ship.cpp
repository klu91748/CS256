#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;



class Ship
{
protected:
	string name;
	string year;
public:
	Ship(string n, string y);
	void setYear(string y);
	void setName(string n);
	string getYear();
	string getName();
	virtual void print();
};
Ship::Ship(string n, string y)
{
	name = n;
	year = y;
}

void Ship::print()
{
	cout << name << " was built in " << year << "." << endl;
}

void Ship::setYear(string y)
{
	year = y;
}

void Ship::setName(string n)
{
	name = n;
}

string Ship:: getName()
{	
	return Ship::name;
}

string Ship::getYear()
{
	return year;
}


class CruiseShip : public Ship
{
protected:
	int passengers;

public:
	CruiseShip(int p, string n, string y);
	int getPassengers();
	virtual void print();
	void setPassengers(int p);
};

CruiseShip::CruiseShip(int p, string n, string y) : Ship(n, y)
{
	passengers = p;
	name = n;
	year = y;
}

int CruiseShip::getPassengers()
{
	return passengers;
}

void CruiseShip::setPassengers(int p)
{
	passengers = p;
}

void CruiseShip::print()
{
	cout << name << " has a limit of " << passengers << " passengers." << endl;
}

class CargoShip : public Ship
{
protected:
	int capacity;

public:
	CargoShip(int c, string n, string y);
	int getCapacity();
	virtual void print();
	void setCapacity(int c);
};

CargoShip::CargoShip(int c, string n, string y) : Ship(n, y)
	{
		capacity = c;
		name = n;
		year = y;
	}

int CargoShip::getCapacity()
{
	return capacity;
}

void CargoShip::setCapacity(int c)
{
	capacity = c;
}
void CargoShip::print()
	{
		cout << name << " has a cargo capacity of " << capacity << " tons." << endl;
	}

int main()
{
	Ship* ships[3] = { new Ship("SuperBoat", "2000"), new CruiseShip(256, "AwesomeBoat", "2001"), new CargoShip(1000, "CoolBoat", "2003")};
	
	for (int i = 0; i < 3; i++)
	{
		ships[i]->print();
	}

	return 0;
}