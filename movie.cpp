#include <sstream>
#include <iomanip>
#include "movie.h"

using namespace std;

Movie::Movie(const std::string category, const std::string name, double price, int qty, string genre, string rating)
: Product(category, name, price, qty), genre_(genre), rating_(rating) {

}

set<string> Movie::keywords() const {
	string words = name_ + " " + genre_;
	return parseStringToWords(words);
}

string Movie::displayString() const {
	string info = name_ + "\n" + "Genre: " + genre_ + " Rating: " + rating_ + "\n" + to_string(price_) + " " + to_string(qty_) + " left.";
	return info;
}

void Movie::dump(std::ostream& os) const {
	os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << genre_ << "\n" << rating_ << endl;
}

string Movie::getGenre() const {
	return genre_;
}

string Movie::getRating() const {
	return rating_;
}