#include<iostream>
#include<iomanip>
#include<cstdlib>
#include<string>
#include<fstream>
#include<vector>
using namespace std;

struct Book {
	string title;
	string author;
	string publisher;
	long long isbn;
	string category;
	int edition;
	double price;
	string bookstore;
};

struct Cart {
	Book books[100];
	int numOfBooks;
};
void displayBooksPublisher(string input);
void displayBooksAuthor(string input);
void displayBooksEdition(string input);
void displayBooksPrice(double input);
void displayRating(int input);

void write_books_to_file(Book books[], const string& filename)
{
	// open the output file stream
	ofstream outfile(filename);

	// check if the file opened successfully
	if (!outfile)
	{
		cerr << "Error: could not open file" << endl;
		return;
	}

	// iterate through the array and write each struct to the file with "#" delimiter
	for (int i = 0; i < 30; i++)
	{
		outfile << books[i].title << "#"
			<< books[i].author << "#"
			<< books[i].publisher << "#"
			<< books[i].isbn << "#"
			<< books[i].category << "#"
			<< books[i].edition << "#"
			<< books[i].price << "#"
			<< books[i].bookstore << endl;
	}

	// close the file stream
	outfile.close();

	cout << "Successfully wrote " << 30 << " books to file." << endl;
}

vector<Book> read_books_from_file(const string& filename)
{
	vector<Book> books;

	// open the input file stream
	ifstream infile(filename);

	// check if the file opened successfully
	if (!infile)
	{
		cerr << "Error: could not open file" << endl;
		return books;
	}

	string line;
	while (getline(infile, line))
	{
		// split the line into fields using "#" delimiter
		string delimiter = "#";
		size_t pos = 0;
		string field;
		vector<string> fields;
		while ((pos = line.find(delimiter)) != string::npos)
		{
			field = line.substr(0, pos);
			fields.push_back(field);
			line.erase(0, pos + delimiter.length());
		}
		fields.push_back(line);

		// create a new mps_book struct and initialize its fields with the data from the line
		Book book;
		book.title = fields[0];
		book.author = fields[1];
		book.publisher = fields[2];
		book.isbn = stoll(fields[3]);
		book.category = fields[4];
		book.edition = stoi(fields[5]);
		book.price = stod(fields[6]);
		book.bookstore = fields[7];

		// add the book to the vector
		books.push_back(book);
	}

	// close the file stream
	infile.close();

	cout << "Successfully read " << books.size() << " books from file." << endl;

	return books;
}

void display_books(const vector<Book>& books)
{
	// iterate through the vector and print each struct's fields
	for (const auto& book : books)
	{
		cout << "Title: " << book.title << endl;
		cout << "Author: " << book.author << endl;
		cout << "Publisher: " << book.publisher << endl;
		cout << "ISBN: " << book.isbn << endl;
		cout << "Category: " << book.category << endl;
		cout << "Edition: " << book.edition << endl;
		cout << "Price: $" << book.price << endl;
		cout << "Bookstore: " << book.bookstore << endl;
		cout << endl;
	}
}

//function definition
void printGreeting() //greeting
{
	cout << "Belo! Welcome to Nomi Books Centre!\n";
	cout << endl;
	cout << "We have 3 bookstores in our one-stop centre," << 
		 "feel free to explore \nthe bookstores below " <<
		"and shop online for your favourite books!\n";
	cout << endl;
}

void bookstoreMenu(vector<Book>& greet_book, vector<Book>& mps_book, vector<Book>& sunny_book) //main menu
{
	int option = 1;
	do {
		cout << "Select the option below to continue from 1-4\n";
		cout << "1.\tThe Great Bookstore\n";
		cout << "2.\tMP Bookstore\n";
		cout << "3.\tSunny Bookstore\n";
		cout << "4.\tSearch for books\n";
		cout << "5.\tExit\n";
		cout << "Option: ";
		cin >> option;
		system("Cls");

		if (option == 1)
		{
			greatBookstoreMenu(greet_book);
		}
		else if (option == 2)
		{
			mpBookstoreMenu(mps_book);
		}
		else if (option == 3)
		{
			sunnyBookstoreMenu(sunny_book);
		}
		else if (option == 4)
		{
			searchBooks();
		}
		else if (option == 5)
		{
			exit(0);
		}
		else
		{
			cout << "Error!! Invalid option!\n";
		}
	} while (option != 5);
}

