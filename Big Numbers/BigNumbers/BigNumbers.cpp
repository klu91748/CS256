// BigNumbers.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <string>
#include <iostream>
#include <cstdio>
#include <sstream>
using namespace std;





class Vectors
{
private:
	vector<int> vect;
	int digits = 0;
	//Vectors createVector(int length);
public:
	Vectors(string str);
	void setDigits(int i);
	int getDigits();
	vector<int> getVector();
	void print();
	Vectors operator+(Vectors&);
	Vectors operator-(Vectors&);
	Vectors operator*(Vectors&);
	Vectors operator/(Vectors&);
	vector<int> compareTo(Vectors&);
};

Vectors::Vectors(string str)
{
	vector<char> v;
	int length = str.length();

	char c[10000];
	strcpy_s(c, str.c_str());

	
	for (int i = 0; i < length; i++)
	{
		if (c[0] != '-' && i == 0)
		{
			vect.push_back(-2);
			digits = 0;
		}
		else if (c[0] == '-' && i == 0)
			digits--;

		vect.push_back(c[i]-48);
		digits++;
	}
}

int Vectors::getDigits() { return digits; }
void Vectors::setDigits(int i) { digits = i; }
vector<int> Vectors::getVector() { return vect; }

void Vectors::print()
{
	//-2 = positve
	//-3 = negative
	int p = this->getVector().size();
	for (int i = 0; i < p; i++)
	{
		if (i == 0 && this->getVector()[i] == -2)
			cout << "";
		else if (i == 0 && this->getVector()[i] == -3)
			cout << "-";		
		else
		cout << this->getVector()[i];
	}
	cout << endl;

}

//Vectors Vectors::createVector(int length)
//{
//	//return new *Vectors("f");
//}


Vectors Vectors::operator+(Vectors& obj)
{
	int largest;
	if (this->getDigits() >= obj.getDigits())
		largest = this->getDigits()+2;
	else
		largest = obj.getDigits()+2;

	vector<int> total(largest);
	vector<int> temp1(largest);
	vector<int> temp2(largest);

	int thisDig = this->getDigits();
	int nextDig = obj.getDigits();

	for (int i = largest; i >= 0; i--)
	{
		if (i == 0)
		{
			temp1[i] = this->getVector()[0];
			temp2[i] = obj.getVector()[0];
		}
		else
		{
			if (thisDig > 0)
				temp1[i-1] = this->getVector()[thisDig];
			else
				temp1[i-1] = 0;
			if (nextDig > 0)
				temp2[i-1] = obj.getVector()[nextDig];
			else
				temp2[i-1] = 0;
		}
		thisDig--;
		nextDig--;
	}
	int carry = 0;

	for (int j = largest - 1; j >= 0; j--)
	{
		if (temp1[j] + temp2[j] > 9)
		{
			total[j] = temp1[j] + temp2[j] - 10 + carry;
			carry = 1;
		}
		else if (j == 0)
		{
			if (temp1[0] == -3 && temp2[0] == -3)
				total[j] = -3;
			else
				total[j] = -2;
		}
		else
		{
			total[j] = temp1[j] + temp2[j]+ carry;
			carry = 0;
		}
	}
	vect = total;
	this->setDigits(largest);

	return *this;
}

Vectors Vectors::operator-(Vectors& obj)
{
	int largest;
	if (this->getDigits() >= obj.getDigits())
		largest = this->getDigits() + 1;
	else
		largest = obj.getDigits() + 1;

	vector<int> total(largest);
	vector<int> temp1(largest);
	vector<int> temp2(largest);
	vector<int> value = this->compareTo(obj);
	int thisDig = this->getDigits();
	int nextDig = obj.getDigits();
	bool temp1IsGreater = false;

	if (this->getVector() == value) //temp1 holds highest digit value and put in placeholder 0's
	{
		temp1 = value;
		for (int i = largest-1; i >= 0; i--)
		{
			if (nextDig > 0)
				temp2[i] = obj.getVector()[nextDig];
			else if (nextDig == 0)
				temp2[0] = obj.getVector()[0];
			else
				if (i > 1)
					temp2[i] = 0;
			nextDig--;
		}
		temp1IsGreater = true;

	}

	else
	{
		temp1 = obj.getVector();
		for (int i = largest - 1; i >= 0; i--)
		{
			if (thisDig > 0)
				temp2[i] = this->getVector()[thisDig];
			else if (thisDig == 0)
				temp2[0] = this->getVector()[0];
			else
				if (i > 1)
					temp2[i] = 0;
			thisDig--;
		}
		temp1IsGreater = false;
	}

	for (int i = largest-1; i >= 0; i--)	//subtract
	{

		if (i == 0)
		{
			if (temp1IsGreater && temp1[0] == -2)
			{
				total[0] = -2;
			}
			if (temp1IsGreater && temp1[0] == -3)
			{
				total[0] = -3;
			}
			if (!temp1IsGreater && temp1[0] == -2)
			{
				total[0] = -3;
				cout << "goes into negative";
			}
			if (!temp1IsGreater && temp1[0] == -3)
			{
				total[0] = -2;
			}

		}
		else if (temp1[i] - temp2[i] < 0)	//borrow
		{
			int t = i;
			t--;
			while (temp1[t] == 0)
			{
				t--;
			}

			temp1[t] = temp1[t] - 1;

			t++;
			while (t != i)
			{
				if (temp1[t] == 0)
					temp1[t] = 9;			
				t++;
			}
			total[i] = temp1[i] + 10 - temp2[i];

		}
		else
			total[i] = temp1[i] - temp2[i];	
		
	}


	vect = total;
	this->setDigits(largest);

	return *this;
}

