all: main test clean
main: ./src/main.cpp ./src/utils.cpp ./src/graph.h
	g++ ./src/main.cpp -o main -std=c++11
test:
	./main
clean: 
	rm -rf *.o main 
