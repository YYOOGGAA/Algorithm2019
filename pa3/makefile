# CC and CFLAGS are varilables
CC = g++
CFLAGS = -c
OPTFLAGS = -O3

all	: cb
	@echo -n ""

# optimized version
cb			: node_mgr_opt.o main_opt.o 
			$(CC) $(OPTFLAGS) node_mgr_opt.o main_opt.o -o cb
main_opt.o 	   	: src/main.cpp src/node.h src/nodeMgr.h src/heap.h
			$(CC) $(CFLAGS) $< -o $@
node_mgr_opt.o	: src/nodeMgr.cpp src/nodeMgr.h src/heap.h src/node.h
			$(CC) $(CFLAGS) $(OPTFLAGS) $< -o $@



# clean all the .o and executable files
clean:
		rm -rf *.o cb