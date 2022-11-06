#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cctype> // library for is digit()

using namespace std;

#define SIZE 100 //global definition to determine the size of the array

//1. Define the FUNCTION PROTOTYPE for all the listed functions
void readItemList(string&, string&, string[], string[], double[], double[], int&);
void writeItemList(string&, string&, string[], string[], double[], double[], int&);
void addItemList(string[], string[], double[], double[], int&);
void modifyItemList(string[], string[], double[], double[], int&);
void displayItemList(string[], string[], double[], double[], int&);
void printInvoice(string&, string&, string[], string[], double[], double[], int&);
double calculateGrandTotal(double[], double[], int&);

int main()
{
	//2. Define all the necessary variables
	string day, date;
	string itemName[SIZE] = {};
	string code[SIZE] = {};
	double priceKg[SIZE] = {};
	double weight[SIZE] = {};
	int cont, select, NoItem = 0;

	//Call readItemList with the required parameters
	readItemList(day, date, itemName, code, priceKg, weight, NoItem);
	do
	{
		cout << "1. Display Item List" << endl;
		cout << "2. Add Item List" << endl;
		cout << "3. Modify Item List" << endl;
		cout << "4. Print Invoice" << endl;
		cout << "5. Quit" << endl;

		//User will key in and select one of the functions available
		cout << "choice: ";
		cin >> select;

		system("cls");
		cin.ignore();
		
		//3.to select the function according to the user input
		if (select == 1)
		{
			//display the item from the list
			displayItemList(itemName, code, priceKg, weight, NoItem);
		}
		else if (select == 2)
		{
			// add new items into the list
			addItemList(itemName, code, priceKg, weight, NoItem);
		}
		else if (select == 3)
		{
			//Function call to modify the details of the items in the list
			modifyItemList(itemName, code, priceKg, weight, NoItem);
		}
		else if (select == 4)
		{ 
			//Function call to print the invoice of the items in the list
			printInvoice(day, date, itemName, code, priceKg, weight, NoItem);
		}
		else if (select == 5)
		{
			//Break the loop
			break;
		}
		else
		{
			cout << "Not available" << endl;
		}

		//Update the items in the text file whatever function is carried out
		writeItemList(day, date, itemName, code, priceKg, weight, NoItem);
		
		//To check whether user wants to continue to perform these functions or not
		cout << "Continue? (1-yes, 2-no): ";
		cin >> cont;

		system("cls");
	} while (cont == 1);//stop if the condition is false (user choose to stop the program)
	
	//4. Grand total of the items is calculated through the RETURN function 
	cout << "Grand Total of the bill = RM" << fixed << setprecision(2) << calculateGrandTotal(priceKg, weight, NoItem) << endl;

	return 0;
}
//5. read (ifstream) and store all the items into the respective parameters listed in "itemList.txt" 
void readItemList(string& day, string& date, string itemName[], string code[], double priceKg[], double weight[], int& NoItem)
{
	ifstream inFile;
	inFile.open("itemList.txt");

	if (inFile.fail())
	{
		cout << "The file not exit!" << endl;
	}
	else
	{
		inFile >> day;
		inFile >> date;
		while (!inFile.eof())
		{
			inFile.ignore();
			getline(inFile, itemName[NoItem]);//name
		
			inFile >> code[NoItem];

			inFile >> priceKg[NoItem] >> weight[NoItem];

			NoItem++;
		}
		NoItem--; // minus one to match NoItem with the array
		inFile.close();	
	}
}

//6. Function writeItemList --> write / update (ofstream) all the items to "itemList.txt"
void writeItemList(string& day, string& date, string itemName[], string code[], double priceKg[], double weight[], int& NoItem)
{
	ofstream outfile;
	outfile.open("itemList.txt",ios::trunc);
	if (outfile.fail())
	{
		cout << "The file not exit!" << endl;
	}
	else
	{
		outfile << day << endl;
		outfile << date;

		for (int i = 0; i < (NoItem + 1); i++)
		{
			outfile << endl << itemName[i] << endl;
			outfile << code[i] << endl;
			outfile << fixed << setprecision(2) << priceKg[i] << " "
				<< weight[i];
		}
		outfile.close();
	}
}

