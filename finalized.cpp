#include<iostream>
#include<iomanip>
#include<cstdlib>
#include<string>
#include<fstream>	//the files
#include<vector>	//use for store data instead of array 
#include <sstream>
using namespace std;

struct Account {
	string id;
	string password;
	string name;
	bool isLogin;
};

struct Book {
	string title;
	string author;
	string publisher;
	long long isbn;
	string category;
	int edition;
	double price;
	string bookstore;
	int rating;
};

// Create a vector to represent the cart
struct Cart {
	vector<Book> books;
};

void printGreeting();
void bookstoreMenu(vector<Book>& greet_book, vector<Book>& mps_book, vector<Book>& sunny_book);
vector<Book> read_books_from_file(const string& filename);
void individualBookStoreMenu(vector<Book>& books, string bookStoreName, Cart& userCart, Account& user);
void mpsChoice(vector<Book>& book1, Cart& userCart);
void mpBestSeller(vector<Book>& book1, Cart& userCart);
void mpsBestMonth(vector<Book>& book1, Cart& userCart);
bool containBook(Cart& cart, Book book);
void makePurchase(Cart& cart);
bool avoidDuplicateAccount(string id);
void write_accounts_to_file(const vector<Account>& accounts, const string& filename);
void write_books_to_file(vector<Book>& books, const string& filename);
vector<Account> read_accounts_from_file(const string& filename);
Account registerAccount();
Account loginAccount();
void searchMenu();
vector<Book> mixAllThreeVectors();
void displayResult(vector<Book>& filteredResult);
void searchByTitle();
void searchByAuthor();
void searchByCategory();
void searchByPublisher();
void searchByEdition();
void searchByISBN();
void updateBookStore(long long isbn, int rating);
void searchByRating();

int main()
{
	//struct data
	vector<Book> greet_book = read_books_from_file("greet_book.txt");
	vector<Book> mps_book = read_books_from_file("mps_book.txt");
	vector<Book> sunny_book = read_books_from_file("sunnys_book.txt");

	//call the function
	printGreeting();
	bookstoreMenu(greet_book, mps_book, sunny_book);

	write_books_to_file(greet_book, "greet_book.txt");
	write_books_to_file(mps_book, "mps_book.txt");
	write_books_to_file(sunny_book, "sunnys_book.txt");
	return 0;
}

vector<Account> read_accounts_from_file(const string& filename) {
	// create a vector to store the account data
	vector<Account> accounts;

	// open the file for reading
	ifstream infile(filename);

	// check if the file was opened successfully
	if (!infile.is_open()) {
		cerr << "Error: Failed to open file " << filename << " for reading!" << endl;
		return accounts;
	}

	// read each line of the file and parse the account data
	string line;
	while (getline(infile, line)) {
		// create an istringstream to parse the line by #
		istringstream iss(line);
		string id, password, name, isLoginStr;

		// read each field separated by # from the istringstream
		if (getline(iss, id, '#') &&
			getline(iss, password, '#') &&
			getline(iss, name, '#') &&
			getline(iss, isLoginStr)) {
			// convert the isLogin field from string to bool
			bool isLogin = (isLoginStr == "1");

			// create an Account struct with the parsed data and add it to the vector
			accounts.push_back({ id, password, name, isLogin });
		}
	}

	// close the file
	infile.close();

	return accounts;
}

void write_accounts_to_file(const vector<Account>& accounts, const string& filename) {
	// open the file for writing
	ofstream outfile(filename);

	// check if the file was opened successfully
	if (!outfile.is_open()) {
		cerr << "Error: Failed to open file " << filename << " for writing!" << endl;
		return;
	}

	// iterate through the vector and write each struct's fields to the file separated by #
	for (const auto& account : accounts) {
		outfile << account.id << "#" << account.password << "#" << account.name << "#" << account.isLogin << endl;
	}

	// close the file
	outfile.close();

	//cout << "Accounts written to file " << filename << " successfully!" << endl;
}

bool containBook(Cart& cart, Book book) {
	vector<Book> books = cart.books;

	for (int i = 0; i < books.size(); i++)
		if (books.at(i).title == book.title && books.at(i).price == book.price)
			return true;

	return false;
}

