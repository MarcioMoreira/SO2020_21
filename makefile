BIN_dir = bin
OBJ_dir = obj
INC_dir = include
SRC_dir = src

OBJETOS = client.o memory.o process.o proxy.o server.o synchronization.o main.o

client.o = client.h memory.h main.h
main.o = memory.h synchronization.h memory-private.h process.h
memory.o = memory.h memory-private.h
process.o = process.h main.h
proxy.o = proxy.h main.h
server.o = server.h main.h
synchronization.o = synchronization.h memory.h memory-private.h

CC = gcc
CFLAGS = -Wall -I $(INC_dir)
FLAGS = -lm -lpthread -lrt 

vpath %.o $(OBJ_dir)

sovaccines: $(OBJETOS)
	$(CC) $(addprefix $(OBJ_dir)/,$(OBJETOS)) -o $(BIN_dir)/sovaccines $(FLAGS)

%.o: $(SRC_dir)/%.c $($@)
	$(CC) $(CFLAGS) -o $(OBJ_dir)/$@ -c $<

clean:
	rm -f $(OBJ_dir)/*.o
	rm -f $(BIN_dir)/sovaccines