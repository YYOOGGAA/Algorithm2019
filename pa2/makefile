GXX 	= g++
CFLAGS 	= -O3 -std=c++11 -Wall
BIN 	= mps
all:mps

$(BIN): src/main.cpp
	@$(GXX) $< -o $@ $(CFLAGS)

clean:
	@rm -f $(BIN)