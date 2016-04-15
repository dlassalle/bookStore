#include <cassert>
#include <stdexcept>
#include <iostream>
#include <unistd.h>
#include <string>
//======begin edit=========
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <cstddef>
#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
//========end edit=======

#include "xmlrpc-c/base.hpp"
#include "xmlrpc-c/registry.hpp"
#include "xmlrpc-c/server_abyss.hpp"
#include "xmlrpc-c/client_simple.hpp"

using namespace std;

//==========begin edit================

   sqlite3 *db;
   char *zErrMsg = 0;
   int rc;
   const char* sql;
   char data[256];
   string sql_string;
   vector<xmlrpc_c::value> arrayData;
   vector<int> quant;

static int callbackbytopic(void* data, int argc, char **argv, char **azColName) {

        arrayData.push_back(xmlrpc_c::value_int(atoi(argv[0]))); //item number
        arrayData.push_back(xmlrpc_c::value_string(argv[2])); //title
   return 0;

  return 0;
}

static int callbackbynumber(void* data, int argc, char **argv, char **azColName) {

        arrayData.push_back(xmlrpc_c::value_string(argv[2])); //title
        arrayData.push_back(xmlrpc_c::value_int(atoi(argv[1]))); //quantity
        arrayData.push_back(xmlrpc_c::value_double(atof(argv[4]))); //cost
   return 0;

  return 0;
 }

static int callbacktoupdate(void* data, int argc, char **argv, char **azColName) {

        quant.push_back(atoi(argv[1]));
   return 0;

  return 0;
 }

//===========end edit==============

class queryTopicMethod : public xmlrpc_c::method {
public:
    queryTopicMethod() {
        this->_signature = "A:s";
        this->_help = "This method takes a string topic as input, and returns an array of book items that match the topic, along with their item number. Each even numbered element of the array stores an item number and the subsequent odd numbered element of the array stores the corresponding book title for that item number.";
    }
    void
    execute(xmlrpc_c::paramList const& paramList,
            xmlrpc_c::value *   const  retvalP) {

	// Verify that the input to this function is only a single parameter
        paramList.verifyEnd(1);

	// Get the first argument to the method, which should be a string that has the topic
	string argument1 = paramList.getString(0);

//=======================SQL Query and Array Filling=====================================

   string to_sql = "SELECT * from INVENTORY WHERE TOPIC='";
   argument1.append("'");
   to_sql.append(argument1);
   sql = to_sql.c_str();
   rc = sqlite3_exec(db, sql, callbackbytopic, (void*)data, &zErrMsg);
   if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }

//================end SQL query=================================================

        // Make an XML-RPC array out of it
        xmlrpc_c::value_array return_array(arrayData);

        *retvalP = return_array;
//==============Clear Filled Array============
	arrayData.clear();
//===============end edit==========
    } catch (exception const& e) {
	cerr << "Client threw error: " << e.what() << endl;
    } catch (...) {
	cerr << "Client threw unexpected error." << endl;
    }
};

class queryItemMethod : public xmlrpc_c::method {
public:
    queryItemMethod() {
        this->_signature = "A:i";
        this->_help = "This method searches for a book title by item number, and returns a string representing the title of that book.";
    }
    void
    execute(xmlrpc_c::paramList const& paramList,
            xmlrpc_c::value *   const  retvalP) {

	// Verify that the input to this function is only a single parameter
        paramList.verifyEnd(1);

	// Get the first argument to the method, which should be an integer representing the item number
	int argument1 = paramList.getInt(0);

//================== SQL Query and Array Filling =========
   string to_sql = "SELECT * from INVENTORY WHERE ITEM_NUMBER='";
	stringstream ss;
	ss << argument1;
	string strt = ss.str();
   to_sql.append(strt);
   to_sql.append("'");
   sql = to_sql.c_str();
   rc = sqlite3_exec(db, sql, callbackbynumber, (void*)data, &zErrMsg);
   if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }
//=======================end edit=================================

