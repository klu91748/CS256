// problem8.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <cstdio>
#include <iostream>
using namespace std;

class PersonData
{
private:
	string lastName;
	string firstName;
	string address;
	string city;
	string state;
	string zip;
	string phone;

public:
	void setLastName(string l) { lastName = l; }
	void setFirstName(string l) { firstName = l; }
	void setAddress(string l) { address = l; }
	void setCity(string l) { city = l; }
	void setState(string l) { state = l; }
	void setZip(string l) { zip = l; }
	void setPhone(string l) { phone = l; }
	
	string getLastName() { return lastName; }
	string getFirstName() { return firstName; }
	string getAddress() { return address; }
	string getCity() { return city; }
	string getState() { return state; }
	string getZip() { return zip; }
	string getPhone() { return phone; }


};

class CustomerData : public PersonData
{
private:
	int customerNumber;
	bool mailingList = false;

public:
	void setCustomerNumber(int i) { customerNumber = i; }
	void setMailingList(bool b) { mailingList = b; }

	int getCustomerNumber() { return customerNumber; }
	void getMailingList() 
	{
		if (mailingList == false)
		{
			cout << "Not on mailing list!" << endl;
		}

		if (mailingList == true)
		{
			cout << "On mailing list!" << endl;
		}
	}
};

class PreferredCustomer : public CustomerData
{
private:
	double purchasesAmount;
	double discountLevel;

public:
	void setPurchasesAmount(double d) { purchasesAmount = d; }
	void setDiscountLevel() 
	{ 
		if (purchasesAmount <= 500)
		{
			discountLevel = .05;
			cout << "Discount is 5%." << endl;
		}

		else if (purchasesAmount >= 500 && purchasesAmount <= 1000)
		{
			discountLevel = .06;
			cout << "Discount is 6%." << endl;
		}
		else if (purchasesAmount >= 1000 && purchasesAmount <= 1500)
		{
			discountLevel = .07;
			cout << "Discount is 7%." << endl;
		}
		else if (purchasesAmount >= 2000)
		{
			discountLevel = .1;
			cout << "Discount is 10%." << endl;
		}
		else
		{
			cout << "Error! PurchasesAmount is a negative number." << endl;
		}
	}

	double getPurchasesAmount() { return purchasesAmount; }
	double getDiscountLevel() { return discountLevel; }
};

int main()
{
	PreferredCustomer pf;

	pf.setFirstName("Bob");
	pf.setLastName("Jones");
	pf.setAddress("1000 E Ave");
	pf.setCity("Pomona");
	pf.setState("California");
	pf.setZip("91043");
	pf.setPhone("(626) 554 - 4343");
	pf.setCustomerNumber(132143);
	pf.setMailingList("true");
	pf.setPurchasesAmount(655);

	cout << "Name: " << pf.getFirstName() << " " << pf.getLastName() << endl;
	cout << "Address: " << pf.getAddress() << " ," << pf.getCity() << " ," << pf.getState() <<
		" ," << pf.getZip() << endl;
	cout << "Phone: " << pf.getPhone() << endl;
	cout << "Customer Number: " << pf.getCustomerNumber() << endl;
	pf.getMailingList();
	pf.setDiscountLevel();

    return 0;
}

