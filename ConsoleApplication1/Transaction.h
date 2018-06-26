#include "media.h"
#pragma once

class Transaction
{
public:
	Transaction(char type = 'S', char payment = 'S', float amount = 0, Media *mptr = NULL) //Default Constructor
	{
		this->type = type;
		this->payment = payment;
		this->amount = amount;
		this->mptr = mptr;

		switch (type)
		{
		case 'S':
			this->mptr->ChangeAvailable('S');
			break;
		case 'R':
			this->mptr->ChangeAvailable('A');
			break;
		default:
			break;
		}

		count++;
		trans_id = count;
	}

	void print() const //prints transaction
	{
		cout << "Transaction ID: " << trans_id << endl
			<< "Type: " << type << endl
			<< "Payment: ";
		switch (payment)
		{
		case 'S':
			cout << "Cash\n";
			break;
		case 'C':
			cout << "Credit Card\n";
			break;
		default:
			cout << "Invalid Transaction\n";
			break;
		}
		cout << "Amount: " << amount << endl;

		mptr->print();
	}

	Media* getMPTR() { return mptr; } //return mpts
private:
	int trans_id;
	char type;      // ‘S’: sale, ‘R’: return. ‘P’: replace..etc.
	char payment; // method of payment. ‘C’: credit card. ‘S’: cash
	float amount;   // 
	Media * mptr;
	static int count;// pointer to the media item involved in the transaction
};
int Transaction::count = 0;