// KevinMidtermHelp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <string>
#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

class Child;
class Parent;

class Human
{
	friend class Parent;
	friend class Child;
private:
	string name;
	int age;
	char sex;
	string works;
	Human() {}

protected:
	Human(string n, int i, char s, string w)
	{
		name = n;
		age = i;
		sex = s;
		works = w;
	}

public:
	void setName(string s) { name = s; }
	void setAge(int i) { age = i; }
	void setSex(char s) { sex = s; }
	string getName() { return name; }
	int getAge() { return age; }
	char getSex() { return sex; }
	string getWork() { return works; }
	void setWork(string s) { works = s; }
	void virtual work(string w) { works = w; };
};

class Parent : public Human
{
	friend class Human;
	friend class Child;
private:
	vector<Child> children;

public:
	Parent() : Human() {}
	Parent(string n, int i, char c, string w) : Human(n, i, c, w) {}

	void setChildren(vector<Child> c) { children = c; }
	vector<Child> getChildren() { return children; }

	void changeChildsName(Child &child, string n);
};

class Child : public Human
{
	friend class Parent;
	friend class Human;
private:
	Parent Mom;
	Parent Dad;
	Child();

public:
	friend Parent;
	Child(Parent m, Parent d)
	{
		Mom = m;
		Dad = d;
	}

};

void Parent::changeChildsName(Child &child, string n)
{
	child.setName(n);
}


int main()
{
	Parent homer("Homer", 36, 'M', "Safety inspector");
	Parent march("March", 34, 'F', "HouseWife");

	Child lisa(homer, march);
	Child bart(homer, march);
	Child maggie(homer, march);

	homer.changeChildsName(lisa, "Lisa");
	lisa.setAge(12);
	lisa.setSex('F');
	lisa.setWork("Students");

	homer.changeChildsName(bart, "Bart");
	bart.setAge(10);
	bart.setSex('M');
	bart.setWork("Student");

	march.changeChildsName(maggie, "Maggie");
	maggie.setAge(3);
	maggie.setSex('F');
	maggie.setWork("Play");

	cout << "Name: " << homer.getName() << endl;
	cout << "Age: " << homer.getAge() << endl;
	cout << "Sex: " << homer.getSex() << endl;
	cout << "Work: " << homer.getWork() << endl;

	cout << "Name: " << lisa.getName() << endl;
	cout << "Age: " << lisa.getAge() << endl;
	cout << "Sex: " << lisa.getSex() << endl;
	cout << "Work: " << lisa.getWork() << endl;

	cout << "Name: " << maggie.getName() << endl;
	cout << "Age: " << maggie.getAge() << endl;
	cout << "Sex: " << maggie.getSex() << endl;
	cout << "Work: " << maggie.getWork() << endl;


	return 0;
}