CC=g++ -std=c++17
CFLAGS=-Wall -I. -O2 -s -lsfml-graphics -lsfml-window -lsfml-system -lGL -lGLEW -pthread
SRC=$(wildcard *.cpp)
OBJ=$(SRC:.cpp=.o)

%.o: %.cpp
	$(CC) -c -o $@  $< $(CFLAGS)

prog: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
	make clean

clean:
	rm *.o