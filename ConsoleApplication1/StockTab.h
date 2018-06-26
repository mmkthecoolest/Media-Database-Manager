#include "Media-Film.h"
#include "Printed-Book.h"
#include "Printed-Magazine.h"
#include "Printed-Newspaper.h"
#include <fstream>

#pragma once

class StockTab
{
public:
	StockTab(int itemCount = 0)//Default Constructor
	{
		this->itemCount = itemCount;

		mptr = new Media*[this->itemCount];
	}

	~StockTab()//Destructor
	{
		for (int i = 0; i < itemCount; i++)
			delete mptr[i];

		delete[] mptr;
	}

	StockTab & Add(ifstream &input,MediaType mt, int index)//takes mt from input and adds stock.txt files to mptr
	{
		string titleMedia, publisher_nameMagazine, authorBook, publisherBook, cityNewspaper, actorFilm;
		int barCodeMedia, no_of_pagesPrinted, date_of_printPrinted, issnMagazine, volumeMagazine, isbnBook, volumeNewspaper, prod_yrFilm;
		char statusMedia, dummy;
		switch (mt)
		{
		case magazine:
			getline(input, titleMedia, ',');
			input >> barCodeMedia >> dummy >> statusMedia >> dummy;
			input >> no_of_pagesPrinted >> dummy >> date_of_printPrinted >> dummy;
			getline(input, publisher_nameMagazine, ',');
			input >> issnMagazine >> dummy >> volumeMagazine;

			mptr[index] = new Magazine(titleMedia, statusMedia, barCodeMedia, no_of_pagesPrinted, date_of_printPrinted, issnMagazine, publisher_nameMagazine, volumeMagazine);
			break;
		case book:
			getline(input, titleMedia, ',');
			input >> barCodeMedia >> dummy >> statusMedia >> dummy;
			input >> no_of_pagesPrinted >> dummy >> date_of_printPrinted >> dummy;
			getline(input, authorBook, ',');
			getline(input, publisherBook, ',');
			input >> isbnBook;

			mptr[index] = new Book(titleMedia, statusMedia, barCodeMedia, no_of_pagesPrinted, date_of_printPrinted, authorBook, publisherBook, isbnBook);
			break;
		case newspaper:
			getline(input, titleMedia, ',');
			input >> barCodeMedia >> dummy >> statusMedia >> dummy;
			input >> no_of_pagesPrinted >> dummy >> date_of_printPrinted >> dummy;
			getline(input, cityNewspaper, ',');
			input >> volumeNewspaper;

			mptr[index] = new Newspaper(titleMedia, statusMedia, barCodeMedia, no_of_pagesPrinted, date_of_printPrinted, cityNewspaper, volumeNewspaper);
			break;
		case film:
			getline(input, titleMedia, ',');
			input >> barCodeMedia >> dummy >> statusMedia >> dummy;
			getline(input, actorFilm, ',');
			input >> prod_yrFilm;

			mptr[index] = new Film(titleMedia, statusMedia, barCodeMedia, actorFilm, prod_yrFilm);
			break;
		default:
			break;
		}
		return *this;
	}

	void input(ifstream &input)//inputs the mediatype from stock.txt
	{
		string MedType;
		
		for (int i = 0; i < itemCount; i++)
		{
			input.ignore();
			getline(input, MedType, ',');

			if (MedType == "Magazine")
				Add(input, magazine, i);

			else if (MedType == "Book")
				Add(input, book, i);

			else if (MedType == "Newspaper")
				Add(input, newspaper, i);

			else if (MedType == "Film")
				Add(input, film, i);
			
			else
			{
				cout << "Invalid media type...\n";
				exit(1);
			}
		}
	}

	void print() const//prints stock
	{
		for (int i = 0; i < itemCount; i++)
		{
			mptr[i]->print();
		}
	}

	void printSoldStock() const//prints sold stock
	{
		cout << "SOLD STOCK REPORT:\n\n";
		
		for (int i = 0; i < itemCount; i++)
			if (mptr[i]->getStatus() == 'S')
				mptr[i]->print();
	}

	void printAvailableStock() const//prints available stock
	{

		for (int i = 0; i < itemCount; i++)
			if (mptr[i]->getStatus() == 'A')
				mptr[i]->print();
	}

	int getAvailableCount() const//returns item amount
	{
		int x = 0;
		for (int i = 0; i < itemCount; i++)
			if (mptr[i]->getStatus() == 'A')
				x++;

		return x;
	}

	int getitemCount() const{ return itemCount; }//returns count
	Media *getMPTR(int i) const { return mptr[i]; }//returns mptr
private:
	int itemCount;	
	Media **mptr;
};