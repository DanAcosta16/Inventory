//============================================================================
// Name        : Inventory.cpp
// Author      : Daniel Acosta
// Version     :
// Copyright   :
// Description : Inventory System for keeping track of orders of parts
//============================================================================

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
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
	void decrementStck(string x, int q){_stockqty -= q;}
	void increaseStck(string x, int q){_stockqty += q;}
};
class Inventory{
private:
	vector<Part*> _inv;
public:
	Inventory(){}
	Inventory(const Inventory& b);
	~Inventory();
	const Inventory& operator=(const Inventory& b);
	vector<Part*> getInv(){return _inv;}
	void addPart(string, string, int);
	bool deletePart(string);
	int partSearch(string);
	void printInventory(ostream&) const;
};
Inventory::Inventory(const Inventory& b){
	for (int i=0; i<b._inv.size(); i++){
		_inv.push_back(new Part(*(b._inv[i])));
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
	return *this;
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
int Inventory::partSearch(string p){
	for (int i = 0; i < _inv.size(); i++){
		if(_inv[i]->getPartNum() == p){
			return i;
		}
	}
	return -1;
}
void Inventory::printInventory(ostream& os) const {
	os << "\nCurrent Inventory Size: " << _inv.size() << endl;
	for (int i = 0; i < _inv.size(); i++){
		os << "Part: " << _inv[i]->getPartNum() <<
			"  Stock Quantity: " << _inv[i]->getStock() << endl;
	}
}
class Order{
private:
	string _ordnum;
	string _cnum;
	vector<string> _parts;
	vector<int> _qtys;
	bool _shipped;
public:
	Order();
	Order(string o, string c, vector<string> p, vector<int> q, bool s): _ordnum(o), _cnum(c), _parts(p), _qtys(q), _shipped(s){}
	void setOrdnum(string o){_ordnum = o;}
	void setName(string c){_cnum = c;}
	void ship(){_shipped = true;}
	bool isShipped(){return _shipped;}
	string getOrdnum(){return _ordnum;}
	string getCnum(){return _cnum;}
	string getParts(int index){return _parts[index];}
	vector<string> getPartsV(){return _parts;}
	vector<int> getQtyV(){return _qtys;}
	int getQty(int index){return _qtys[index];}
	int getSize(){return _parts.size();}
	void addPart(string p, int q){
		_parts.push_back(p);
		_qtys.push_back(q);
	}
	bool deletePart(string);
};
bool Order::deletePart(string p){
	bool found = false;
	for (int i=0; (i < _parts.size() && !found); i++){
		if(_parts[i] == p){
			found = true;
			_parts.erase(_parts.begin() + i);
			_qtys.erase(_qtys.begin() + i);
		}
	}
	return found;
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
	void setCnum(string cnum){_cnum = cnum;}
	string getCnum(){return _cnum;}
	Address getAddr(){return _addr;}
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
	void addCustomer(string, string, string, string, string);
	bool deleteCustomer(string);
	void printCustomers(ostream& os) const;
};
AllCustomers::AllCustomers(const AllCustomers& b){
	for(int i = 0; i < b._customers.size(); i++){
		_customers.push_back(new Customer(*(b._customers[i])));
	}
}
AllCustomers::~AllCustomers(){
	for(int i=0; i < _customers.size(); i++){
		delete _customers[i];
	}
}
void AllCustomers::addCustomer(string cnum, string str, string c, string s, string z){
	Customer* ptr = new Customer(cnum, str, c, s, z);
	_customers.push_back(ptr);
}
bool AllCustomers::deleteCustomer(string cnum){
	bool found = false;
	for(int i=0; (i < _customers.size() && !found); i++){
		if (_customers[i]->getCnum() == cnum){
			found = true;
			delete _customers[i];
			_customers.erase(_customers.begin() + i);
		}
	}
	return found;
}
void AllCustomers::printCustomers(ostream& os) const {
	os << "\nCurrent Customer List Size: " << _customers.size() << endl;
	for(int i = 0; i < _customers.size(); i++){
		os << "|| Customer Number: " << _customers[i]->getCnum() << "|| Street Name: " << _customers[i]->getAddr().getStreet() <<
				"|| City: " << _customers[i]->getAddr().getCity() << "|| State: " << _customers[i]->getAddr().getState() <<
				"|| Zip: " << _customers[i]->getAddr().getZip() << " ||" << endl;
	}
}
class AllOrders{
private:
	vector<Order*> _orders;
public:
	AllOrders(){}
	AllOrders(const AllOrders& b);
	~AllOrders();
	const AllOrders& operator=(const AllOrders& b);
	void addOrder(string, string, vector<string>, vector<int>, bool s);
	bool deleteOrder(string);
	void printOrders(ostream& os) const;
	int checkForOrder(string&);
	void addToOrder(int, string, int);
	bool deleteFromOrder(int, string);
	bool checkShipped(int);
	vector<Order*> getOrders(){return _orders;}
};
AllOrders::AllOrders(const AllOrders& b){
	for (int i=0; i < b._orders.size(); i++){
		_orders.push_back(new Order(*(b._orders[i])));
	}
}
AllOrders::~AllOrders(){
	for(int i=0; i < _orders.size(); i++){
		delete _orders[i];
	}
}
const AllOrders& AllOrders::operator=(const AllOrders& b){
	if(this != &b){
		for(int i=0; i < b._orders.size(); i++){
			delete b._orders[i];
		}
		for(int i=0; i < b._orders.size(); i++){
			_orders.push_back(new Order(*(b._orders[i])));
		}
	}
	return *this;
}
void AllOrders::addOrder(string o, string c, vector<string> p, vector<int> q, bool s){
	Order* ptr = new Order(o, c, p, q, s);
	_orders.push_back(ptr);
}
bool AllOrders::checkShipped(int index){
	return _orders[index]->isShipped();
}
void AllOrders::addToOrder(int index, string part, int qty){
	_orders[index]->addPart(part, qty);
}
bool AllOrders::deleteFromOrder(int index, string part){
	_orders[index]->deletePart(part);
	return true;
}
int AllOrders::checkForOrder(string& orderNum){
	cout << _orders.size();
	for(int i = 0; i < _orders.size(); i++){
		cout << _orders[i]->getOrdnum() << endl;
		if(_orders[i]->getOrdnum() == orderNum){
			return i;
		}
	}
	return -1;
}
bool AllOrders::deleteOrder(string o){
	bool found = false;
	for(int i=0; (i < _orders.size() && !found); i++){
		if(_orders[i]->getOrdnum() == o){
			found = true;
			delete _orders[i];
			_orders.erase(_orders.begin() + i);
		}
	}
	return found;
}
void AllOrders::printOrders(ostream& os) const {
	os << "\nCurrent Order List Size: " << _orders.size() << endl;
	for(int i=0; i < _orders.size(); i++){
		os << "ORDER NUMBER: " << _orders[i]->getOrdnum() << " || CUSTOMER NUMBER: " << _orders[i]->getCnum() << endl;
		for(int j = 0; j < _orders[i]->getSize(); j++){
			os << "|| Part: " << _orders[i]->getParts(j) << " Quantity: " << _orders[i]->getQty(j) << " ||" << "Shipped Status:"
					" " << _orders[i]->isShipped() << endl;
		}
		cout << "\n";
	}
}
//precondition: file and Inventory objects have been instantiated
//post: Inventory data has been loaded from file
void initializeInventory(ifstream& infile, Inventory& inv){
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
		int stock = stoi(v[2]);
		inv.addPart(v[0], v[1], stock);
		getline(infile, part);
	}
}
//precondition: file and AllCustomers objects have been instantiated
//post: AllCustomers data has been loaded from file
void initializeCustomers(ifstream& infile, AllCustomers& cust){
	string customer;
	getline(infile, customer);
	while(customer != "0, 0, 0, 0, 0"){
		vector<string> v;
		stringstream ss(customer);
		while (ss.good()) {
			string substr;
			getline(ss, substr, ',');
			v.push_back(substr);
		}
		cust.addCustomer(v[0], v[1], v[2], v[3], v[4]);
		getline(infile, customer);
	}
}
//precondition: file and AllOrders objects have been instantiated
//post: AllOrders data has been loaded from file
void initializeOrders(ifstream& infile, AllOrders& orders){
	string order;
	getline(infile, order);
	while(order != "0, 0"){
		vector<string> v;
		stringstream ss(order);
		while (ss.good()){
			string substr;
			getline(ss, substr, ',');
			v.push_back(substr);
		}
		vector<string> parts;
		vector<int> qtys;
		string contents;
		getline(infile, contents);
		while(contents != "0, 0"){
			vector<string> temp;
			stringstream ss(contents);
			while (ss.good()){
				string substr;
				getline(ss, substr, ',');
				temp.push_back(substr);
			}
			int qty = stoi(temp[1]);
			parts.push_back(temp[0]);
			qtys.push_back(qty);
			getline(infile, contents);
		}
		orders.addOrder(v[0], v[1], parts, qtys, false);
		getline(infile, order);
	}
}
//precondition: AllOrder, Inventory, and AllCustomers objects have been instantiated, user selected this option
//post: User interface that allows user to add an order or delete/modify orders that have not been shipped already
void csr(AllOrders& ord, Inventory& inv){
	int option;
	do {
		cout << "\n****CUSTOMER SERVICE REP****" << endl;
		cout << "1.Add Order\n2.Delete Order\n3.Modify Existing Order\n4.Back" << endl;
		cout << "Please enter a number 1-4: ";
		cin >> option;
		while(option < 1 || option > 4){
			cout << "\nPlease enter a number 1-4: ";
			cin >> option;
		}
		switch(option) {
		case 1 :
		{
			int qty;
			char ans;
			int index;
			string orderNum, custNum, partNum;
			vector<string> parts;
			vector<int> qtys;
			cout << "Please enter the following customer data.\nOrder Number: ";
			cin >> orderNum;
			cout << "Customer Number: ";
			cin >> custNum;
			cout << "Did the customer order parts? Y/N: ";
			cin >> ans;
			while(ans == 'Y'|| ans == 'y'){
				cout << "Part Number: ";
				cin >> partNum;
				index = inv.partSearch(partNum);
				//if index returns as -1, then it was not found
				//otherwise index is position in vector
				while(index < 0){
					cout << "Part does not exist in inventory! Please enter another part number: ";
					cin >> partNum;
					index = inv.partSearch(partNum);
				}
				parts.push_back(partNum);
				cout << "Quantity: ";
				cin >> qty;
				while(qty < 1){
					cout << "\nPlease enter a valid integer: ";
					cin >> qty;
				}
				qtys.push_back(qty);
				cout << "Is there more to the order? Y/N: ";
				cin >> ans;
				while(ans != 'Y' && ans != 'y' && ans != 'N' && ans != 'n'){
					cout << "Please enter Y or N: ";
					cin >> ans;
				}
			}
			ord.addOrder(orderNum, custNum, parts, qtys, false);
			cout << "Order added successfully!";
			break;
		}
		case 2 :
		{
			string orderNum;
			bool deleted, shipped;
			int index;
			cout << "Please enter order number of order you wish to delete: ";
			cin >> orderNum;
			index = ord.checkForOrder(orderNum);
			//if index returns as -1, then it was not found
			//otherwise index is position in vector
			if(index >= 0){
				shipped = ord.checkShipped(index);
				if(shipped){
					cout << "Cannot delete orders that have been shipped!";
				}
				else{
					deleted = ord.deleteOrder(orderNum);
					if(deleted){
						cout << "Order successfully deleted!" << endl;
					}
					else
						cout << "Error deleting order!" << endl;
				}
			}
			else
				cout << "Order not found!";
			break;
		}
		case 3 :
		{
			int option, qty, index;
			bool found, shipped;
			string orderNum, partNum;
			cout << "Please enter the order number of the order you wish to modify: ";
			cin >> orderNum;
			index = ord.checkForOrder(orderNum);
			//if index returns as -1, then it was not found
			//otherwise index is position in vector
			if(index >= 0){
				shipped = ord.checkShipped(index);
				if(shipped){
					cout << "Cannot modify orders that have been shipped!";
				}
				else{
					do{
						cout << "\n****" << orderNum << "****" << endl;
						cout << "1.Add to order\n2.Delete from order\n3.Back" << endl;
						cout << "Please enter a number 1-3: ";
						cin >> option;
						while(option < 1 || option > 3){
							cout << "Please enter a number 1-3: ";
							cin >> option;
						}
						switch(option) {
						case 1 :
						{
							cout << "Enter part number: ";
							cin >> partNum;
							cout << "Enter quantity: ";
							cin >> qty;
							while(qty < 1){
								cout << "\nPlease enter a valid integer: ";
								cin >> qty;
							}
							ord.addToOrder(index, partNum, qty);
							cout << "Part added successfully!" << endl;
						}
						case 2 :
						{
							cout << "Enter part number of the part you wish to delete: ";
							cin >> partNum;
							found = ord.deleteFromOrder(index, partNum);
							if(found){
								cout << "Part deleted from order!" << endl;
							}
							else
								cout << "Part not found!" << endl;
						}
						}
					}while(option != 3);
				}
			}
			else
				cout << "Order not found!" << endl;
			break;
		}
		}
	} while (option != 4);
}
//precondition: AllOrder, Inventory, and AllCustomers objects have been instantiated, user selected this option
//post: User interface that allows user to perfrom warehouse receiver tasks such as adding a new part to the inventory or adding to existing part quantities
void whr(Inventory& inv){
	int option;
	do{
		cout << "\n****Warehouse Receiver*****" << endl;
		cout << "1.Add new part\n2.Increase quantity\n3.Back" << endl;
		cout << "Please enter a number 1-3: ";
		cin >> option;
		while(option < 1 || option > 3){
			cout << "Please enter a number 1-3: ";
			cin >> option;
		}
		switch(option) {
		case 1 :
		{
			string partNum, desc;
			int qty;
			cout << "\nPlease enter the part number: ";
			cin >> partNum;
			cout << "Please enter part description: ";
			cin >> desc;
			cout << "Please enter quantity: ";
			cin >> qty;
			while(qty < 1){
				cout << "\nPlease enter a valid integer: ";
				cin >> qty;
			}
			inv.addPart(partNum, desc, qty);
			cout << "Part added successfully!" << endl;
			break;
		}
		case 2 :
		{
			string partNum;
			int index;
			int qty;
			cout << "Please enter part number: ";
			cin >> partNum;
			index = inv.partSearch(partNum);
			if(index >= 0){
				cout << "How much do you want to add?: ";
				cin >> qty;
				while(qty < 1){
					cout << "\nPlease enter a valid integer: ";
					cin >> qty;
				}
				inv.getInv()[index]->increaseStck(partNum, qty);
			}
			else{
				cout << "Part does not exist in inventory!" << endl;
			}
			break;
		}
		}
	}while(option != 3);
}
//precondition: AllOrder, Inventory, and AllCustomers objects have been instantiated, user selected this option
//post: User interface allowing user to perform warehouse shipper to ship orders that have not been shipped already
void whs(Inventory& inv, AllCustomers& cust, AllOrders& ord){
	string orderNum;
	int index;
	bool shipped;
	cout << "\n****Warehouse Shipper****" << endl;
	cout << "Enter the order number of the order you would like to ship: ";
	cin >> orderNum;
	index = ord.checkForOrder(orderNum);
	if(index >= 0){
		shipped = ord.checkShipped(index);
		if(shipped){
			cout << "Order already shipped!";
		}
		else{
			ord.getOrders()[index]->ship();
			for(int i = 0; i < ord.getOrders()[index]->getPartsV().size(); i++){
				string partNum;
				int qty;
				partNum = ord.getOrders()[index]->getPartsV()[i];
				qty = ord.getOrders()[index]->getQtyV()[i];
				for(int i=0; i < inv.getInv().size(); i++){
					if(partNum == inv.getInv()[i]->getPartNum()){
						inv.getInv()[i]->decrementStck(partNum, qty);
					}
				}
			}
			cout << "Order succesfully shipped!";
		}
	}
}
//precondition: AllOrder, Inventory, and AllCustomers objects have been instantiated
//post: All current object data for AllCustomers, Inventory, and AllOrders classes is displayed ot the user
void dumpData(Inventory& inv, AllCustomers& cust, AllOrders& ord){
	inv.printInventory(cout);
	cust.printCustomers(cout);
	ord.printOrders(cout);
}
//precondition: AllOrder, Inventory, and AllCustomers objects have been instantiated
//post: User interface menu is shown allowing the user to perform different tasks
void menu(Inventory& inv, AllCustomers& cust, AllOrders& ord){
	int option;
	do {
		cout << "\n****MAIN MENU****" << endl;
		cout << "1.Customer Service Rep\n2.Warehouse Reveiver\n3.Warehouse Status\n4.Dump Data\n5.Exit" << endl;
		cout << "Please enter a number 1-5: ";
		cin >> option;
		while(option > 5 || option < 1){
			cout << "\nPlease enter a numer 1-5: ";
			cin >> option;
		}
		switch(option) {
		case 1 :
			csr(ord, inv);
			break;
		case 2:
			whr(inv);
			break;
		case 3:
			whs(inv, cust, ord);
			break;
		case 4:
			dumpData(inv, cust, ord);
			break;
		}

	} while (option != 5);
}
int main() {
	ifstream infile("datafile.txt");
	if(!infile){
		cout << "Unable to get file" << endl;
		exit(-1);
	}
	Inventory invInit;
	initializeInventory(infile, invInit);

	AllCustomers custInit;
	initializeCustomers(infile, custInit);
	AllOrders ordInit;
	initializeOrders(infile, ordInit);
	menu(invInit, custInit, ordInit);
	return 0;
}
