CC = g++

all: pi_estimator.bin

pi_estimator.bin: main.o helpers.o
	$(CC) -o pi_estimator.bin main.o helpers.o -lpthread

main.o: main.cpp
	$(CC) -c main.cpp -lpthread

helpers.o: helpers.cpp
	$(CC) -c helpers.cpp

