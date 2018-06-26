#include "media.h"
#pragma once

class Film : public Media
{
public:
	Film(string p = "none", char status = 'A', int barCode = 1, string actor = "none", int prod_year = 0)
		:Media(p, status, barCode) //Default Constructor
	{
		this->actor = actor;
		this->prod_yr = prod_year;
		mt = film;
		film_items++;
	}
	Film(const Film &a) //Copy Constructor
		:Media(a)
	{
		this->actor = a.actor;
		this->prod_yr = a.prod_yr;
		mt = film;
		film_items++;
	}
	~Film() //Destructor
	{
		film_items--;
	}
	Film &operator=(const Film &a) //Overloaded Operator =
	{
		Media::operator=(a);

		this->actor = a.actor;
		this->prod_yr = a.prod_yr;
		mt = a.mt;

		return *this;
	}
	int getBarCode() { return barCode; } //returns barcode
	virtual void print() //print function
	{
		cout << "Media Type: Film\n";
		Media::print();
		cout << "Leading Actor: " << actor << endl
			<< "Production Year: " << prod_yr << endl << endl;
	}
	virtual void Output(ofstream &output) //Outputs items to stock.txt
	{
		output << "Film,";
		Media::Output(output);
		output << actor << "," << prod_yr << endl;
	}
	MediaType getMediaType() { return mt; } //return MediaType
	virtual int getItems() { return film_items; } //return Media Items
	virtual int getMediaID() { return mediaID; } //return Media ID
	virtual char getStatus() { return status; } //return Status
private:
	string actor;
	int prod_yr;
	static int film_items;
};
int Film::film_items = 0;