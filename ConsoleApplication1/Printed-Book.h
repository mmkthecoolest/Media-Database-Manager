#include "Media-Printed.h"
#pragma once

class Book : public Printed
{
public:
	Book(string p = "none", char status = 'A', int barCode = 1, int no_of_pages = 0, int date_of_print = 0, string auth = "none", string pub = "none", int isbn = 0)
		:Printed(p, status, barCode, no_of_pages, date_of_print) //Default Constructor
	{
		author = auth;
		publisher = pub;
		this->isbn = isbn;
		bk_items++;
		mt = book;
	}

	Book(const Book &a) //Copy Constructor
		:Printed(a)
	{
		author = a.author;
		publisher = a.publisher;
		isbn = a.isbn;
		bk_items++;
		mt = book;
	}

	~Book() //Destructor
	{
		bk_items--;
	}

	Book & operator=(const Book &a) //Overloaded operator =
	{
		Printed::operator=(a);

		author = a.author;
		publisher = a.publisher;
		isbn = a.isbn;
		mt = a.mt;

		return *this;
	}

	string getAuthor() { return author; }
	string getPublisher() { return publisher; }
	int getISBN() { return isbn; }
	virtual int getItems() { return bk_items; }


	virtual void print() //print function
	{
		cout << "Media Type: Book\n";
		Printed::print();
		cout << "Author: " << author << endl
			<< "Publisher: " << publisher << endl
			<< "ISBN: " << isbn << endl << endl;
	}
	virtual void Output(ofstream &output) //Outputs items to stock.txt
	{
		output << "Book,";
		Printed::Output(output);
		output << author << "," << publisher << "," << isbn << endl;
	}
private:
	string author;
	string publisher;
	int isbn;
	static int bk_items;
};

int Book::bk_items = 0;