void mpsChoice(vector<Book>& book1, Cart& userCart) //mp's choice
{
	int selected_books[10] = {};	//initialize selected_books array to 0
	int num_selected_books = 0;
	int option = 1;

	int numberOfBooks = book1.size();

	for (int i = 0; i < book1.size(); i++) {
		Book book = book1.at(i);
		cout << i + 1 << ". " << "Title: " << book.title << endl
			<< "   " << "Author: " << book.author << endl
			<< "   " << "Category: " << book.category << endl
			<< "   " << "Price: RM" << book.price << endl << endl;
	}

	cout << "Select a book to add to your cart (1-" << numberOfBooks << "), or enter 0 to exit: ";
	cin >> option;
	system("Cls");

	if (option >= 1 && option <= numberOfBooks ) {
		Book book = book1.at(option - 1);
		if (!containBook(userCart, book)) {
			userCart.books.push_back(book);
			cout << "Added \"" << book.title << "\" to your cart." << endl;
		}
		else {
			cout << "Book \"" << book1[option - 1].title << "\" has already been selected." << endl;
			system("pause");
		}
	}
	else if (option != 0)
	{
		cout << "Invalid option. Please enter a number between 1 and " << 10
			<< ", or 0 to back to Great's Bookstore menu." << endl;
	}

	cout << "You have selected the following books:" << endl;
	vector<Book> bookInsideCart = userCart.books;
	for (int i = 0; i < bookInsideCart.size(); i++)
	{
		Book book = bookInsideCart.at(i);
		cout << "- " << bookInsideCart.at(i).title << endl;
	}

}

void mpBestSeller(vector<Book>& book1, Cart& userCart) //mp's choice
{
	int selected_books[10] = {};	//initialize selected_books array to 0
	int num_selected_books = 0;
	int option = 1;

	int numberOfBooks = book1.size();

	for (int i = 0; i < 10; i++) {
		Book book = book1.at(i);
		cout << i + 1 << ". " << "Title: " << book.title << endl
			<< "   " << "Author: " << book.author << endl
			<< "   " << "Category: " << book.category << endl
			<< "   " << "Price: RM" << book.price << endl << endl;
	}

	cout << "Select a book to add to your cart (1-" << 10 << "), or enter 0 to exit: ";
	cin >> option;
	system("Cls");

	if (option >= 1 && option <= 10) {
		Book book = book1.at(option - 1);
		if (!containBook(userCart, book)) {
			userCart.books.push_back(book);
			cout << "Added \"" << book.title << "\" to your cart." << endl;
		}
		else {
			cout << "Book \"" << book1[option - 1].title << "\" has already been selected." << endl;
			system("pause");
		}
	}
	else if (option != 0)
	{
		cout << "Invalid option. Please enter a number between 1 and " << 10
			<< ", or 0 to back to Great's Bookstore menu." << endl;
	}

	cout << "You have selected the following books:" << endl;
	vector<Book> bookInsideCart = userCart.books;
	for (int i = 0; i < bookInsideCart.size(); i++)
	{
		Book book = bookInsideCart.at(i);
		cout << "- " << bookInsideCart.at(i).title << endl;
	}

}

void mpsBestMonth(vector<Book>& book1, Cart& userCart) //mp's choice
{
	int selected_books[10] = {};	//initialize selected_books array to 0
	int num_selected_books = 0;
	int option = 1;

	int numberOfBooks = 10;

	for (int i = 10; i < 20; i++) {
		Book book = book1.at(i);
		cout << i + 1 << ". " << "Title: " << book.title << endl
			<< "   " << "Author: " << book.author << endl
			<< "   " << "Category: " << book.category << endl
			<< "   " << "Price: RM" << book.price << endl << endl;
	}

	cout << "Select a book to add to your cart (1-" << numberOfBooks << "), or enter 0 to exit: ";
	cin >> option;
	system("Cls");

	if (option >= 1 && option <= numberOfBooks) {
		Book book = book1.at(option - 1 + 10);
		if (!containBook(userCart, book)) {
			userCart.books.push_back(book);
			cout << "Added \"" << book.title << "\" to your cart." << endl;
		}
		else {
			cout << "Book \"" << book1[option - 1 + 10].title << "\" has already been selected." << endl;
			system("pause");
		}
	}
	else if (option != 0)
	{
		cout << "Invalid option. Please enter a number between 1 and " << 10
			<< ", or 0 to back to Great's Bookstore menu." << endl;
	}

	cout << "You have selected the following books:" << endl;
	vector<Book> bookInsideCart = userCart.books;
	for (int i = 0; i < bookInsideCart.size(); i++)
	{
		Book book = bookInsideCart.at(i);
		cout << "- " << bookInsideCart.at(i).title << endl;
	}

}

