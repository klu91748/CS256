#pragma once
// BigNumbersLibrary.cpp : Defines the exported functions for the DLL application.
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
	vector<int> remainder;
	int digits = 0;

public:
	Vectors();
	Vectors(string str);
	void setDigits(int i);
	int getDigits();
	vector<int> getVector();
	vector<int> getRemainder();
	void setVector(vector<int> r);
	void setRemainder(vector<int> r);
	void print();
	Vectors operator+(Vectors&);
	Vectors operator-(Vectors&);
	Vectors operator*(Vectors&);
	Vectors operator/(Vectors&);
	Vectors operator%(Vectors&);
	vector<int> compareTo(Vectors&);
};

Vectors::Vectors() {}
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

		vect.push_back(c[i] - 48);
		digits++;
	}
}

void Vectors::setVector(vector<int> r) { vect = r; }
void Vectors::setRemainder(vector<int> r) { remainder = r; }
int Vectors::getDigits() { return digits; }
void Vectors::setDigits(int i) { digits = i; }
vector<int> Vectors::getVector() { return vect; }
vector<int> Vectors::getRemainder() { return remainder; }


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


Vectors Vectors::operator+(Vectors& obj)
{
	int largest;
	if (this->getDigits() >= obj.getDigits())
		largest = this->getDigits() + 1;
	else
		largest = obj.getDigits() + 1;

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
			total[j] = temp1[j] + temp2[j] + carry;
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
		for (int i = largest - 1; i >= 0; i--)
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
	for (int i = largest - 1; i >= 0; i--)	//subtract
	{
		if (i == 0)
		{
			if (temp1IsGreater && temp1[0] == -2)
				total[0] = -2;
			if (temp1IsGreater && temp1[0] == -3)
				total[0] = -3;
			if (!temp1IsGreater && temp1[0] == -2)
				total[0] = -3;
			if (!temp1IsGreater && temp1[0] == -3)
				total[0] = -2;
		}
		else if (temp1[i] - temp2[i] < 0)	//borrow
		{
			int t = i;
			t--;
			while (temp1[t] == 0)
				t--;

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
		cap = this->getDigits() + 2;
	else
		cap = obj.getDigits() + 2;

	vector<int> temp1(cap);
	vector<int> temp2(cap);
	vector<int> temp3(largest);
	vector<int> temp4(largest);
	vect.resize(largest);
	int thisDig = this->getDigits();
	int nextDig = obj.getDigits();

	vector<int> value = this->compareTo(obj);
	for (int i = cap; i >= 0; i--)
	{
		if (this->getVector() == value)
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
		if (obj.getVector() == value)
		{
			if (i == 0)
			{
				temp1[i] = obj.getVector()[0];
				temp2[i] = this->getVector()[0];
			}
			else
			{
				if (nextDig > 0)
					temp1[i - 1] = obj.getVector()[nextDig];
				else
					temp1[i - 1] = 0;
				if (thisDig > 0)
					temp2[i - 1] = this->getVector()[thisDig];
				else
					temp2[i - 1] = 0;
			}
			thisDig--;
			nextDig--;
		}
	}
	//clear this vect
	for (int i = 0; i < largest - 1; i++)
		temp4[i] = 0;

	int carry = 0;
	int rotate = 0;
	int dec = 0;
	int t = 0;
	for (int i = cap - 1; i > 0; i--)	//i = bottom row
	{
		int dec = 0;
		for (int j = cap - 1; j > 0; j--)	// j = top row
		{

			if (temp1[j] * temp2[i] > 9)
			{
				stringstream tmp;

				tmp << temp1[j] * temp2[i] + carry;
				temp3[largest - rotate - 1 - dec] = (tmp.str())[1] - 48;
				tmp << temp1[j] * temp2[i];
				carry = (tmp.str())[0] - 48;
			}
			else
			{
				temp3[largest - 1 - dec] = temp1[j] * temp2[i] + carry;
				carry = 0;
			}
			dec += 1;
		}

		//shift
		vector<int> temp5(temp3.size());
		int w = 0;
		if (t > 0)
		{
			for (int q = temp5.size() - 1; q > 0; q--) //place 0s
			{
				if (t != w)
				{
					temp5[q] = 0;
					w++;
				}
			}
			for (int q = temp5.size() - 1; q > 0; q--)
			{
				if (q - t > 0)
					temp5[q - t] = temp3[q];
			}
		}
		else
		{
			for (int q = temp5.size() - 1; q > 0; q--)
				temp5[q] = temp3[q];
		}
		temp3 = temp5;
		t++;

		int carry1 = 0;
		for (int j = largest - 1; j > 0; j--)	//add
		{
			if (temp4[j] + temp3[j] > 9)
			{
				temp4[j] = temp4[j] + temp3[j] - 10 + carry1;
				carry1 = 1;
			}
			else if (j == 0)
				temp4[0] = -2;
			else
			{
				temp4[j] = temp4[j] + temp3[j] + carry1;
				carry1 = 0;
			}
		}
		for (int i = 0; i < largest; i++)
			temp3[i] = 0;
	}

	Vectors r;

	int k = 1;
	while (temp4[k] == 0 && k != temp4.size() - 1)	//remove front zeroes
		k++;
	vector<int>temp6(temp4.size() - k + 1);
	int e = 1;
	while (e != temp6.size())
	{
		temp6[e] = temp4[k];
		e++;
		k++;
	}
	r.setVector(temp6);
	r.setDigits(e - 1);

	return r;
}

Vectors Vectors::operator/(Vectors& obj)
{
	int largest;

	if (this->getDigits() >= obj.getDigits())
		largest = this->getDigits() + 1;
	else
		largest = obj.getDigits() + 1;

	vector<int> temp1(largest);
	vector<int> temp3(largest);

	Vectors dividend;
	dividend.setVector(this->getVector());
	dividend.setDigits(this->getVector().size() - 1);
	Vectors divisor;
	divisor.setVector(obj.getVector());
	divisor.setDigits(obj.getVector().size() - 1);
	Vectors quotient;
	quotient.setVector(temp1);
	quotient.setDigits(temp1.size() - 1);
	Vectors total;
	total = divisor * quotient;

	int digits = divisor.getDigits();

	int l = largest;
	int num = 0;
	int carry1 = 0;
	temp3[largest - 1] = 1;

	while (total.compareTo(dividend) != total.getVector())
	{
		num++;

		carry1 = 0;
		for (int j = largest - 1; j > 0; j--)	//add
		{
			if (temp1[j] + temp3[j] > 9)
			{
				temp1[j] = temp1[j] + temp3[j] - 10 + carry1;
				carry1 = 1;
			}
			else if (j == 0)
				temp1[0] = -2;
			else
			{
				temp1[j] = temp1[j] + temp3[j] + carry1;
				carry1 = 0;
			}
		}
		quotient.setVector(temp1);
		total = divisor * quotient;
	}
	Vectors p;
	p.setVector(temp3);
	p.setDigits(largest - 1);
	Vectors r = quotient - p;
	r.setDigits(largest - 1);

	Vectors q;
	q.setVector(dividend.getVector());
	q.setDigits(dividend.getDigits());
	Vectors o;
	o.setVector(total.getVector());
	o.setDigits(total.getDigits());
	Vectors w;

	bool flag = false;
	int t = 1;
	while (divisor.getVector()[t] == 0 && t != divisor.getVector().size() - 1)
	{
		if (divisor.getVector()[t] != 0)
		{
			flag = false;
			break;
		}
		if (divisor.getVector()[t + 1] == 0)
		{
			flag = true;
			break;
		}
		t++;
	}

	if (!flag)
	{
		w = divisor * r;
		w = q - w;
	}
	if (flag)
	{
		vector<int> a(digits + 1);
		for (int i = 1; i <= digits; i++)
		{
			a[i] = divisor.getVector()[i];
		}
		w.setVector(a);
	}

	r.setRemainder(w.getVector());
	return r;
}

Vectors Vectors::operator%(Vectors& obj)
{
	Vectors q;
	q.setVector(this->getVector());
	q.setDigits(this->getDigits());
	Vectors o;
	o.setVector(obj.getVector());
	o.setDigits(obj.getDigits());
	Vectors w;
	int p = 1;
	bool flag = false;
	vector<int> value = q.compareTo(o);
	while (q.getVector()[p] == o.getVector()[p] && p != value.size() - 1)
	{

		if (q.getVector()[p] == o.getVector()[p])
			flag = true;
		else
		{
			flag = false;
			break;
		}
		p++;
	}

	if (flag || obj.getVector()[obj.getVector().size() - 1] == 1)
	{
		vector<int> v(2);
		v[1] = 0;
		w.setVector(v);
		return w;
	}

	w = o / q;

	w.setVector(w.getRemainder());

	return w;
}

vector<int> Vectors::compareTo(Vectors& obj)
{

	if (this->getVector().size() > obj.getVector().size())
		return this->getVector();
	if (this->getVector().size() < obj.getVector().size())
		return obj.getVector();

	if (this->getVector().size() > obj.getVector().size())
		return obj.getVector();
	if (this->getVector().size() < obj.getVector().size())
		return this->getVector();

	int i = 2;
	while (this->getVector()[i - 1] == obj.getVector()[i - 1])
	{
		if (this->getVector().size() == i)
		{
			return this->getVector();
		}
		i++;
	}
	if (this->getVector()[i - 1] >= obj.getVector()[i - 1])
		return this->getVector();
	else
		return obj.getVector();

}


