CXX=g++
CXXFLAGS= -Wall -ggdb -O0 -std=c++98

all: driver

driver: driver.o store.o customer.o customertable.o
	$(CXX) $(CXXFLAGS) -o driver driver.o store.o customer.o customertable.o

driver.o: driver.cpp
	$(CXX) $(CXXFLAGS) -c driver.cpp

store.o: store.cpp store.h customer.h customertable.h
	$(CXX) $(CXXFLAGS) -c store.cpp

customer.o: customer.cpp customer.h
	$(CXX) $(CXXFLAGS) -c customer.cpp

customertable.o: customertable.cpp customertable.h
	$(CXX) $(CXXFLAGS) -c customertable.cpp

clean:
	rm -f *.o driver *~