void greatBookstoreMenu(vector<Book>& book1) //great's menu
{
	int option = 1;
	do {
		cout << "Select the option below to continue from 1-4\n";
		cout << "1.\t GREAT'S CHOICE to Read\n";
		cout << "2.\t BEST SELLERS in GREAT'S\n";
		cout << "3.\t BOOKS OF THE MONTH in GREAT'S\n";
		cout << "4.\t Back to Main Menu\n";
		cout << "Option: ";
		cin >> option;
		system("Cls");

		if (option == 1)
		{
			// greatsChoice(greats_book book1[]);
			// global scope book1 variable from int main function to global file scope.
			greatsChoice(book1);
		}
		else if (option == 2)
		{
			greatsBestSeller(book1);
		}
		else if (option == 3)
		{
			greatsBooksMonth(book1);
		}
		else if (option == 4)
		{
			bookstoreMenu(book1);
		}
		else
		{
			cout << "Error!! Invalid option!\n";
		}
	} while (option != 4);
}

void greatsChoice(vector<Book>& book1) //great's choice
{
	int selected_books[10] = {};	//initialize selected_books array to 0
	int num_selected_books = 0;
	int option = 1;

	do {	//print list of the books
		for (int i = 0; i < 10; i++)
		{
			Book book = book1.at(i);
			cout << i + 1 << ". " << "Title: " << book.title << endl
				<< "   " << "Author: " << book.author << endl
				<< "   " << "Category: " << book.category << endl
				<< "   " << "Price: RM" << book.price << endl << endl;
		}
		cout << "Select a book to add to your cart (1-" << 10 << "), or enter 0 to exit: ";
		cin >> option;
		system("Cls");

		if (option >= 1 && option <= 10)	// check if the book has already been selected
		{
			if (selected_books[option - 1] == 0)	// add the book to the cart
			{
				selected_books[option - 1] = 1;
				num_selected_books++;
				cout << "Added \"" << book1[option - 1].title << "\" to your cart." << endl;
			}
			else
			{
				cout << "Book \"" << book1[option - 1].title << "\" has already been selected." << endl;
			}
		}
		else if (option != 0)
		{
			cout << "Invalid option. Please enter a number between 1 and " << 10
				<< ", or 0 to back to Great's Bookstore menu." << endl;
		}
	} while (option != 0 && num_selected_books < 10); // exit if all books have been selected or the user enters 0

	cout << "You have selected the following books:" << endl;
	for (int i = 0; i < 10; i++)
	{
		if (selected_books[i] == 1)
		{
			cout << "- " << book1[i].title << endl;
		}
	}

	system("pause");
}

void greatsBestSeller(vector<Book>& book1) //great's best seller
{
	int selected_books[10] = {};	//initialize selected_books array to 0
	int num_selected_books = 0;
	int option = 1;

	do {	//print list of the books
		for (int i = 10; i < 20; i++)
		{
			cout << i - 9 << ". " << "Title: " << book1[i].title << endl
				<< "   " << "Author: " << book1[i].author << endl
				<< "   " << "Category: " << book1[i].category << endl
				<< "   " << "Price: RM" << book1[i].price << endl << endl;
		}
		cout << "Select a book to add to your cart (1-" << 10 << "), or enter 0 to exit: ";
		cin >> option;
		system("Cls");

		if (option >= 1 && option <= 10)	// check if the book has already been selected
		{
			if (selected_books[option - 1] == 0)	// add the book to the cart
			{
				selected_books[option - 1] = 1;
				num_selected_books++;
				cout << "Added \"" << book1[option - 1].title << "\" to your cart." << endl;
			}
			else
			{
				cout << "Book \"" << book1[option - 1].title << "\" has already been selected." << endl;
				system("pause");
			}
		}
		else if (option != 0)
		{
			cout << "Invalid option. Please enter a number between 1 and " << 10
				<< ", or 0 to back to Great's Bookstore menu." << endl;
		}
	} while (option != 0 && num_selected_books < 10); // exit if all books have been selected or the user enters 0

	cout << "You have selected the following books:" << endl;
	for (int i = 0; i < 10; i++)
	{
		if (selected_books[i] == 1)
		{
			cout << "- " << book1[i].title << endl;
		}
	}
}

