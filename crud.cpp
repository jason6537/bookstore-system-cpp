#include<iostream>
#include<iomanip>
#include<cstdlib>
#include<string>

using namespace std;

struct Book
{
	string title;
	string author;
	string publisher;
	long long isbn;
	string category;
	int edition;
	double price;
};

void searchMenu() {

	cout << "Search Menu" << endl;
	cout << "1. Search By Title" << endl;
	cout << "2. Search By Author" << endl;
	cout << "3. Search By Publisher" << endl;
	cout << "4. Search By Category" << endl;
	cout << "5. Search By Edition" << endl;
	cout << "6. Search By ISDB" << endl;
	cout << "7. Search By Review" << endl;
	cout << "8. Cancel Search" << endl;
	cout << "Choose your choice to search ";

}

void searchBook() {

	int input;
	do {

		system("cls");
		searchMenu();
		cin >> input;

	}while(input != 8);

	switch(input){
		case 1:
			searchByTitle();



	}

}

void saveBookToFile() {
	
}

void searchByTitle(Book[] books) {




}
