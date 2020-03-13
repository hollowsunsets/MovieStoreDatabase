CXX=g++
CXXFLAGS= -Wall -g -std=c++98

all: driver

driver: driver.o store.o customer.o customertable.o item.o movie.o
	$(CXX) $(CXXFLAGS) -o driver driver.o store.o customer.o customertable.o item.o movie.o

driver.o: driver.cpp
	$(CXX) $(CXXFLAGS) -c driver.cpp

store.o: store.cpp store.h customer.h customertable.h
	$(CXX) $(CXXFLAGS) -c store.cpp

item.o: item.cpp item.h
	$(CXX) $(CXXFLAGS) -c item.cpp

movie.o: movie.cpp movie.h item.cpp item.h
	$(CXX) $(CXXFLAGS) -c movie.cpp

customer.o: customer.cpp customer.h
	$(CXX) $(CXXFLAGS) -c customer.cpp

customertable.o: customertable.cpp customertable.h
	$(CXX) $(CXXFLAGS) -c customertable.cpp

clean:
	rm -f *.o driver *~
