#include <sstream>
#include <iomanip>
#include "mydatastore.h"
#include "product_parser.h"
#include "util.h"

using namespace std;

MyDataStore::MyDataStore() {

}

MyDataStore::~MyDataStore() {
	for (set<Product*>::iterator it = products.begin(); it != products.end(); ++it) {
		delete *it;
	}

	for (set<User*>::iterator it = users.begin(); it != users.end(); ++it) {
		delete *it;
	}
}

void MyDataStore::addProduct(Product* p) {
	products.insert(p);
	set<string> currKeywords = p->keywords();
	for (set<string>::iterator it = currKeywords.begin(); it != currKeywords.end(); ++it) {
		if (searchEngine.find(*it) == searchEngine.end()) {
			set<Product*> emptySet;
			searchEngine.insert(pair<string, set<Product*>>(*it, emptySet));
		}

		searchEngine[*it].insert(p);
	}
}

void MyDataStore::addUser(User* u) {
	users.insert(u);
}

vector<Product*> MyDataStore::search(vector<string>& terms, int type) {
	set<Product*> matches;
	set<string> t(terms.begin(), terms.end());
	if (terms.size() == 1) {
		if (searchEngine.find(terms[0]) != searchEngine.end())
			copy(searchEngine[terms[0]].begin(), searchEngine[terms[0]].end(), inserter(matches, matches.end()));
	}

	else if (type == 0) {
		bool atLeastOne = false;
		for (set<string>::iterator it = t.begin(); it != t.end(); ++it) {
			if (atLeastOne)
				matches = setIntersection(matches, searchEngine[*it]);

			if (!atLeastOne && searchEngine.find(*it) != searchEngine.end()) {
				matches = searchEngine[*it];
				atLeastOne = true;
			}
		}
	}

	else if (type == 1) {
		for (set<string>::iterator it = t.begin(); it != t.end(); ++it) {
			if (searchEngine.find(*it) != searchEngine.end()) {
				set<Product*> uni = setUnion(matches, searchEngine[*it]);
				matches.insert(uni.begin(), uni.end());
			}
		}
	}

	vector<Product*> tbr(matches.size());
	copy(matches.begin(), matches.end(), tbr.begin());
	return tbr;
}

void MyDataStore::dump(ostream& ofile) {
	ofile << "<products>" << endl;
	for (set<Product*>::iterator it = products.begin(); it != products.end(); ++it) {
		(*it)->dump(ofile);
	}
	
	ofile << "</products>\n<users>" << endl;
	for (set<User*>::iterator it2 = users.begin(); it2 != users.end(); ++it2) {
		(*it2)->dump(ofile);
	}

	ofile << "</users>" << endl;
}

void MyDataStore::addToCart(string username, Product* hit) {
	bool exists = false;
	username = convToLower(username);
	for (set<User*>::iterator it = users.begin(); it != users.end(); ++it) {
		if ((*it)->getName() == username) {
			exists = true;
			break;
		}
	}

	if (!exists) {
		cout << "Invalid request" << endl;
		return;
	}

	pair<string, Product*> p;
	p = make_pair(username, hit);
	cart.push_back(p);
}

void MyDataStore::viewCart(string username) {
	bool exists = false;
	username = convToLower(username);
	for (set<User*>::iterator it = users.begin(); it != users.end(); ++it) {
		if ((*it)->getName() == username) {
			exists = true;
			break;
		}
	}

	if (!exists) {
		cout << "Invalid username" << endl;
		return;
	}

	int no = 1;
	for (size_t i = 0; i < cart.size(); ++i) {
		if (cart[i].first == username) {
			cout << "Item " << no << endl;
			cout << cart[i].second->displayString() << endl;
			++no;
		}
	}
}

void MyDataStore::buyCart(string username) {
	bool exists = false;
	User* curr;
	username = convToLower(username);
	for (set<User*>::iterator it = users.begin(); it != users.end(); ++it) {
		if ((*it)->getName() == username) {
			exists = true;
			curr = *it;
			break;
		}
	}

	if (!exists) {
		cout << "Invalid username" << endl;
		return;
	}

	size_t ogSize = cart.size();
	vector<int> tbe;
	for (size_t i = 0; i < ogSize; ++i) {
		if (cart[i].first == username) {
			if (cart[i].second->getQty() > 0 && cart[i].second->getPrice() <= curr->getBalance()) {
				cart[i].second->subtractQty(1);
				curr->deductAmount(cart[i].second->getPrice());
				tbe.push_back(i);
			}
		}
	}

	int nte = 0;
	for (size_t i = 0; i < tbe.size(); ++i) {
		cart.erase(cart.begin() + tbe[i] - nte++);
	}
}