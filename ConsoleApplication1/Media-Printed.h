#include "media.h"
#pragma once

class Printed : public Media
{
public:
	Printed(string p = "none", char status = 'A', int barCode = 1, int no_of_pages = 0, int date_of_print = 0)
		:Media(p, status, barCode) //Default Constructor
	{
		this->no_of_pages = no_of_pages;
		this->date_of_print = date_of_print;

		print_items++;
	}

	Printed(const Printed &a) //Copy Constructor
		:Media(a)
	{
		this->no_of_pages = a.no_of_pages;
		this->date_of_print = a.date_of_print;

		print_items++;
	}

	~Printed() //Destructor
	{
		print_items--;
	}

	Printed & operator=(const Printed &a) //Overloaded Operator =
	{
		Media::operator=(a);

		this->no_of_pages = a.no_of_pages;
		this->date_of_print = a.date_of_print;
		mt = a.mt;

		return *this;
	}

	int getBarCode() //returns barcode
	{
		return barCode;
	}

	int get_no_of_pages() { return no_of_pages; }
	int get_date_of_print() { return date_of_print; }

	virtual void print() //print function
	{
		Media::print();
		cout << "Pages: " << no_of_pages << endl
			<< "Date of Print: " << date_of_print << endl;

	}
	virtual void Output(ofstream &output) //Outputs items to stock.txt
	{
		Media::Output(output);
		output << no_of_pages << "," << date_of_print << ",";
	}
	virtual MediaType getMediaType() { return mt; }
	virtual int getItems() { return print_items; }
	virtual int getMediaID() { return mediaID; }
	virtual char getStatus() { return status; }
protected:
	int no_of_pages;
	int date_of_print;
	static int print_items;
};

int Printed::print_items = 0;