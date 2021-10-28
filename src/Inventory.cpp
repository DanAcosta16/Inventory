//============================================================================
// Name        : Inventory.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <typeinfo>
using namespace std;

class Part{
private:
	string _partnum;
	int _stockqty;
	string _desc;
public:
	Part(){}
	Part(string p, string d, int s): _partnum(p), _stockqty(s), _desc(d){}
	void setPartNum(string p){_partnum = p;}
	string getPartNum() const {return _partnum;}
	void setStock(int s){_stockqty = s;}
	int getStock() const {return _stockqty;}
	void setDesc(string d){_desc = d;}
	string getDesc() const {return _desc;}
};

class Inventory{
private:
	vector<Part*> _inv;
public:
	Inventory(){}
	Inventory(const Inventory& b);
	~Inventory();
	const Inventory& operator=(const Inventory& b);
	void addPart(string, string, int);
	bool deletePart(string);
	void printInventory(ostream&) const;
	// need to write copy constructor and overloaded assignment operator
};

Inventory::Inventory(const Inventory& b){
	for (int i=0; i<b._inv.size(); i++){
		_inv.push_back(new Part(*(b._inv[i])));
	//	_inv.push_back(new Part(b._inv[i]->getPartNum(), b._inv[i]->getStock()));
	}
}
Inventory::~Inventory(){
	for (int i=0; i<_inv.size(); i++){
		delete _inv[i];
	}
}
const Inventory& Inventory::operator=(const Inventory& b){
	if(this != &b){
		for(int i = 0; i < b._inv.size(); i++){
			delete b._inv[i];
		}
		for(int i = 0; i < b._inv.size(); i++){
			_inv.push_back(new Part(*(b._inv[i])));
		}

	}
}

void Inventory::addPart(string p, string d, int s){
	Part* ptr = new Part(p, d, s);
	_inv.push_back(ptr);
}

bool Inventory::deletePart(string p){
	bool found = false;
	for (int i=0; (i < _inv.size() && !found); i++){
		if (_inv[i]->getPartNum() == p){
			found = true;
			delete _inv[i];
			_inv.erase(_inv.begin()+i);
		}
	}
	return found;
}

void Inventory::printInventory(ostream& os) const {
	os << "\nCurrent Inventory File" << endl;
	os << _inv.size() << endl;
	for (int i = 0; i < _inv.size(); i++){
		os << "Part: " << _inv[i]->getPartNum() <<
			"  Stock Qty: " << _inv[i]->getStock() << endl;
		//os << &(*_inv[i]) << endl;  -or-
		//os << _inv[i] << endl;
		os << &(_inv[i]) << endl;
	}
}

class Order{
private:
	int _ordnum;
	string _cname;
	vector<string> _parts;
	vector<int> _qtys;
public:
	Order();
	void setOrdnum(int o){_ordnum = o;}
	void setName(string c){_cname = c;}
	int getOrdnum(){return _ordnum;}
	string getName(){return _cname;}
	void addPart(string p, int q){
		_parts.push_back(p);
		_qtys.push_back(q);
	}
	void print(ofstream&);
};
void Order::print(ofstream& os){

}

class Address{
private:
	string _street;
	string _city;
	string _state;
	string _zip;
public:
	Address(){}
	Address(string str, string c, string s, string z): _street(str), _city(c), _state(s), _zip(z){}
	void setStreet(string str){_street = str;}
	void setCity(string c){_city = c;}
	void setState(string s){_state = s;}
	void setZip(string z){_zip = z;}
	string getStreet(){return _street;}
	string getCity(){return _city;}
	string getState(){return _state;}
	string getZip(){return _zip;}
};

class Customer{
private:
	string _cnum;
	Address _addr;
public:
	Customer(){}
	Customer(string cnum, string str, string c, string s, string z);
	void setAddress(Address adr){_addr = adr;}
	void setCnum(string cnum){_cnum = cnum;}
	Address getAddress(){return _addr;}
	string getCnum(){return _cnum;}
};

Customer::Customer(string cnum, string str, string c, string s, string z){
	_cnum = cnum;
	_addr.setStreet(str);
	_addr.setCity(c);
	_addr.setState(s);
	_addr.setZip(z);
}
class AllCustomers{
private:
	vector<Customer*> _customers;
public:
	AllCustomers(){}
	AllCustomers(const AllCustomers& b);
	~AllCustomers();
	const AllCustomers& operator=(const AllCustomers& b);
	void addCustomer(int, string, string, string, int);
	bool deleteCustomer(int);
};

AllCustomers::AllCustomers(const AllCustomers& b){
	for(int i = 0; i < b._customers.size(); i++){
		_customers.push_back(new Customer(*(b._customers[i])));
	}
}

class AllOrders{
private:
	vector<Order*> _orders;
public:

};

void initializeData(ifstream& infile, Inventory& inv){
	string part;
	getline(infile, part);
	while(part != "0, 0, 0"){
		vector<string> v;
		stringstream ss(part);
		while (ss.good()) {
			string substr;
			getline(ss, substr, ',');
			v.push_back(substr);
		}
		string p = v[2];
		stringstream toInt(p);
		int partStock = 0;
		toInt >> partStock;
		inv.addPart(v[0], v[1], partStock);
		getline(infile, part);
	}
}


int main() {
	ifstream infile("datafile.txt");
	if(!infile){
		cout << "Unable to get file" << endl;
		exit(-1);
	}
	Inventory init;
	initializeData(infile, init);
	return 0;
}