void individualBookStoreMenu(vector<Book>& book2, string bookStoreName, Cart& userCart, Account& user) //mp's menu
{
	int option = 1;
	do {
		system("cls");
		cout << "Select the option below to continue :-)\n";
		cout << "1.\t" << bookStoreName << "'S CHOICE to Read\n";
		cout << "2.\t BEST SELLERS in " << bookStoreName <<"\n";
		cout << "3.\t BOOKS OF THE MONTH in " << bookStoreName <<"\n";
		cout << "4.\t Back to Main Menu\n";
		cout << "Option: ";
		cin >> option;
		system("Cls");

		if (option == 1)
		{
			mpsChoice(book2, userCart);
		}
		else if (option == 2)
		{
			mpBestSeller(book2,userCart);
		}
		else if (option == 3)
		{
			mpsBestMonth(book2, userCart);
		}
		else if (option == 4)
		{
			return;
		}
		else
		{
			cout << "Error!! Invalid option!\n";
		}

		
		if(option >= 1 && option <= 3 && userCart.books.size() > 0){

	

			//ask for payment
			cout << "Would you like to make payment ? (Y/N) ";
			char choice;
			cin >> choice;

			//validate
			//while loop 

			if (toupper(choice) == 'Y') {
				if (user.isLogin) {
					makePurchase(userCart);

					//Rating Section
					vector<Book> books = userCart.books;

					for (int i = 0; i < books.size(); i++)
					{
						int rating;
						cout << "Enter rating for the book " << endl << books.at(i).title << " : ";
						cin >> rating;

						books.at(i).rating = rating;
						updateBookStore(books.at(i).isbn, rating);
					}

					//Clear the cart
					userCart.books.clear();

				}
				else {
					cout << "Please Register Or Login to Make Purchase !";
					system("pause");
					cout << "Enter R or L to register or login" << endl;
					char ch;
					cin >> ch;
					if (ch == 'R')
						user = registerAccount();
					else
						user = loginAccount();

					if (user.isLogin) {
						makePurchase(userCart);

						//Rating Section
						vector<Book> books = userCart.books;

						for (int i = 0; i < books.size(); i++)
						{
							int rating;
							cout << "Enter rating for the book " << endl << books.at(i).title << " : ";
							cin >> rating;

							books.at(i).rating = rating;
							updateBookStore(books.at(i).isbn, rating);
						}

						//Clear the cart
						userCart.books.clear();
					}
					
				}
			}
		}

	} while (option != 4);
}

bool avoidDuplicateAccount(string id) {

	vector<Account> accounts = read_accounts_from_file("account.txt");

	for (int i = 0; i < accounts.size(); i++)
		if (accounts.at(i).id == id)
			return true;

	return false;
}

void updateBookStore(long long isbn, int rating) {
	vector<Book> greet_book = read_books_from_file("greet_book.txt");
	vector<Book> mps_book = read_books_from_file("mps_book.txt");
	vector<Book> sunny_book = read_books_from_file("sunnys_book.txt");


	for (Book& book : greet_book) 
		if (book.isbn == isbn)
			book.rating = rating;
		
	for (Book& book : mps_book) 
		if (book.isbn == isbn)
			book.rating = rating;

	for (Book& book : sunny_book)
		if (book.isbn == isbn)
			book.rating = rating;

	write_books_to_file(greet_book, "greet_book.txt");
	write_books_to_file(mps_book, "mps_book.txt");
	write_books_to_file(sunny_book, "sunnys_book.txt");

}

Account loginAccount() {

	system("cls");
	vector<Account> accounts = read_accounts_from_file("account.txt");
	string id;
	string password;
	string name;
	Account result;
	bool loginSuccess = false;
	cout << "Enter ID : ";
	getline(cin, id);
	cout << "Enter Password : ";
	getline(cin, password);

	for (int i = 0; i < accounts.size(); i++)
		if (accounts.at(i).id == id && accounts.at(i).password == password)
		{
			loginSuccess = true;
			cout << "Welcome " << accounts.at(i).name << "!!!" << endl;
			result = accounts.at(i);
			result.isLogin = true;
		}

	if (!loginSuccess) {
		result.isLogin = false;
		cout << "Invalid ID or Password" << endl;
	}

	system("pause");

	return result;
}