        // Make an XML-RPC array out of it
        xmlrpc_c::value_array return_array(arrayData);

        *retvalP = return_array;
//================clear data===============
	arrayData.clear();
//===================end edit===========

    } catch (exception const& e) {
	cerr << "Client threw error: " << e.what() << endl;
    } catch (...) {
	cerr << "Client threw unexpected error." << endl;
    }
};


class updateMethod : public xmlrpc_c::method {
public:
    updateMethod() {
        this->_signature = "i:ii";
        this->_help = "This method changes the number of books of a specific item number by the second argument. The method returns -1 if the purchase failed, and 0 otherwise.";
    }
    void
    execute(xmlrpc_c::paramList const& paramList,
            xmlrpc_c::value *   const  retvalP) {

	int result; 

	// Verify that the input to this function is only a two parameter
        paramList.verifyEnd(2);

	// Get the first argument to the method, which should be an integer representing the book item number to decrement
	int item_number = paramList.getInt(0);
	int change = paramList.getInt(1);

//================== SQL Query and Array Filling =========
   string to_sql = "SELECT * from INVENTORY WHERE ITEM_NUMBER='";
        stringstream ss;
        ss << item_number;
        string strt = ss.str();
   to_sql.append(strt);
   to_sql.append("'");
   sql = to_sql.c_str();
   rc = sqlite3_exec(db, sql, callbacktoupdate, (void*)data, &zErrMsg);
   if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }
//================= end SQL query ==========

//check to see if quantity is okay
	int quantity = quant.back();
	if (quantity <= 0) //if quantity is too small then fail
	  result = -1;
	else { //if quantity is large enugh then go ahead and update
	  	quantity-=change;
	  	result = 0;
        	stringstream dd;
        	dd << quantity;
        	string strt2 = dd.str();
//================ SQL Update ==============
   		string to_sql = "UPDATE INVENTORY set QUANTITY='";
   		to_sql.append(strt2); //new quantity
   		to_sql.append("' WHERE ITEM_NUMBER='");
   		to_sql.append(strt); //item number
   		to_sql.append("'");
   		sql = to_sql.c_str();
   		rc = sqlite3_exec(db, sql, callbacktoupdate, (void*)data, &zErrMsg);
   		if( rc != SQLITE_OK ){
      			fprintf(stderr, "SQL error: %s\n", zErrMsg);
      			sqlite3_free(zErrMsg);
   		}
//================= end SQL ==========

	} //end up updating

	// Return the correct result to the client to indicate success or failure
        *retvalP = xmlrpc_c::value_int(result);
//===============clear array=============
	quant.clear();
//===============end edit============

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
   	rc = sqlite3_open("inventory.db", &db);
   	if( rc ){
      		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db)); 
      		exit(0);
   	}
        xmlrpc_c::registry myRegistry;

        xmlrpc_c::methodPtr const queryTopicMethodRPC(new queryTopicMethod);
        xmlrpc_c::methodPtr const queryItemMethodRPC(new queryItemMethod);
        xmlrpc_c::methodPtr const updateMethodRPC(new updateMethod);

	// Register the RPC functions we will expose on the catalog server
        myRegistry.addMethod("queryTopic.rpc", queryTopicMethodRPC);
        myRegistry.addMethod("queryItem.rpc", queryItemMethodRPC);
        myRegistry.addMethod("update.rpc", updateMethodRPC);

	// Start the catalog server; note that it runs on port 8081
        xmlrpc_c::serverAbyss myAbyssServer(
            xmlrpc_c::serverAbyss::constrOpt()
            .registryP(&myRegistry)
            .portNumber(8082));

	// Start my server; this call never returns
        myAbyssServer.run();

        assert(false);
    } catch (exception const& e) {
        cerr << "Something failed.  " << e.what() << endl;
    }
    sqlite3_close(db);
    return 0;
}
