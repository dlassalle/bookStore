#include <iostream>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <cstddef>
#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h> 

using namespace std;

// void* data = pointer from the sql statement that identifies this callback
// int argc = the number of columns in each row
// char** argv = array of strings, one for each field in each row
// char** azColName = array of strings, one for each column name
static int callback(void* data, int argc, char **argv, char **azColName) {

   // fprintf(stderr, "%s: ", (const char*)data);
   for(int i=0; i<argc; i++){
      printf("%s = %s\n", azColName[i], argv[i]);
   }
   printf("\n");
   return 0;

  return 0;
 }

int main(int argc, char* argv[])
{
   sqlite3 *db;
   char *zErrMsg = 0;
   int rc;
   const char* sql;
   char data[256];
   string sql_string;  

   rc = sqlite3_open("inventory.db", &db);
   if( rc ){
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      exit(0);
   }else{
      fprintf(stderr, "Opened database successfully\n");
   }

   sql = "CREATE TABLE INVENTORY("  \
         "ITEM_NUMBER INT PRIMARY KEY NOT NULL," \
         "QUANTITY INT NOT NULL," \
	 "TITLE TEXT NOT NULL," \
	 "TOPIC TEXT NOT NULL," \
	 "COST DOUBLE NOT NULL);";
 
   rc = sqlite3_exec(db, sql, NULL, 0, &zErrMsg);
   if( rc != SQLITE_OK ){
   fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }else{
      fprintf(stdout, "Table created successfully\n");
   }

   sql_string = "INSERT INTO INVENTORY VALUES (53477, 1, 'Achieving Less Bugs in your Code', 'software systems', 19.99);";
   sql = sql_string.c_str();
   rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
   if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }else{
      fprintf(stdout, "Records created successfully\n");
   }

   sql_string = "INSERT INTO INVENTORY VALUES (53573, 2, 'Software Design for Dummies', 'software systems', 29.99);";
   sql = sql_string.c_str();
   rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
   if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }else{
      fprintf(stdout, "Records created successfully\n");
   }

   sql_string = "INSERT INTO INVENTORY VALUES (12365, 1, 'Surviving College', 'college life', 39.99);";
   sql = sql_string.c_str();
   rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
   if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }else{
      fprintf(stdout, "Records created successfully\n");
   }

   sql_string = "INSERT INTO INVENTORY VALUES (12498, 3, 'Cooking for the Impatient Undergraduate', 'college life', 49.99);";
   sql = sql_string.c_str();
   rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
   if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }else{
      fprintf(stdout, "Records created successfully\n\n");
   }

   // Example of a database query
   sql = "SELECT * from INVENTORY WHERE TOPIC='college life'";
   rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
   if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }else{
      fprintf(stdout, "Operation done successfully\n");
   }

   sqlite3_close(db);
}