Account registerAccount() {

	system("cls");
	vector<Account> accounts = read_accounts_from_file("account.txt");
	string id;
	string password;
	string name;

	rewind(stdin);

	cout << "Enter ID : ";
	getline(cin,id);

	while (avoidDuplicateAccount(id)) {
		cout << "Duplicated ID Found " << endl;
		cout << "Enter ID : ";
		getline(cin, id);
	}

	while (id.size() >= 15) {
		cout << "The id should not be more than 15 characters!!" << endl;
		cout << "Enter ID : ";
		getline(cin, id);
	}

	cout << "Enter password : ";
	getline(cin, password);

	while (password.size() >= 15) {
		cout << "The password should not be more than 15 characters!!" << endl;
		cout << "Enter password : ";
		getline(cin, password);
	}

	cout << "Enter name : ";
	getline(cin, name);

	Account newAcc;
	newAcc.id = id;
	newAcc.password = password;
	newAcc.name = name;
	newAcc.isLogin = true;

	accounts.push_back(newAcc);
	write_accounts_to_file(accounts, "account.txt");

	return newAcc;
}

void makePurchase(Cart& cart) {
	double subtotal = 0;
	cout << "Receipt" << endl;
	cout << "=====================" << endl;
	cout << "Book Name" << "Book Price" << endl;
	cout << "=====================" << endl;
	vector<Book> books = cart.books;
	for (int i = 0; i < books.size(); i++) {
		Book book = books.at(i);
		cout << book.title << "\t" << book.price << endl;
		subtotal += book.price;
	}
	cout << "=====================" << endl;
	cout << "Subtotal :    " << subtotal << endl;
	cout << "Tax      :    " << subtotal * 0.06 << endl;
	cout << "Total Amount : " << subtotal + (subtotal * 0.06) << endl;
	//clear the cart
	cart.books.clear();
	//wait for the user input before returning to the main menu
	system("pause");
}

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
	greet_book = read_books_from_file("greet_book.txt");
	mps_book = read_books_from_file("mps_book.txt");
	sunny_book = read_books_from_file("sunnys_book.txt");
	Cart cart; 
	Account user;
	user.isLogin = false;
	string bookStoreName;
	int option = 1;
	do {
		system("cls");
		rewind(stdin);
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
			bookStoreName = "The Great Bookstore";
			individualBookStoreMenu(greet_book, bookStoreName, cart, user);
		}
		else if (option == 2)
		{
			bookStoreName = "The MPS";
			individualBookStoreMenu(mps_book, bookStoreName, cart, user);
		}
		else if (option == 3)
		{
			bookStoreName = "The Sunnys";
			individualBookStoreMenu(sunny_book, bookStoreName, cart, user);
		}
		else if (option == 4)
		{
			searchMenu();
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

void searchMenu() {

	//Search for books by title and/or author and/or category and/or publisher and/or price
	//ii.Search for books by reviews / ratings
	cout << "Search Menu" << endl;
	cout << "1. Search By Title" << endl;
	cout << "2. Search By Author" << endl;
	cout << "3. Search By Publisher" << endl;
	cout << "4. Search By Category" << endl;
	cout << "5. Search By Edition" << endl;
	cout << "6. Search By ISDN" << endl;
	cout << "7. Search By Rating" << endl;
	cout << "8. Cancel Search" << endl;
	cout << "Choose your choice to search ";

	int choice;
	cin >> choice;

	switch (choice) {
	case 1:
		searchByTitle();
		break;
	case 2:
		searchByAuthor();
		break;
	case 3:
		searchByPublisher();
		break;
	case 4:
		searchByCategory();
		break;
	case 5:
		searchByEdition();
		break;
	case 6:
		searchByISBN();
		break;
	case 7:
		searchByRating();
		break;
	case 8:
		return;
	}

}

vector<Book> mixAllThreeVectors() {
	vector<Book> greet_book = read_books_from_file("greet_book.txt");
	vector<Book> mps_book = read_books_from_file("mps_book.txt");
	vector<Book> sunny_book = read_books_from_file("sunnys_book.txt");

	vector<Book> result;

	for (Book& book : greet_book)
		result.push_back(book);


	for (Book& book : mps_book)
		result.push_back(book);

	for (Book& book : sunny_book)
		result.push_back(book);

	return result;
}

void searchByRating() {

	vector<Book> allBooks = mixAllThreeVectors();
	vector<Book> filteredBook;

	int query;
	cout << "Enter rating : ";
	cin >> query;

	for (int i = 0; i < allBooks.size(); i++)
	{
		Book book = allBooks.at(i);
		if (book.rating == query) {
			filteredBook.push_back(book);
		}
	}

	displayResult(filteredBook);
}

void searchByISBN(){

	vector<Book> allBooks = mixAllThreeVectors();
	vector<Book> filteredBook;

	//Upcoming Bug , dun insert char on this input
	long long query;
	cout << "Enter ISBN : ";
	cin >> query;

	for (int i = 0; i < allBooks.size(); i++)
	{
		Book book = allBooks.at(i);
		if (book.isbn == query) {
			filteredBook.push_back(book);
		}
	}

	displayResult(filteredBook);
}

void searchByEdition() {

	vector<Book> allBooks = mixAllThreeVectors();
	vector<Book> filteredBook;

	int query;
	cout << "Enter Edition : ";
	cin >> query;

	for (int i = 0; i < allBooks.size(); i++)
	{
		Book book = allBooks.at(i);
		if (book.edition == query) {
			filteredBook.push_back(book);
		}
	}

	displayResult(filteredBook);
}

void searchByCategory() {

	vector<Book> allBooks = mixAllThreeVectors();
	vector<Book> filteredBook;
	rewind(stdin);
	string query;
	cout << "Enter Category : ";
	getline(cin, query);

	for (int i = 0; i < allBooks.size(); i++)
	{
		Book book = allBooks.at(i);
		if (book.category.find(query) != std::string::npos) {
			filteredBook.push_back(book);
		}
	}

	displayResult(filteredBook);
}

void searchByPublisher() {

	vector<Book> allBooks = mixAllThreeVectors();
	vector<Book> filteredBook;

	string query;
	rewind(stdin);
	cout << "Enter Title : ";
	getline(cin, query);

	for (int i = 0; i < allBooks.size(); i++)
	{
		Book book = allBooks.at(i);
		if (book.publisher.find(query) != std::string::npos) {
			filteredBook.push_back(book);
		}
	}

	displayResult(filteredBook);
}

void searchByAuthor() {

	vector<Book> allBooks = mixAllThreeVectors();
	vector<Book> filteredBook;

	rewind(stdin);
	string query;
	cout << "Enter Title : ";
	getline(cin, query);

	for (int i = 0; i < allBooks.size(); i++)
	{
		Book book = allBooks.at(i);
		if (book.author.find(query) != std::string::npos) {
			filteredBook.push_back(book);
		}
	}

	displayResult(filteredBook);
}

void searchByTitle() {

	vector<Book> allBooks = mixAllThreeVectors();
	vector<Book> filteredBook;

	rewind(stdin);

	string query;
	cout << "Enter Title : ";
	getline(cin, query);

	for (int i = 0; i < allBooks.size(); i++)
	{
		Book book = allBooks.at(i);
		if(book.title.find(query) != std::string::npos) {
			filteredBook.push_back(book);
		}
	}
	
	displayResult(filteredBook);
}

void displayResult(vector<Book>& filteredResult) {

	for (int i = 0; i < filteredResult.size(); i++) {
		Book book = filteredResult.at(i);
		cout << i + 1 << ". " << "Title: " << book.title << endl
			<< "   " << "Author: " << book.author << endl
			<< "   " << "Category: " << book.category << endl
			<< "   " << "Price: RM" << book.price << endl << endl;
	}

	system("pause");
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
		book.rating = stoi(fields[8]);

		// add the book to the vector
		books.push_back(book);
	}

	// close the file stream
	infile.close();

	//cout << "Successfully read " << books.size() << " books from file." << endl;

	return books;
}

void write_books_to_file(vector<Book>& books, const string& filename)
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
	for (const auto& book : books)
	{
		//delimiter                  
		outfile << book.title << "#"
			<< book.author << "#"
			<< book.publisher << "#"
			<< book.isbn << "#"
			<< book.category << "#"
			<< book.edition << "#"
			<< book.price << "#"
			<< book.bookstore << "#" 
			<< book.rating << endl;
	}

	// close the file stream
	outfile.close();

	cout << "Successfully wrote " << books.size() << " books to file." << endl;
}
