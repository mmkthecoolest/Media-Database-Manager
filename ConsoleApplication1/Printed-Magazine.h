#include "Media-Printed.h"

#pragma once

class Magazine : public Printed
{
public:
	Magazine(string p = "none", char status = 'A', int barCode = 1, int no_of_pages = 0, int date_of_print = 0, int issn = 0, string pub_name = "none", int vol = 0)
		:Printed(p, status, barCode, no_of_pages, date_of_print) //Default Constructor
	{
		this->issn = issn;
		publisher_name = pub_name;
		volume = vol;

		mag_items++;
		this->mt = magazine;
	}

	Magazine(const Magazine &a) //Copy Constructor
		:Printed(a)
	{
		issn = a.issn;
		publisher_name = a.publisher_name;
		volume = a.volume;

		mag_items++;
		this->mt = magazine;
	}

	~Magazine() //Destructor
	{
		mag_items--;
	}

	Magazine & operator=(const Magazine &a) //Overloaded operator =
	{
		Printed::operator=(a);

		issn = a.issn;
		publisher_name = a.publisher_name;
		volume = a.volume;

		this->mt = a.mt;

		return *this;
	}
	int getISSN() { return issn; } //returns ISSN
	string getPublisherName() { return publisher_name; } //return publishers name
	int getVolume() { return volume; } //returns volume

	virtual void print() //print function
	{
		cout << "Media Type: Magazine\n";
		Printed::print();
		cout << "ISSN: " << issn << endl
			<< "Publisher Name: " << publisher_name << endl
			<< "Volume: " << volume << endl << endl;
	}
	virtual void Output(ofstream &output) //Outputs items to stock.txt
	{
		output << "Magazine,";
		Printed::Output(output);
		output << publisher_name << "," << issn << "," << volume << endl;
	}
	virtual int getItems() { return mag_items; } //returns magazine items
private:
	int issn;
	string publisher_name;
	int volume;
	static int mag_items;
};

int Magazine::mag_items = 0;