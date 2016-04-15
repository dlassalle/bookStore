#include <cassert>
#include <stdexcept>
#include <iostream>
#include <unistd.h>
#include <string>

#include "xmlrpc-c/base.hpp"
#include "xmlrpc-c/registry.hpp"
#include "xmlrpc-c/server_abyss.hpp"
#include "xmlrpc-c/client_simple.hpp"

using namespace std;

string const catalogUrl = "http://localhost:8082/RPC2";
string const orderUrl = "http://localhost:8081/RPC2";

class lookupMethod : public xmlrpc_c::method {
public:
    lookupMethod() {
        this->_signature = "A:i";
        this->_help = "This method searches for a book by item number. The method returns an array that has the title of the book (as a string) in the first element, the number of items in stock for the book in the second element, and the cost of the book in the third element";
    }
    void
    execute(xmlrpc_c::paramList const& paramList,
            xmlrpc_c::value *   const  retvalP) {

	// Client stub to act as a client to the XML-RPC call to the catalog server
	xmlrpc_c::clientSimple myClient;

	// Variable for storing the result from the server
        xmlrpc_c::value result;

	// Verify that the input to this function is only a single parameter
        paramList.verifyEnd(1);

	// Get the first argument to the method, which should be a string
	int item_number = paramList.getInt(0);

	// Call catalog server to query for this topic; send it one string as the query topic
	myClient.call(catalogUrl, "queryItem.rpc", "i", &result, item_number);

	// Get the result from the catalog server, in the form of an array
        xmlrpc_c::value_array response_array(result);

	// Forward the array to the client
        *retvalP = response_array;

    } catch (exception const& e) {
	cerr << "Client threw error: " << e.what() << endl;
    } catch (...) {
	cerr << "Client threw unexpected error." << endl;
    }
};


class searchMethod : public xmlrpc_c::method {
public:
    searchMethod() {
        this->_signature = "A:s";
        this->_help = "This method searches for a topic by string. The method returns an array to the client, such that the even-numbered elements of the array specify an item number and the following odd element of the array specifies an item's title.";
    }
    void
    execute(xmlrpc_c::paramList const& paramList,
            xmlrpc_c::value *   const  retvalP) {

	// Client stub to act as a client to the XML-RPC call to the catalog server
	xmlrpc_c::clientSimple myClient;

	// Variable for storing the result from the server
        xmlrpc_c::value result;

	// Verify that the input to this function is only a single parameter
        paramList.verifyEnd(1);

	// Get the first argument to the method, which should be a string
	string argument1 = paramList.getString(0);

	// Call catalog server to query for this topic; send it one string as the query topic
	myClient.call(catalogUrl, "queryTopic.rpc", "s", &result, argument1.c_str());        

	// Get the result from the catalog server, in the form of an array
        xmlrpc_c::value_array response_array(result);

	// Forward the array to the client
        *retvalP = response_array;

    } catch (exception const& e) {
	cerr << "Client threw error: " << e.what() << endl;
    } catch (...) {
	cerr << "Client threw unexpected error." << endl;
    }
};


class buyMethod : public xmlrpc_c::method {
public:
    buyMethod() {
        this->_signature = "i:ii";
        this->_help = "This method buys a book specified by an item number. The method returns -1 if the purchase failed, and 0 otherwise.";
    }
    void
    execute(xmlrpc_c::paramList const& paramList,
            xmlrpc_c::value *   const  retvalP) {

	// Client stub to act as a client to the XML-RPC call to the catalog server
	xmlrpc_c::clientSimple myClient;

	// Variable for storing the result from the server
        xmlrpc_c::value result;

	// Verify that the input to this function is only a single parameter
        paramList.verifyEnd(2);

	// Get the first argument to the method, which should be a string
	int argument1 = paramList.getInt(0);
	int argument2 = paramList.getInt(1);

	// XXX
	// XXX CODE CURRENTLY CALLS THE CATALOG SERVER DIRECTLY TO PURCHASE AN ITEM
	// XXX YOU SHOULD MODIFY THE CODE TO CALL THE ORDER SERVER TO BUY A BOOK
	// XXX AND MODIFY THE ORDER SERVER TO SUPPORT BUYING BOOKS
	myClient.call(orderUrl, "buy.rpc", "ii", &result, argument1, argument2);
	// XXX

	// Get the result from the catalog server, in the form of an array
        xmlrpc_c::value_int response_array(result);

	// Forward the array to the client
        *retvalP = xmlrpc_c::value_int(result);

    } catch (exception const& e) {
	cerr << "Client threw error: " << e.what() << endl;
    } catch (...) {
	cerr << "Client threw unexpected error." << endl;
    }
};


int 
main(int           const, 
     const char ** const) {

    try {
        xmlrpc_c::registry myRegistry;

        xmlrpc_c::methodPtr const searchMethodRPC(new searchMethod);
        xmlrpc_c::methodPtr const lookupMethodRPC(new lookupMethod);
        xmlrpc_c::methodPtr const buyMethodRPC(new buyMethod);

	// Expose the search and buy functions to end clients
        myRegistry.addMethod("search.rpc", searchMethodRPC);
        myRegistry.addMethod("lookup.rpc", lookupMethodRPC);
        myRegistry.addMethod("buy.rpc", buyMethodRPC);

	// Start the server; note that we run the frontend server on port 8080        
        xmlrpc_c::serverAbyss myAbyssServer(
            xmlrpc_c::serverAbyss::constrOpt()
            .registryP(&myRegistry)
            .portNumber(8080));
        
	// Start my server; this call never returns
        myAbyssServer.run();

        assert(false);
    } catch (exception const& e) {
        cerr << "Something failed.  " << e.what() << endl;
    }
    return 0;
}
