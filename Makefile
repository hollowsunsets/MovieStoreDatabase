CXX=g++
CXXFLAGS= -Wall -ggdb -O0 -std=c++98

all: driver

driver: driver.o store.o customer.o customertable.o item.o movie.o itemfactory.o transaction.o transactionfactory.o
	$(CXX) $(CXXFLAGS) -o driver driver.o store.o customer.o customertable.o item.o movie.o itemfactory.o transaction.o transactionfactory.o

driver.o: driver.cpp
	$(CXX) $(CXXFLAGS) -c driver.cpp

store.o: store.cpp store.h customer.h customertable.h
	$(CXX) $(CXXFLAGS) -c store.cpp

itemfactory.o: itemfactory.cpp itemfactory.h item.h movie.h
	$(CXX) $(CXXFLAGS) -c itemfactory.cpp

item.o: item.cpp item.h
	$(CXX) $(CXXFLAGS) -c item.cpp

movie.o: movie.cpp movie.h item.cpp item.h
	$(CXX) $(CXXFLAGS) -c movie.cpp

customer.o: customer.cpp customer.h
	$(CXX) $(CXXFLAGS) -c customer.cpp

customertable.o: customertable.cpp customertable.h
	$(CXX) $(CXXFLAGS) -c customertable.cpp

transactionfactory.o: transactionfactory.cpp transactionfactory.h transaction.h
	$(CXX) $(CXXFLAGS) -c transactionfactory.cpp

transaction.o: transaction.cpp transaction.h
	$(CXX) $(CXXFLAGS) -c transaction.cpp

clean:
	rm -f *.o driver *~
