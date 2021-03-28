OBJ_DIR = obj
SRC_DIR = src 
BIN_DIR = bin 
INC_DIR = include

OBJECTOS  = main.o client.o memory.o process.o proxy.o server.o synchronization.o

main.o = memory.h synchronization.h memory-private.h process.h
client.o = memory.h main.h
memory.o = memory-private.h
process.o = memory.h main.h
proxy.o = memory.h main.h
server.o = memory.h main.h
synchronization.o = synchronization.h

CFLAGS = -Wall -I $(INC_DIR)
FLAGS = -lm -lrt -pthread 
CC = gcc

vpath %.o $(OBJ_DIR)

sovaccines: $(OBJECTOS)
	$(CC) $(FLAGS) $(addprefix $(OBJ_DIR)/,$(OBJECTOS)) -o $(BIN_DIR)/sovaccines 

%.o: $(SRC_DIR)/%.c $($@)
	$(CC) $(CFLAGS) -o $(OBJ_DIR)/$@ -c $<

clean:
	rm -f $(OBJ_DIR)/*.o
	rm -f $(BIN_DIR)/sovaccines
