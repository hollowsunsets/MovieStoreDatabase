CXX=g++
CXXFLAGS= -Wall -g -std=c++98

all: driver

driver: driver.o store.o
	$(CXX) $(CXXFLAGS) -o driver driver.o store.o

driver.o: driver.cpp store.h
	$(CXX) $(CXXFLAGS) -c driver.cpp

store.o:
	$(CXX) $(CXXFLAGS) -c store.h store.cpp


clean:
	rm -f *.o driver *~