void greatsBooksMonth(vector<Book>& book1) //great's books of the month
{
	int selected_books[10] = {};	//initialize selected_books array to 0
	int num_selected_books = 0;
	int option = 1;

	do {	//print list of the books
		for (int i = 20; i < 30; i++)
		{
			cout << i - 19 << ". " << "Title: " << book1[i].title << endl
				<< "   " << "Author: " << book1[i].author << endl
				<< "   " << "Category: " << book1[i].category << endl
				<< "   " << "Price: RM" << book1[i].price << endl << endl;
		}
		cout << "Select a book to add to your cart (1-" << 10 << "), or enter 0 to exit: ";
		cin >> option;
		system("Cls");

		if (option >= 1 && option <= 10)	// check if the book has already been selected
		{
			if (selected_books[option - 1] == 0)	// add the book to the cart
			{
				selected_books[option - 1] = 1;
				num_selected_books++;
				cout << "Added \"" << book1[option - 1].title << "\" to your cart." << endl;
			}
			else
			{
				cout << "Book \"" << book1[option - 1].title << "\" has already been selected." << endl;
			}
		}
		else if (option != 0)
		{
			cout << "Invalid option. Please enter a number between 1 and " << 10
				<< ", or 0 to back to Great's Bookstore menu." << endl;
		}
	} while (option != 0 && num_selected_books < 10); // exit if all books have been selected or the user enters 0

	cout << "You have selected the following books:" << endl;
	for (int i = 0; i < 10; i++)
	{
		if (selected_books[i] == 1)
		{
			cout << "- " << book1[i].title << endl;
		}
	}
}

void mpBookstoreMenu(vector<Book>& book2) //mp's menu
{
	int option = 1;
	do {
		cout << "Select the option below to continue :-)\n";
		cout << "1.\t MP'S CHOICE to Read\n";
		cout << "2.\t BEST SELLERS in MP'S\n";
		cout << "3.\t BOOKS OF THE MONTH in MP'S\n";
		cout << "4.\t Back to Main Menu\n";
		cout << "Option: ";
		cin >> option;
		system("Cls");

		if (option == 1)
		{
			mpsChoice(book2);
		}
		else if (option == 2)
		{
			mpsBestSeller(book2);
		}
		else if (option == 3)
		{
			mpsBooksMonth(book2);
		}
		else if (option == 4)
		{
			bookstoreMenu();
		}
		else
		{
			cout << "Error!! Invalid option!\n";
		}
	} while (option != 4);
}

void mpsChoice(vector<Book>& book1) //mp's choice
{
	int selected_books[10] = {};	//initialize selected_books array to 0
	int num_selected_books = 0;
	int option = 1;

	do {	//print list of the books
		for (int i = 0; i < 10; i++)
		{
			cout << i + 1 << ". " << "Title: " << book1[i].title << endl
				<< "   " << "Author: " << book1[i].author << endl
				<< "   " << "Category: " << book1[i].category << endl
				<< "   " << "Price: RM" << book1[i].price << endl << endl;
		}
		cout << "Select a book to add to your cart (1-" << 10 << "), or enter 0 to exit: ";
		cin >> option;
		system("Cls");

		if (option >= 1 && option <= 10)	// check if the book has already been selected
		{
			if (selected_books[option - 1] == 0)	// add the book to the cart
			{
				selected_books[option - 1] = 1;
				num_selected_books++;
				cout << "Added \"" << book1[option - 1].title << "\" to your cart." << endl;
			}
			else
			{
				cout << "Book \"" << book1[option - 1].title << "\" has already been selected." << endl;
			}
		}
		else if (option != 0)
		{
			cout << "Invalid option. Please enter a number between 1 and " << 10
				<< ", or 0 to back to Great's Bookstore menu." << endl;
		}
	} while (option != 0 && num_selected_books < 10); // exit if all books have been selected or the user enters 0

	cout << "You have selected the following books:" << endl;
	for (int i = 0; i < 10; i++)
	{
		if (selected_books[i] == 1)
		{
			cout << "- " << book1[i].title << endl;
		}
	}
}

void mpsBestSeller(vector<Book>& book1) //mp's best seller
{
	int selected_books[10] = {};	//initialize selected_books array to 0
	int num_selected_books = 0;
	int option = 1;

	do {	//print list of the books
		for (int i = 10; i < 20; i++)
		{
			cout << i - 9 << ". " << "Title: " << book1[i].title << endl
				<< "   " << "Author: " << book1[i].author << endl
				<< "   " << "Category: " << book1[i].category << endl
				<< "   " << "Price: RM" << book1[i].price << endl << endl;
		}
		cout << "Select a book to add to your cart (1-" << 10 << "), or enter 0 to exit: ";
		cin >> option;
		system("Cls");

		if (option >= 1 && option <= 10)	// check if the book has already been selected
		{
			if (selected_books[option - 1] == 0)	// add the book to the cart
			{
				selected_books[option - 1] = 1;
				num_selected_books++;
				cout << "Added \"" << book1[option - 1].title << "\" to your cart." << endl;
			}
			else
			{
				cout << "Book \"" << book1[option - 1].title << "\" has already been selected." << endl;
			}
		}
		else if (option != 0)
		{
			cout << "Invalid option. Please enter a number between 1 and " << 10
				<< ", or 0 to back to Great's Bookstore menu." << endl;
		}
	} while (option != 0 && num_selected_books < 10); // exit if all books have been selected or the user enters 0

	cout << "You have selected the following books:" << endl;
	for (int i = 0; i < 10; i++)
	{
		if (selected_books[i] == 1)
		{
			cout << "- " << book1[i].title << endl;
		}
	}
}

