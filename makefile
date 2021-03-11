OBJ_DIR = obj
SRC_DIR = src 
BIN_DIR = bin 
INC_DIR = inc 

OBJECTOS  = main.o client.o memory-private.o memory.o process.o proxy.o server.o synchronization.o
main.o = main.c memory.h synchronization.h
client.o = client.c memory.h main.h
memory-private.o = memory-private.c
memory.o = memory.c memory-private.h
process.o = process.c memory.h main.h
proxy.o = proxy.c memory.h main.h
server.o = server.c memory.h main.h
synchronization.o = synchronization.c semaphore.h

CC = gcc

vpath %.o $(OBJ_DIR)

sovaccines: $(OBJECTOS)
	$(CC) $(addprefix $(OBJ_DIR)/, $(OBJECTOS)) -o $(BIN_DIR)/$@

%.o: $(SRC_DIR)/%.c $($@)
	$(CC) -I $(INC_DIR) -o $(OBJ_DIR)/$@ -c $<

clean:
	rm -f $(OBJ_DIR)/*.o
	rm -f $(BIN_DIR)/sovaccines