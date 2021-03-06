// Employee.cpp : Defines the entry point for the console applicatizon.
//

#include "stdafx.h"
#include<string>
#include<cstdio>
#include<iostream>
using namespace std;

class Employee 
{
private:
	string name;
	int number;
	string hireDate;

public:
	Employee(string n, int i, string h)
	{
		name = n;
		number = i;
		hireDate = h;
	}
	string getName() { return name; }
	int getNumber() { return number; }
	string getHireDate() { return hireDate; }
	void setName(string s) { name = s; }
	void setNumber(int n) 
	{
		if (n > 9999 || n < 0)
		{
			string InvalidEmployeeNumber = "Invalid Employee Number.";
			throw InvalidEmployeeNumber;
		}
		else
		number = n; 
	}
	void setHireDate(string s) { hireDate = s; }

};

class ProductionWorker : public Employee
{
private:
	int shift;
	double payRate;

public:
	ProductionWorker(string a, int b, string c, int d, double e) : Employee(a, b, c)
	{
		shift = d;
		payRate = e;
	}
	int getShift() { return shift; }
	double getPayRate() { return payRate; }
	void setShift(int i)
	{ 
		if (i > 2 || i < 0)
		{
			string InvalidShift = "Invalid Shift.";
			throw InvalidShift;
		}
		else
			shift = i; 
	}
	void setPayRate(double d)
	{ 
		if (d < 0)
		{
			string InvalidPayRate = "Invalid Payrate.";
			throw InvalidPayRate;
		}
		else;
			payRate = d; 
	}
};

int main()
{
	ProductionWorker emp("Kevin", 100, "10/5/2015", 1, 20);
	try
	{
		emp.setNumber(1000000);
	}
	catch (string s)
	{
		cout << s;
	}

	try
	{
		emp.setShift(20);
	}
	catch (string s)
	{
		cout << s;
	}

	try
	{
		emp.setPayRate(-11);
	}
	catch (string s)
	{
		cout << s;
	}
    return 0;
}

