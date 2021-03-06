// midterm.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

class Child;
class Human;
class Parent;

class Human
{
private:
	string name;
	int age;
	char sex;
	string work;
	Human();

protected:
	Human(string n, int i, char s, string w)
	{
		name = n;
		age = i;
		sex = s;
		work = w;
	}

public:
	void setName(string s) { name = s; }
	void setAge(int i) { age = i; }
	void setSex(char s) { sex = s; }
	string getName() { return name; }
	int getAge() { return age; }
	char getSex() { return sex; }
	string getWork() { return work; }
	void setWork(string s) { work = s; }
	//void virtual work() {}
};

class Parent : public Human
{
private:
	vector<Child> children;

public:
	Parent(string n, int i, char c, string w) : Human(n, i, c, w) {}

	void setChildren(vector<Child> c) { children = c; }
	vector<Child> getChildren() { return children; }

	void work(string w) { setWork(w); }

	void changeChildsName(Child &child, string n)
	{

	}
};

class Child : public Human
{
private:
	//Parent Mom;
	//Parent Dad;
	Child();

public:
	friend Parent;
	Child(string n, int i, char c, string w) : Human(n, i, c, w) {}
	void work(string w) { setWork(w); }
	//Child(Parent &m, Parent &d) {};
};


int main()
{
	Parent homer("Homer", 36, 'M', "Safety inspector");
	Parent march("March", 34, 'F', "HouseWife");
	
	Child lisa("Lisa", 12, 'F', "Students");
	Child bart("Bart", 10, 'M', "Student");
	Child maggie("Maggie", 3, 'F', "Play");

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