//7. Function addItemList --> add new items into the existing list 
void addItemList(string itemName[], string code[], double priceKg[], double weight[], int& NoItem)
{
	char select[15];//assume user will not key in wrongly more than 15 words
	bool flag = true;
	//8. This part is to confirm whether user want to key in new item or not.
	do
	{
		cout << "Add new item? (1-yes, 2-no): ";
		cin.getline(select, 15);

		if (!isdigit(select[0])) //as long as first array not a digit EXP: space, alphabet...
		{
			flag = false;
		}
		else if (strlen(select) == 1) // if user input only 1 character
		{
			if (select[0] != '1' && select[0] != '2')
			{
				flag = false;
			}
			else
			{
				flag = true;
			}
		}
		else //if is digit, but output length not 1
		{
			flag = false;
		}
	} while (!flag);

	if (select[0] == '1')
	{
		NoItem++;
		cout << "New item's name: ";
		getline(cin, itemName[NoItem]);
		cout << "New item's code: ";
		getline(cin, code[NoItem]);
		cout << "Price of new item per KG (RM): ";
		cin >> priceKg[NoItem];
		cout << "Purchasing Weight (KG): ";
		cin >> weight[NoItem];
	}
	else if (select[0] == '2')
	{
		return;
	}
}

//	//10. Function modifyItemList --> modify the details of any existing items in the list
void modifyItemList(string itemName[], string code[], double priceKg[], double weight[], int& NoItem)
{
		int select, index;
		int found = -1;

		do 
		{
			cout << "Modify item? (1-yes, 2-no): ";
			cin >> select;

		} while (select <= 0 || select >= 3);

		if (select == 1)
		{
			//11. User will key in the item to be modified through item code and find its match from the existing list
			//    If item is detected, all the details are to be keyed in 
			//    Else, it will have to cout "Item is not available." as shown in the A2 doc
			//    The COUT of modification for this module is shown in the A2 doc
			//    Marks will not be awarded if your COUT different from the sample COUT

			string Searchcode; // store the search code 

			cout << "Key in item code: ";
			cin >> Searchcode;
			for (int i = 0; i < (NoItem + 1); i++)
			{
				found = (code[i]).compare(Searchcode);// if found then = 0	
				index = i;

				if (found == 0)// when found, straight away break the loop
				{
					break;
				}
			}
		
			if (found == 0)
			{
				cout << "Item found!" << endl;
				cin.ignore();

				cout << "New item's name: ";
				getline(cin, itemName[index]);

				cout << "New item's code: ";
				getline(cin, code[index]);

				cout << "Price per KG (RM): ";
				cin >> priceKg[index];

				cout << "Purchasing Weight (KG): ";
				cin >> weight[index];
			}
			else
			{
				cout << "Item is not available." << endl;
			}
		}
}

//12. Function displayItemList --> display the details of all the items in the list
void displayItemList(string itemName[], string code[], double priceKg[], double weight[], int& NoItem)
{
	for (int j = 0; j < (NoItem + 1); j++)
	{
		cout << "Item " << j + 1 << endl;
		cout << "Name: " << itemName[j] << endl;
		cout << "Code: " << code[j] << endl;
		cout << fixed << showpoint << setprecision(2);
		cout << "Price per KG: RM" << priceKg[j] << endl;
		cout << "Purchasing Weight: " << weight[j] << "KG" << endl << endl;
	}
}

//13. Function printInvoice --> print out an invoice named "invoice.txt"
//    The output of the invoice is shown in the A2 doc
//    Marks will not be awarded if the output of your invoice is different from the sample invoice
void printInvoice(string& day, string& date, string itemName[], string code[], double priceKg[], double weight[], int& NoItem) 
{
	double sum = 0;

	ofstream invoiceFile;
	invoiceFile.open("invoice.txt", ios::trunc);
	invoiceFile << "Date: " << date << endl;
	invoiceFile << "Day: " << day << endl;
	invoiceFile << "List of Items: " << endl;

	for (int i = 0; i < (NoItem + 1); i++)
	{
		invoiceFile << i + 1 << ". " << itemName[i] << " = "
			<< fixed << setprecision(2) << weight[i] << "KG * RM" << priceKg[i] << " = RM"
			<< (weight[i] * priceKg[i]);
		invoiceFile << endl;
		sum = sum + (weight[i] * priceKg[i]);
	}
	invoiceFile << "Grand Total of the bill = RM" << sum;
}

//14. Function calculateGrandTotal --> calculate the grand total of the items purchase and RETURN the grand total to the calling function
double calculateGrandTotal(double priceKg[], double weight[], int& NoItem) 
{
	double sum = 0;
	for (int i = 0; i < (NoItem + 1); i++)
	{
		sum = sum + (weight[i] * priceKg[i]);
	}
	return sum;
}