Vectors Vectors::operator*(Vectors& obj)
{
	int largest = this->getDigits() + obj.getDigits() + 1;

	int cap;
	if (this->getDigits() >= obj.getDigits())
		cap = this->getDigits() + 1;
	else
		cap = obj.getDigits() + 1;

	vector<int> temp1(cap);
	vector<int> temp2(cap);
	vector<int> temp3(largest);
	vect.resize(largest);
	int thisDig = this->getDigits();
	int nextDig = obj.getDigits();

	for (int i = cap; i >= 0; i--)
	{
		if (i == 0)
		{
			temp1[i] = this->getVector()[0];
			temp2[i] = obj.getVector()[0];
		}
		else
		{
			if (thisDig > 0)
				temp1[i - 1] = this->getVector()[thisDig];
			else
				temp1[i - 1] = 0;
			if (nextDig > 0)
				temp2[i - 1] = obj.getVector()[nextDig];
			else
				temp2[i - 1] = 0;
		}
		thisDig--;
		nextDig--;
	}

	//clear this vect
	for (int i = 0; i < largest - 1; i++)
		vect[i] = 0;

	stringstream tmp;

	int carry = 0;
	int rotate = 0;
	for (int i = cap - 1; i > 0; i--)	//i = top row
	{

		int dec = 0;
		for (int j = cap - 1; j >= 0; j--)	// j = bottom row
		{
			if (j == 0)
			{
				if (temp1[0] == -2 && temp2[0] == -2)
					vect[0] = -2;
				if (temp1[0] == -3 && temp2[0] == -3)
					vect[0] = -2;
				else
					vect[0] = -3;
			}
			else if (temp1[j] * temp2[i] > 9)
			{
				tmp << temp1[j] * temp2[i];
				temp3[largest - rotate - 1 - dec] = (tmp.str())[1] - 48 + carry;
				tmp << temp1[j] * temp2[i];
				carry = (tmp.str())[0] - 48;
			}
			else
			{
				temp3[largest - rotate - 1 - dec] = temp1[j] * temp2[i] + carry;
				carry = 0;
			}
			dec += 1;
		}

		rotate += 1;
		for (int j = largest - 1; j > 0; j--)	//add
		{
			if (vect[j] + temp3[j] > 9)
			{
				vect[j] = vect[j] + temp3[j] - 10 + carry;
				carry = 1;
			}
			else if (j == 0)
					vect[0] = -2;
			else
			{
				vect[j] = vect[j] + temp3[j] + carry;
				carry = 0;
			}
		}

		int s = 0;
		while (s != rotate)
		{
			temp3[largest - 1 - s] = 0;
			s++;
		}

	}

	return *this;
}

Vectors Vectors::operator/(Vectors& obj)
{
	int largest = this->getDigits() + obj.getDigits() + 1;

	int cap;
	if (this->getDigits() >= obj.getDigits())
		cap = this->getDigits() + 1;
	else
		cap = obj.getDigits() + 1;

	vector<int> temp1(cap);
	vector<int> temp2(cap);
	vector<int> temp3(largest);
	vector<int> temp4(largest);
	vect.resize(largest);
	int thisDig = this->getDigits();
	int nextDig = obj.getDigits();

	for (int i = cap; i >= 0; i--)
	{
		if (i == 0)
		{
			temp1[i] = this->getVector()[0];
			temp2[i] = obj.getVector()[0];
		}
		else
		{
			if (thisDig > 0)
				temp1[i - 1] = this->getVector()[thisDig];
			else
				temp1[i - 1] = 0;
			if (nextDig > 0)
				temp2[i - 1] = obj.getVector()[nextDig];
			else
				temp2[i - 1] = 0;
		}
		thisDig--;
		nextDig--;
	}




	return *this;
}

vector<int> Vectors::compareTo(Vectors& obj)
{

	if (this->getDigits() > obj.getDigits())
		return this->getVector();
	if (this->getDigits() < obj.getDigits())
		return obj.getVector();
	if (this->getDigits() > obj.getDigits())
		return obj.getVector();
	if (this->getDigits() < obj.getDigits())
		return this->getVector();


	int i = 1;
	while (this->getVector()[i] == obj.getVector()[i])
	{
		if (this->getDigits() == i)
			return this->getVector();
		i++;
	}
	if (this->getVector()[i] >= obj.getVector()[i])
		return this->getVector();
	else
		return obj.getVector();
		
}



int main()
{
	Vectors a("10");
	Vectors b("22");
	Vectors c = a * b;
	

	c.print();



    return 0;
}

