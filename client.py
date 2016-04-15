#Python Version of C++ Client.cpp


import xmlrpclib

# Create an object to represent our server.
server_url = 'http://localhost:8080/RPC2';
server = xmlrpclib.Server(server_url);

#        search("college life");
print "Searching for books with the topic 'college life'."

result = server.search.rpc("college life");
print "Search for books returned", (len(result)/2), "results."
for i in range(0,len(result),2):
	print (i/2+1), "Book title is", result[i+1], "and its item number is", result[i]
print
#        search("software systems");
print "Searching for books with the topic 'software systems'."

result = server.search.rpc("software systems");
print "Search for books returned", (len(result)/2), "results."
for i in range(0,len(result),2):
        print (i/2+1), "Book title is", result[i+1], "and its item number is", result[i]
print
#	 item_number = 53477;
item_number = 53477;
#        lookup(item_number);
print "Looking up book title with item number", item_number
result = server.lookup.rpc(item_number);
print "Lookup for book with item number", item_number, "returned the following information."
string_value = result[0];
int_value = result[1];
double_value = result[2];
print "Title:", string_value, "Quantity in Stock:", int_value, "Cost:", double_value
print
#        buy(item_number);
change = 1
print "Buying book with item number", item_number
result = server.buy.rpc(item_number,change);
if result == 0:
	print "Book purchase successful!"
else:
	print "Book purchase failed. Please check that the quantity is not 0."
print
#        buy(item_number);
change = 1
print "Buying book with item number", item_number
result = server.buy.rpc(item_number,change);
if result == 0:
        print "Book purchase successful!"
else:
        print "Book purchase failed. Please check that the quantity is not 0."
print
#        lookup(item_number);
print "Looking up book title with item number", item_number
result = server.lookup.rpc(item_number);
print "Lookup for book with item number", item_number, "returned the following information."
string_value = result[0];
int_value = result[1];
double_value = result[2];
print "Title:", string_value, "Quantity in Stock:", int_value, "Cost:", double_value
print
#       item_number = 53573;
item_number = 53573;
#       lookup(item_number);
print "Looking up book title with item number", item_number
result = server.lookup.rpc(item_number);
print "Lookup for book with item number", item_number, "returned the following information."
string_value = result[0];
int_value = result[1];
double_value = result[2];
print "Title:", string_value, "Quantity in Stock:", int_value, "Cost:", double_value
print
#       buy(item_number);
change = 1
print "Buying book with item number", item_number
result = server.buy.rpc(item_number,change);
if result == 0:
        print "Book purchase successful!"
else:
        print "Book purchase failed. Please check that the quantity is not 0."
print
#       lookup(item_number);
print "Looking up book title with item number", item_number
result = server.lookup.rpc(item_number);
print "Lookup for book with item number", item_number, "returned the following information."
string_value = result[0];
int_value = result[1];
double_value = result[2];
print "Title:", string_value, "Quantity in Stock:", int_value, "Cost:", double_value
print

#       item_number = 12365;
item_number = 12365;
#       lookup(item_number);
print "Looking up book title with item number", item_number
result = server.lookup.rpc(item_number);
print "Lookup for book with item number", item_number, "returned the following information."
string_value = result[0];
int_value = result[1];
double_value = result[2];
print "Title:", string_value, "Quantity in Stock:", int_value, "Cost:", double_value
print
#       buy(item_number);
change = 1
print "Buying book with item number", item_number
result = server.buy.rpc(item_number,change);
if result == 0:
        print "Book purchase successful!"
else:
        print "Book purchase failed. Please check that the quantity is not 0."
print 
#       lookup(item_number);
print "Looking up book title with item number", item_number
result = server.lookup.rpc(item_number);
print "Lookup for book with item number", item_number, "returned the following information."
string_value = result[0];
int_value = result[1];
double_value = result[2];
print "Title:", string_value, "Quantity in Stock:", int_value, "Cost:", double_value
print

#       item_number = 12498;
item_number = 12498;
#       lookup(item_number);
print "Looking up book title with item number", item_number
result = server.lookup.rpc(item_number);
print "Lookup for book with item number", item_number, "returned the following information."
string_value = result[0];
int_value = result[1];
double_value = result[2];
print "Title:", string_value, "Quantity in Stock:", int_value, "Cost:", double_value
print
#       buy(item_number);
change = 1
print "Buying book with item number", item_number
result = server.buy.rpc(item_number,change);
if result == 0:
        print "Book purchase successful!"
else:
        print "Book purchase failed. Please check that the quantity is not 0."
print
#       lookup(item_number);
print "Looking up book title with item number", item_number
result = server.lookup.rpc(item_number);
print "Lookup for book with item number", item_number, "returned the following information."
string_value = result[0];
int_value = result[1];
double_value = result[2];
print "Title:", string_value, "Quantity in Stock:", int_value, "Cost:", double_value
print