void mpsBooksMonth(vector<Book>& book1) //mp's books of the month
{
	int selected_books[10] = {};	//initialize selected_books array to 0
	int num_selected_books = 0;
	int option = 1;

	do {	//print list of the books
		for (int i = 20; i < 30; i++)
		{
			cout << i - 19 << ". " << "Title: " << book1[i].title << endl
				<< "   " << "Author: " << book1[i].author << endl
				<< "   " << "Category: " << book1[i].category << endl
				<< "   " << "Price: RM" << book1[i].price << endl << endl;
		}
		cout << "Select a book to add to your cart (1-" << 10 << "), or enter 0 to exit: ";
		cin >> option;
		system("Cls");

		if (option >= 1 && option <= 10)	// check if the book has already been selected
		{
			if (selected_books[option - 1] == 0)	// add the book to the cart
			{
				selected_books[option - 1] = 1;
				num_selected_books++;
				cout << "Added \"" << book1[option - 1].title << "\" to your cart." << endl;
			}
			else
			{
				cout << "Book \"" << book1[option - 1].title << "\" has already been selected." << endl;
			}
		}
		else if (option != 0)
		{
			cout << "Invalid option. Please enter a number between 1 and " << 10
				<< ", or 0 to back to Great's Bookstore menu." << endl;
		}
	} while (option != 0 && num_selected_books < 10); // exit if all books have been selected or the user enters 0

	cout << "You have selected the following books:" << endl;
	for (int i = 0; i < 10; i++)
	{
		if (selected_books[i] == 1)
		{
			cout << "- " << book1[i].title << endl;
		}
	}
}

void sunnyBookstoreMenu(vector<Book>& book1) //sunny menu
{
	int option = 1;
	do {
		cout << "Select the option below to continue :-)\n";
		cout << "1.\t SUNNY'S CHOICE to Read\n";
		cout << "2.\t BEST SELLERS in SUNNY'S\n";
		cout << "3.\t BOOKS OF THE MONTH in SUNNY'S\n";
		cout << "4.\t Back to Main Menu\n";
		cout << "Option: ";
		cin >> option;
		system("Cls");

		if (option == 1)
		{
			sunnysChoice(book1);
		}
		else if (option == 2)
		{
			sunnysBestSeller(book1);
		}
		else if (option == 3)
		{
			sunnysBooksMonth(book1);
		}
		else if (option == 4)
		{
			//bookstoreMenu();
		}
		else
		{
			cout << "Error!! Invalid option!\n";
		}
	} while (option != 4);
}

void sunnysChoice(vector<Book>& book1) //sunny's choice
{
	int selected_books[10] = {};	//initialize selected_books array to 0
	int num_selected_books = 0;
	int option = 1;

	do {	//print list of the books
		for (int i = 0; i < 10; i++)
		{
			cout << i + 1 << ". " << "Title: " << book1[i].title << endl
				<< "   " << "Author: " << book1[i].author << endl
				<< "   " << "Category: " << book1[i].category << endl
				<< "   " << "Price: RM" << book1[i].price << endl << endl;
		}
		cout << "Select a book to add to your cart (1-" << 10 << "), or enter 0 to exit: ";
		cin >> option;
		system("Cls");

		if (option >= 1 && option <= 10)	// check if the book has already been selected
		{
			if (selected_books[option - 1] == 0)	// add the book to the cart
			{
				selected_books[option - 1] = 1;
				num_selected_books++;
				cout << "Added \"" << book1[option - 1].title << "\" to your cart." << endl;
			}
			else
			{
				cout << "Book \"" << book1[option - 1].title << "\" has already been selected." << endl;
			}
		}
		else if (option != 0)
		{
			cout << "Invalid option. Please enter a number between 1 and " << 10
				<< ", or 0 to back to Great's Bookstore menu." << endl;
		}
	} while (option != 0 && num_selected_books < 10); // exit if all books have been selected or the user enters 0

	cout << "You have selected the following books:" << endl;
	for (int i = 0; i < 10; i++)
	{
		if (selected_books[i] == 1)
		{
			cout << "- " << book1[i].title << endl;
		}
	}
}

