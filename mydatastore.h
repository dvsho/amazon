#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include <string>
#include <set>
#include <vector>
#include <deque>
#include <map>
#include <utility>
#include "product.h"
#include "user.h"
#include "datastore.h"

class MyDataStore : public DataStore {
	public:
		MyDataStore();
		~MyDataStore();
		void addProduct(Product* p);
		void addUser(User* u);
		std::vector<Product*> search(std::vector<std::string>& terms, int type);
		void dump(std::ostream& ofile);
		void addToCart(std::string username, Product* hit);
		void viewCart(std::string username);
		void buyCart(std::string username);
	
	private:
    std::set<Product*> products;
    std::set<User*> users;
		std::map<std::string, std::set<Product*>> searchEngine;
    std::deque<std::pair<std::string, Product*>> cart;
};

#endif