CC=g++
DEBUG=-g
CFLAGS=$(DEBUG) -c
DB_SOURCE=initialize_db.cpp
DB_EXECUTABLE=initialize_db

ORDER_SOURCE=order_server.cpp
ORDER_INCLUDE=-I. -I./include -I./include
ORDER_LIB=./lib/libxmlrpc_client++.a ./lib/libxmlrpc_client.a -lcurl ./lib/libxmlrpc_packetsocket.a -L/usr/lib/i386-linux-gnu ./lib/libxmlrpc_server_abyss++.a ./lib/libxmlrpc_server++.a ./lib/libxmlrpc_server_abyss.a ./lib/libxmlrpc_server.a ./lib/libxmlrpc_abyss.a -lpthread ./lib/libxmlrpc++.a ./lib/libxmlrpc.a ./lib/libxmlrpc_util.a ./lib/libxmlrpc_xmlparse.a ./lib/libxmlrpc_xmltok.a
ORDER_EXECUTABLE=order_server

CATALOG_SOURCE=catalog_server.cpp
CATALOG_INCLUDE=-I. -I./include -I./include
CATALOG_LIB=./lib/libxmlrpc_server_abyss++.a ./lib/libxmlrpc_server++.a ./lib/libxmlrpc_server_abyss.a ./lib/libxmlrpc_server.a ./lib/libxmlrpc_abyss.a -lpthread ./lib/libxmlrpc++.a ./lib/libxmlrpc.a ./lib/libxmlrpc_util.a ./lib/libxmlrpc_xmlparse.a ./lib/libxmlrpc_xmltok.a -lsqlite3
CATALOG_EXECUTABLE=catalog_server

FRONTEND_SOURCE=frontend_server.cpp
FRONTEND_INCLUDE=-I. -I./include -I./include
FRONTEND_LIB=./lib/libxmlrpc_client++.a ./lib/libxmlrpc_client.a -lcurl ./lib/libxmlrpc_packetsocket.a -L/usr/lib/i386-linux-gnu ./lib/libxmlrpc_server_abyss++.a ./lib/libxmlrpc_server++.a ./lib/libxmlrpc_server_abyss.a ./lib/libxmlrpc_server.a ./lib/libxmlrpc_abyss.a -lpthread ./lib/libxmlrpc++.a ./lib/libxmlrpc.a ./lib/libxmlrpc_util.a ./lib/libxmlrpc_xmlparse.a ./lib/libxmlrpc_xmltok.a
FRONTEND_EXECUTABLE=frontend_server

CLIENT_SOURCE=client.cpp
CLIENT_INCLUDE=-I. -I./include -I./include 
CLIENT_LIB=./lib/libxmlrpc_client++.a ./lib/libxmlrpc_client.a ./lib/libxmlrpc++.a ./lib/libxmlrpc.a ./lib/libxmlrpc_util.a ./lib/libxmlrpc_xmlparse.a ./lib/libxmlrpc_xmltok.a  -L/usr/lib/i386-linux-gnu -lcurl ./lib/libxmlrpc_packetsocket.a
CLIENT_EXECUTABLE=client

all: $(CLIENT_SOURCE) $(ORDER_SOURCE) $(CATALOG_SOURCE) $(FRONTEND_SOURCE) $(DB_SOURCE) $(DB_EXECUTABLE) $(CLIENT_EXECUTABLE) $(ORDER_EXECUTABLE) $(CATALOG_EXECUTABLE) $(FRONTEND_EXECUTABLE)

$(ORDER_EXECUTABLE): 
	$(CC) $(CFLAGS) $(ORDER_INCLUDE) $@.cpp -o $@.o
	$(CC) -o $@ $@.o $(ORDER_LIB)

$(CATALOG_EXECUTABLE): 
	$(CC) $(CFLAGS) $(CATALOG_INCLUDE) $@.cpp -o $@.o
	$(CC) -o $@ $@.o $(CATALOG_LIB)

$(FRONTEND_EXECUTABLE): 
	$(CC) $(CFLAGS) $(FRONTEND_INCLUDE) $@.cpp -o $@.o
	$(CC) -o $@ $@.o $(FRONTEND_LIB)

$(CLIENT_EXECUTABLE): 
	$(CC) $(CFLAGS) $(CLIENT_INCLUDE) $@.cpp -o $@.o
	$(CC) $@.o $(CLIENT_LIB) -o $@

$(DB_EXECUTABLE):
	$(CC) $@.cpp -lsqlite3 -o $@
	
clean:
	rm -rf *.o $(CLIENT_EXECUTABLE) $(CATALOG_EXECUTABLE) $(ORDER_EXECUTABLE) $(FRONTEND_EXECUTABLE) $(DB_EXECUTABLE) inventory.db

