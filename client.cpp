#include <cstdlib>
#include <string>
#include <iostream>
#include <xmlrpc-c/girerr.hpp>
#include <xmlrpc-c/base.hpp>
#include <xmlrpc-c/client_simple.hpp>

using namespace std;
using namespace xmlrpc_c;

string const frontendUrl = "http://localhost:8080/RPC2";

void search(string topic) {
	int size, i;
        clientSimple myClient;
        value result;
	int int_value, int_value2;
	string string_value;

	cout << "Searching for books with the topic '" << topic << "'." << endl;
        myClient.call(frontendUrl, "search.rpc", "s", &result, topic.c_str());
        value_array search_array(result);
        vector<value> const search_array_entries(search_array.vectorValueValue());
	size = search_array_entries.size();
	if ((size % 2) != 0) {
	   cout << "Error: incorrect number of results returned. Exiting." << endl;
	   exit(1);
	}
	cout << "Search for books returned " << (size/2) << " results." << endl;
	for (i = 0; i < size; i+=2) {
	   int_value = value_int(search_array_entries[i]);
	   string_value = value_string(search_array_entries[i+1]);
	   cout << (i/2+1) << " Book title is " << string_value << " and its item number is " << int_value << endl;
	}
	cout << endl;
}

void buy(int item_number) {
        clientSimple myClient;
        value result;
	int int_value;
	int change = 1;

	cout << "Buying book with item number " << item_number << endl;
        myClient.call(frontendUrl, "buy.rpc", "ii", &result, item_number, change);
	int_value = value_int(result);
	if (int_value == 0) {
	  cout << "Book purchase successful!" << endl;
	} else {
	  cout << "Book purchase failed. Please check that the quantity is not 0." << endl;
	}
	cout << endl;
}

void lookup(int item_number) {
	int size, i, int_value;
	double double_value;
        clientSimple myClient;
        value result;
	string string_value;

	cout << "Looking up book title with item number " << item_number << endl;
        myClient.call(frontendUrl, "lookup.rpc", "i", &result, item_number);
        value_array lookup_array(result);
        vector<value> const lookup_array_entries(lookup_array.vectorValueValue());
	size = lookup_array_entries.size();
	if (size != 3) {
	   cout << "Error: incorrect number of results returned. Exiting." << endl;
	   exit(1);
	}
	cout << "Lookup for book with item number " << item_number << " returned the following information." << endl;
	string_value = value_string(lookup_array_entries[0]);
	int_value = value_int(lookup_array_entries[1]);
	double_value = value_double(lookup_array_entries[2]);
	cout << "Title: " << string_value << " Quantity in Stock: " << int_value << " Cost: " << double_value << endl;
	cout << endl;
	return;
}


int main(int argc, char **) {
    int item_number;

    try {
// XXX 
// XXX UNCOMMENT ALL LINES BELOW
//
	search("college life");
	search("software systems");

	item_number = 53477;
	lookup(item_number);
	buy(item_number);
	buy(item_number);
	lookup(item_number);

	item_number = 53573;
	lookup(item_number);
	buy(item_number);
	lookup(item_number);

	item_number = 12365;
	lookup(item_number);
	buy(item_number);
	lookup(item_number);

	item_number = 12498;
	lookup(item_number);
	buy(item_number);
	lookup(item_number);
    } catch (exception const& e) {
        cerr << "Client threw error: " << e.what() << endl;
    } catch (...) {
        cerr << "Client threw unexpected error." << endl;
    }

    return 0;
}
