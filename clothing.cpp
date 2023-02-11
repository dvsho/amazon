#include <sstream>
#include <iomanip>
#include "clothing.h"

using namespace std;

Clothing::Clothing(const std::string category, const std::string name, double price, int qty, string size, string brand)
: Product(category, name, price, qty), size_(size), brand_(brand) {

}

set<string> Clothing::keywords() const {
	string words = name_ + " " + brand_;
	return parseStringToWords(words);
}

string Clothing::displayString() const {
	string info = name_ + "\n" + "Size: " + size_ + " Brand: " + brand_ + "\n" + to_string(price_) + " " + to_string(qty_) + " left.";
	return info;
}

void Clothing::dump(std::ostream& os) const {
	os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << size_ << "\n" << brand_ << endl;
}

string Clothing::getSize() const {
	return size_;
}

string Clothing::getBrand() const {
	return brand_;
}