#include "Media-Printed.h"
#pragma once

class Newspaper : public Printed
{
public:
	Newspaper(string p = "none", char status = 'A', int barCode = 1, int no_of_pages = 0, int date_of_print = 0, string city = "none", int volume = 0)
		:Printed(p, status, barCode, no_of_pages, date_of_print) //Default Constructor
	{
		this->city = city;
		this->volume = volume;
		news_items++;
		mt = newspaper;
	}
	Newspaper(const Newspaper &a) //Copy Constructor
		:Printed(a)
	{
		this->city = a.city;
		this->volume = a.volume;
		news_items++;
		mt = newspaper;
	}
	~Newspaper() //Destructor
	{
		news_items--;
	}
	Newspaper & operator=(const Newspaper &a) //Overloaded Oprator =
	{
		Printed::operator=(a);
		this->city = a.city;
		this->volume = a.volume;
		mt = a.mt;

		return *this;
	}
	virtual void print() //print function
	{
		cout << "Media Type: Newspaper\n";
		Printed::print();
		cout << "City: " << city << endl
			<< "Volume: " << volume << endl << endl;

	}
	virtual void Output(ofstream &output) //Outputs items to stock.txt
	{
		output << "Newspaper,";
		Printed::Output(output);
		output << city << "," << volume << endl;
	}
	string getCity() { return city; } //returns city name
	int getVolume() { return volume; } //returns volume number
	virtual int getItems() { return news_items; } //returms items

private:
	string city;
	int volume;
	static int news_items;
};
int Newspaper::news_items = 0;