void sunnysBestSeller(vector<Book>& book1) //sunny's best seller
{
	int selected_books[10] = {};	//initialize selected_books array to 0
	int num_selected_books = 0;
	int option = 1;

	do {	//print list of the books
		for (int i = 10; i < 20; i++)
		{
			cout << i - 9 << ". " << "Title: " << book1[i].title << endl
				<< "   " << "Author: " << book1[i].author << endl
				<< "   " << "Category: " << book1[i].category << endl
				<< "   " << "Price: RM" << book1[i].price << endl << endl;
		}
		cout << "Select a book to add to your cart (1-" << 10 << "), or enter 0 to exit: ";
		cin >> option;
		system("Cls");

		if (option >= 1 && option <= 10)	// check if the book has already been selected
		{
			if (selected_books[option - 1] == 0)	// add the book to the cart
			{
				selected_books[option - 1] = 1;
				num_selected_books++;
				cout << "Added \"" << book1[option - 1].title << "\" to your cart." << endl;
			}
			else
			{
				cout << "Book \"" << book1[option - 1].title << "\" has already been selected." << endl;
			}
		}
		else if (option != 0)
		{
			cout << "Invalid option. Please enter a number between 1 and " << 10
				<< ", or 0 to back to Great's Bookstore menu." << endl;
		}
	} while (option != 0 && num_selected_books < 10); // exit if all books have been selected or the user enters 0

	cout << "You have selected the following books:" << endl;
	for (int i = 0; i < 10; i++)
	{
		if (selected_books[i] == 1)
		{
			cout << "- " << book1[i].title << endl;
		}
	}
}

void sunnysBooksMonth(vector<Book>& book1) //sunny's books of the month
{
	int selected_books[10] = {};	//initialize selected_books array to 0
	int num_selected_books = 0;
	int option = 1;

	do {	//print list of the books
		for (int i = 20; i < 30; i++)
		{
			cout << i - 19 << ". " << "Title: " << book1[i].title << endl
				<< "   " << "Author: " << book1[i].author << endl
				<< "   " << "Category: " << book1[i].category << endl
				<< "   " << "Price: RM" << book1[i].price << endl << endl;
		}
		cout << "Select a book to add to your cart (1-" << 10 << "), or enter 0 to exit: ";
		cin >> option;
		system("Cls");

		if (option >= 1 && option <= 10)	// check if the book has already been selected
		{
			if (selected_books[option - 1] == 0)	// add the book to the cart
			{
				selected_books[option - 1] = 1;
				num_selected_books++;
				cout << "Added \"" << book1[option - 1].title << "\" to your cart." << endl;
			}
			else
			{
				cout << "Book \"" << book1[option - 1].title << "\" has already been selected." << endl;
			}
		}
		else if (option != 0)
		{
			cout << "Invalid option. Please enter a number between 1 and " << 10
				<< ", or 0 to back to Great's Bookstore menu." << endl;
		}
	} while (option != 0 && num_selected_books < 10); // exit if all books have been selected or the user enters 0

	cout << "You have selected the following books:" << endl;
	for (int i = 0; i < 10; i++)
	{
		if (selected_books[i] == 1)
		{
			cout << "- " << book1[i].title << endl;
		}
	}
}

void searchBooks() //books' details all over the bookstore
{
	string input;
	cout << "Enter book details such as title, author, publisher, category, edition, ISBN, price in RM,\n";
	cout << "or reviews/ratings of books from 1 to 5:\n";
	getline(cin, input);

	if (!input.empty()) {
		displayBooksTitle(input);
		displayBooksCategory(input);
		displayISBN(input);
		displayBooksPublisher(input);
		displayBooksAuthor(input);
		displayBooksEdition(input);
		displayBooksPrice(stod(input));
		displayRating(stoi(input));
	}
	else {
		cout << "Error! Record Not Found!!" << endl;
	}
	system("Cls");
}

void displayBooksTitle(string input)
{

}

void displayBooksCategory(string input)
{

}

void displayISBN(string input)
{

}

void displayBooksPublisher(string input)
{

}

void displayBooksAuthor(string input)
{

}

void displayBooksEdition(string input)
{

}

void displayBooksPrice(double input)
{

}

void displayRating(int input)
{

}

int main()
{
	vector<Book> greet_book = read_books_from_file("greet_book.txt");
	vector<Book> mps_book = read_books_from_file("mps_book.txt");
	vector<Book> sunny_book = read_books_from_file("sunnys_book.txt");

	//call the function
	printGreeting();
	bookstoreMenu(greet_book, mps_book, sunny_book);

	return 0;
}