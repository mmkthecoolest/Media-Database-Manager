#include "Transaction.h"
#pragma once

class SaleTranxs
{
public:
	SaleTranxs()//Default Constructor
	{
		ptrans = new Transaction*[0];
		count = 0;
	}

	~SaleTranxs()
	{
		for (int i = 0; i < count; i++)
		{
			delete ptrans[i];
		}

		delete[] ptrans;
	}

	SaleTranxs &operator+= (const Transaction& a)//Overloaded Operator += to add a new transaction
	{
		Transaction** next = new Transaction*[count + 1];
		for (int i = 0; i < count; i++)
		{
			next[i] = new Transaction(*ptrans[i]);
		}
		next[count] = new Transaction(a);

		for (int i = 0; i < count; i++)
		{
			delete ptrans[i];
		}

		delete[] ptrans;

		ptrans = next;
		count++;

		return *this;

	}

	void TransactionBuy(const StockTab &a)//Transaction Buy function to buy an item
	{
		char payment;
		float amount;
		int mediaID;

		cout << "Items available:\n\n";
		printAvailableStock(a);//prints stock
		
		cout << "\n\nChoose method of payment (C for credit card, S for cash): ";
		cin >> payment;//payment method
		payment = toupper(payment);
		if (payment != 'S' && payment != 'C')
			return;
		cout << "Enter amount to be paid: ";
		cin >> amount;
		cout << "Input media ID for item: ";
		cin >> mediaID;

		Media* ptr = NULL;//initializes media ptr as a NULL pointer to check for the user's input

		for (int i = 0; i < a.getitemCount(); i++)
		{
			if (mediaID == a.getMPTR(i)->getMediaID())
			{
				ptr = a.getMPTR(i);
				break;
			}
		}

		for (int i = 0; i < count; i++)
		{
			if (mediaID == ptrans[i]->getMPTR()->getMediaID())
			{
				ptr = ptrans[i]->getMPTR();
				break;
			}
		}

		if (ptr == NULL)
		{
			cout << "Media Item not found...\n";
			return;
		}

		*this += Transaction('S', payment, amount, ptr);
	}

	void TransactionReturn()//Transaction Return function to return an item
	{
		Media *ptr;
		char payment;
		float amount;
		string title, publisher_name, author, city, actor;
		int barCode, option, no_of_pages, date_of_print, issn, volume, prod_yr;

		cout << "Choose method of payment (C for credit card, S for cash): ";
		cin >> payment;
		cout << "Enter amount to be paid: ";
		cin >> amount;

		cout << "Enter title of media: ";
		cin.ignore();
		getline(cin, title);
		cout << "Enter barcode: ";
		cin >> barCode;

		cout << "Enter Media Type:\n"
			<< "1-Magazine\n"
			<< "2-Book\n"
			<< "3-Newspaper\n"
			<< "4-Film\n"
			<< "Input: ";
		cin >> option;

		if (option <= 3 && option >= 1)
		{
			cout << "Input number of pages: ";
			cin >> no_of_pages;
			cout << "Input year of print: ";
			cin >> date_of_print;

			if (option == 1)
			{
				cout << "Input ISSN: ";
				cin >> issn;
				cout << "Input publisher name: ";
				cin.ignore();
				getline(cin, publisher_name);
				cout << "Input volume: ";
				cin >> volume;

				ptr = new Magazine(title, 'A', barCode, no_of_pages, date_of_print, issn, publisher_name, volume);
			}

			else if (option == 2)
			{
				cout << "Input author: ";
				cin.ignore();
				getline(cin, author);
				cout << "Input publisher name: ";
				cin.ignore();
				getline(cin, publisher_name);
				cout << "Input ISBN: ";
				cin >> issn;

				ptr = new Book(title, 'A', barCode, no_of_pages, date_of_print, author, publisher_name, issn);
			}

			else if (option == 3)
			{
				cout << "Input city: ";
				cin.ignore();
				getline(cin, city);
				cout << "Input volume: ";
				cin >> volume;

				ptr = new Newspaper(title, 'A', barCode, no_of_pages, date_of_print, city, volume);
			}
		}

		else if (option == 4)
		{
			cout << "Input leading actor: ";
			cin.ignore();
			getline(cin, actor);
			cout << "Input production year: ";
			cin >> prod_yr;

			ptr = new Film(title, 'A', barCode, actor, prod_yr);
		}

		*this += Transaction('R', payment, amount, ptr);
	}

	void TransactionReplace(const StockTab &a)//Transaction Replace function to replace an item
	{
		TransactionBuy(a);
		TransactionReturn();
	}
	
	void print() const//prints Transaction report
	{
		if (count == 0)
			return;
		
		cout << "TRANSACTION REPORT:\n\n";
		
		for (int i = 0; i < count; i++)
		{
			ptrans[i]->print();
		}
	}

	void printSoldStock() const//prints sold stocks
	{
		if (count == 0)
			return;
		
		cout << "SOLD STOCK REPORT:\n\n";
		for (int i = 0; i < count; i++)
			if (ptrans[i]->getMPTR()->getStatus() == 'S')
				ptrans[i]->getMPTR()->print();
	}

	void printAvailableStock(const StockTab &a) const//prints available stock
	{
		if (count == 0 && a.getAvailableCount() == 0)
			return;
		
		a.printAvailableStock();
		for (int i = 0; i < count; i++)
			if (ptrans[i]->getMPTR()->getStatus() == 'A')
				ptrans[i]->getMPTR()->print();
	}

	int getAvailableCount(const StockTab &a)//returns available items
	{
		int x = a.getAvailableCount();
		for (int i = 0; i < count; i++)
			if (ptrans[i]->getMPTR()->getStatus() == 'A')
				x++;

		return x;
	}

	int getCount() const { return count; }//returns item count

	void Output(ofstream &output, const StockTab &a)//Outputs items to stock.txt
	{
		output << getAvailableCount(a) << endl;
		for (int i = 0; i < a.getitemCount(); i++)
			if (a.getMPTR(i)->getStatus() == 'A')
				a.getMPTR(i)->Output(output);
		
		for (int i = 0; i < count; i++)
		{
			if(ptrans[i]->getMPTR()->getStatus() == 'A')
				ptrans[i]->getMPTR()->Output(output);
		}
	}
private:
	Transaction  **ptrans;
	int count;
};