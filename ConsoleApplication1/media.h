#include <iostream>
#include <string>
#include <fstream>
using namespace std;

#pragma once

enum MediaType { magazine, book, newspaper, film, none }; //MediaType enum

class Media { //The Abstract Class Media
public:
	Media(string p = "none", char status = 'A', int barCode = 1) //Default Constructor
	{
		title = p;

		this->status = status;
		this->barCode = barCode;
		mt = none;

		med_items++;
		mediaID = med_items;
	}
	Media(const Media &a) //Copy Constructor
	{
		title = a.title;

		this->status = a.status;
		this->barCode = a.barCode;
		mt = none;

		med_items++;
		mediaID = med_items;
	}
	Media & operator=(const Media &a) //Overloaded Operator =
	{

		title = a.title;

		this->status = a.status;
		this->barCode = a.barCode;

		return *this;
	}
	virtual ~Media() = 0 //Destructor
	{
		med_items--;
	}
	virtual int getBarCode() = 0;// returns the bar-code of the media item
	virtual void print() = 0 // virtual print
	{
		cout << "Media ID: " << mediaID << endl
			<< "Title: " << title << endl
			<< "BarCode: " << barCode << endl
			<< "Status: " << status << endl;
	}

	virtual int getMediaID() = 0 { return mediaID; } //returns Media ID
	virtual int getItems() = 0 { return med_items; } //returns Items
	Media &ChangeAvailable(char letter) //Status change
	{
		status = letter;
		return *this;
	}

	virtual void Output(ofstream &output) = 0 //Outputs items to stock.txt
	{
		output << title << "," << barCode << "," << status << ",";
	}

	virtual char getStatus() = 0 { return status; } //returns status
	virtual MediaType getMediaType() = 0; //returns MediaType
protected:
	string title;
	int barCode;
	char    status;           	// ‘A’: available in stock, ‘S’: sold.
	MediaType mt;    	// enum- 0: Magazine, 1: Book, 2: Newspaper, 3:Film.
	static int med_items;
	int mediaID;
};

int Media::med_items = 0;