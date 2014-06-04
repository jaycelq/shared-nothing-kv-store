CC := g++
CXXFLAGS = -g -Wall -O2 -std=c++0x
TEST_SRC := dbTest.cpp
#TEST_SRC := DBOperationGetRangeTestCaseGenerator.cpp 
#TEST_SRC += DBOperationGetTestCaseGenerator.cpp 
#TEST_SRC += DBOperationPutTestCaseGenerator.cpp
#TEST_SRC += DBTestCaseGenerator.cpp
LIB := test.a

.PHONY: all 

all: depend $(LIB)

$(LIB):$(TEST_SRC:.cpp=.o)
	ar rcs $@ $^

depend:
	$(CC) -MM $(TEST_SRC) > .depend

-include .depend

.PHONY: clean
clean:
	rm -f *.o *~ .depend
