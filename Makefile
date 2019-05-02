CC=g++ -std=c++17
CFLAGS=-Wall -I. -O2 -s -lsfml-graphics -lsfml-window -lsfml-system -lGL -lGLEW -pthread -lGLU
SRC=$(wildcard *.cpp) \
		$(wildcard drawables/*.cpp)
OBJ=$(SRC:.cpp=.o)

%.o: %.cpp
	$(CC) -c -o $@  $< $(CFLAGS)

prog: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
	$(MAKE) clean
clean:
	rm *.o
	rm drawables/*.o

run:
	./prog
