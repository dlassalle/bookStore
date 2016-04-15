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
using namespace xmlrpc_c;
string const catalogUrl = "http://localhost:8082/RPC2";

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
//	int item_number = paramList.getInt(0);

	//===================begin edits ===========================
	
	xmlrpc_c::value result2;
        int item_number = paramList.getInt(0);
        int change = paramList.getInt(1);
	//======== TODO QUERY ==========
        int int_value;

	myClient.call(catalogUrl, "queryItem.rpc", "i", &result, item_number);

	value_array lookup_array(result);
        vector<value> const lookup_array_entries(lookup_array.vectorValueValue());
        int_value = value_int(lookup_array_entries[1]);

	if(int_value > 0){
	//======== QUANTITY GOOD ===============

		myClient.call(catalogUrl, "update.rpc", "ii", &result2, item_number, change);

        	// Get the result from the catalog server, in the form of an array
        	value_int response_array(result2);

        	// Forward the array to the client
        	*retvalP = value_int(result2);

	}
	else{
	//=========== QUANTITY BAD ===============
		*retvalP = xmlrpc_c::value_int(-1);

	}
	//====================end edits ============================


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

        xmlrpc_c::methodPtr const buyMethodRPC(new buyMethod);

	// The order server only exposes the buy RPC to the front-end server
        myRegistry.addMethod("buy.rpc", buyMethodRPC);
        
	// Configure the order server to start on port 8081
        xmlrpc_c::serverAbyss myAbyssServer(
            xmlrpc_c::serverAbyss::constrOpt()
            .registryP(&myRegistry)
            .portNumber(8081));
        
	// Start my server; this call never returns
        myAbyssServer.run();

        assert(false);
    } catch (exception const& e) {
        cerr << "Something failed.  " << e.what() << endl;
    }
    return 0;
}
