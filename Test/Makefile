CC := g++
CXXFLAGS = -g -Wall -O2 -std=c++0x
TEST_SRC := DBOperationGetRangeTestCaseGenerator.cpp 
TEST_SRC += DBOperationGetTestCaseGenerator.cpp 
TEST_SRC += DBOperationPutTestCaseGenerator.cpp
TEST_SRC += DBTestCaseGenerator.cpp

.PHONY: all 

all: depend $(TEST_SRC:.cpp=.o)

depend:
	$(CC) -MM $(TEST_SRC) > .depend

-include .depend

.PHONY: clean
clean:
	rm -f *.o *~ .depend
