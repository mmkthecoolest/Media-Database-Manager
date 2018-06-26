#include "StockTab.h"
#include "SaleTranxs.h"
using namespace std;

void main()
{
	ifstream input("stock.txt");

	int n;
	input >> n;

	string str_dummy;
	StockTab stock(n);
	stock.input(input);
	SaleTranxs table;

	int option;
	while (1)
	{
		cout << "Please select form the following menu : " << endl;
		cout << endl;
		cout << "1.Buy a media item " << endl;
		cout << "2.Return a media item" << endl;
		cout << "3.Replace a media item " << endl;
		cout << "4.Generate Available Stock Report " << endl;
		cout << "5.Generate Sold Stock Report " << endl;
		cout << "6. Generate Transaction Report" << endl;
		cout << "7.Close" << endl << endl;

		cout << "Please enter your choice : ";
		cin >> option;

		input.close();
		ofstream output("stock.txt");
		switch (option)
		{
		case 1:
			table.TransactionBuy(stock); //calls the TransactionBuy function
			break;
		case 2:
			table.TransactionReturn(); //calls the TransactionReturn function
			break;
		case 3:
			table.TransactionReplace(stock); //calls the TransactionReplace function
			break;
		case 4:
			cout << "AVAILABLE STOCK REPORT:\n\n";
			table.printAvailableStock(stock); //displays the available stock report
			break;
		case 5:
			table.printSoldStock(); //prints the sold items from StockTab
			break;
		case 6:
			table.print(); //prints all items currently in SaleTranxs table
			break;
		case 7:
			//closes the file
			table.Output(output, stock);
			exit(1);
			output.close();
			break;
		default:
			cout << "Invalid option...\n";
			break;
		}
	}
}