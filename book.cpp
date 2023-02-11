#include <sstream>
#include <iomanip>
#include "book.h"

using namespace std;

Book::Book(const std::string category, const std::string name, double price, int qty, string isbn, string author)
: Product(category, name, price, qty), isbn_(isbn), author_(author) {

}

set<string> Book::keywords() const {
	string words = name_ + " " + author_ + " " + isbn_;
	return parseStringToWords(words);
}

string Book::displayString() const {
	string info = name_ + "\n" + "Author: " + author_ + " ISBN: " + isbn_ + "\n" + to_string(price_) + " " + to_string(qty_) + " left.";
	return info;
}

void Book::dump(std::ostream& os) const {
	os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << isbn_ << "\n" << author_ << endl;
}

string Book::getISBN() const {
	return isbn_;
}

string Book::getAuthor() const {
	return author_;
}