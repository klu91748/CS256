// p2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include <cstdio>

using namespace std;

class BankAccount
{
protected:
	double balance = 0;
	int deposits = 0;
	int withdrawals = 0;
	double annualInterestRate = 0;
	int monthlyServiceCharges = 0;

public:
	BankAccount(double b, double AIR)
	{
		balance = b;
		annualInterestRate = AIR;
	}

	virtual void deposit(double d)
	{
		balance = balance + d;
		deposits++;
	}

	virtual void withdraw(double d)
	{
		balance = balance - d;
		withdrawals++;
	}

	virtual void calcInt()
	{
		double monthlyInterestRate = annualInterestRate / 12;
		double monthlyInterest = balance * monthlyInterestRate;
		balance = balance + monthlyInterest;
	}

	virtual void monthlyProc()
	{
		balance = balance - monthlyServiceCharges;
		calcInt();
		withdrawals = 0;
		deposits = 0;
		monthlyServiceCharges = 0;
	}

	virtual double getBalance()
	{
		return balance;
	}

	virtual double getTotalDeposits()
	{
		return deposits;
	}

	virtual double getTotalWithdrawals()
	{
		return withdrawals;
	}

	virtual double getServiceCharges()
	{
		return monthlyServiceCharges;
	}
};

class SavingsAccount : public BankAccount
{
private:
	bool status;

public:
	SavingsAccount(double d, double AIR) : BankAccount(d, AIR)
	{
		balance = d;
		annualInterestRate = AIR;

		if (balance >= 25)
		{
			status = true;
		}
		else
		{
			status = false;
		}
	}

	void withdraw(double d)
	{
		if (status == false)
		{
			cout << "Balance is under $25. Account is inactive. Please achieve a balance over $25." << endl;
		}
		else
		{
			BankAccount::withdraw(d);
		}

		if (balance < 25)
		{
			status = false;
		}
	}

	void deposit(double d)
	{
		BankAccount::deposit(d);
		if (status == false && balance >= 25)
		{
			status = true;
		}
	}

	void monthlyProc()
	{
		if (withdrawals > 4)
		{
			monthlyServiceCharges++;
		}
	}

};

class CheckingAccount : public BankAccount
{
public:
	CheckingAccount(double d, double AIR) : BankAccount(d, AIR)
	{
		balance = d;
		annualInterestRate = AIR;
	}

	void withdraw(double d)
	{
		double check = balance - d;
		if (check < 0)
		{
			balance = balance - 15;
		}
		else
		{
			BankAccount::withdraw(d);
		}
	}

	void monthlyProc()
	{
		monthlyServiceCharges = monthlyServiceCharges + 5 + (.1*withdrawals);
		BankAccount::monthlyProc();
	}
};

void check(CheckingAccount checkings)
{
	int begBalance = checkings.getBalance();
	int choice = 1;
	while (choice != 4)
	{
		cout << "Checkings Account: " << endl;
		cout << "Enter 1 to deposit." << endl;
		cout << "Enter 2 to withdraw." << endl;
		cout << "Enter 3 to view stats." << endl;
		cout << "Enter 4 to exit." << endl;

		cin >> choice;

		if (choice == 1)
		{
			cout << "Enter deposit amount: " << endl;
			int dep;
			cin >> dep;
			checkings.deposit(dep);
		}

		else if (choice == 2)
		{
			cout << "Enter withdraw amount: " << endl;
			int wit;
			cin >> wit;
			checkings.withdraw(wit);
		}

		else if (choice == 3)
		{
			cout << "Balance: " << begBalance << endl;
			cout << "Total amount of deposits: " << checkings.getTotalDeposits() << endl;
			cout << "Total amount of withdraws: " << checkings.getTotalWithdrawals() << endl;
			cout << "Service charges: " << checkings.getServiceCharges() << endl;
			checkings.monthlyProc();
			cout << "Ending Balance: " << checkings.getBalance() << endl;
		}

		else if (choice == 4)
		{
			choice = 4;
		}
	}
}

void saving(SavingsAccount savings)
{
	int begBalance = savings.getBalance();
	int choice = 1;
	while (choice != 4)
	{
		cout << "Savings Account: " << endl;
		cout << "Enter 1 to deposit." << endl;
		cout << "Enter 2 to withdraw." << endl;
		cout << "Enter 3 to view stats." << endl;
		cout << "Enter 4 to exit." << endl;

		cin >> choice;

		if (choice == 1)
		{
			cout << "Enter deposit amount: " << endl;
			int dep;
			cin >> dep;
			savings.deposit(dep);
		}

		else if (choice == 2)
		{
			cout << "Enter withdraw amount: " << endl;
			int wit;
			cin >> wit;
			savings.withdraw(wit);
		}

		else if (choice == 3)
		{
			cout << "Balance: " << begBalance << endl;
			cout << "Total amount of deposits: " << savings.getTotalDeposits() << endl;
			cout << "Total amount of withdraws: " << savings.getTotalWithdrawals() << endl;
			cout << "Service charges: " << savings.getServiceCharges() << endl;
			savings.monthlyProc();
			cout << "Ending Balance: " << savings.getBalance() << endl;
		}

		else if (choice == 4)
		{
			choice = 4;
		}
	}
}

int main()
{
	CheckingAccount checkings(125, .01);
	SavingsAccount savings(125, .01);

	int choice = 0;

	while (choice != 4)
	{
		cout << "Press 1 to enter checkings account." << endl;
		cout << "Press 2 to enter savings account." << endl;
		cout << "Press 3 to exit." << endl;
		cin >> choice;

		if (choice == 1)
			check(checkings);
		else if (choice == 2)
			saving(savings);
		else if (choice == 3)
			return 0;

	}

}

