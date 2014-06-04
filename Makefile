PROGS := dbserver dbclient
CC := g++
CXXFLAGS = -g -Wall -O2

PROTO := transaction.proto
SRC := transaction.cpp dbcoordinator.cpp dbworker.cpp BPlusTree.cpp
PROTO_BUF_SRC := transaction.pb.cc
PROTO_BUF_HEADER := transaction.pb.h

OBJ := $(SRC:.cpp=.o)
OBJ += $(PROTO_BUF_SRC:.cc=.o)

PROGS_SRC := $(addsuffix .cpp, $(PROGS))

XMLRPC_C_CONFIG = xmlrpc-c-config

XMLRPC_INCLUDES = $(shell $(XMLRPC_C_CONFIG) c++2 abyss-server client --cflags)
XMLRPC_LIBS = $(shell $(XMLRPC_C_CONFIG) c++2 abyss-server client --libs)
PROTO_BUF_INCLUDES := `pkg-config --cflags protobuf`
PROTO_BUF_LIBS := `pkg-config --libs protobuf`
TESTDIRS := Test
TESTLIBS := Test/test.a

all: depend test $(PROGS)
.PHONY: all

$(PROTO_BUF_SRC): $(PROTO)
	protoc --cpp_out=. $(PROTO)


depend: $(PROTO_BUF_SRC) 
	$(CC) -MM $(SRC) $(PROTO_BUF_SRC) $(PROGS_SRC) > .depend

test:	
	$(MAKE) -C $(TESTDIRS)

-include .depend

$(PROGS):%: %.o $(OBJ) $(TESTLIBS)
	g++ -o $@ $^ $(TESTLIBS) $(XMLRPC_LIBS) $(PROTO_BUF_LIBS)

.PHONY: clean
clean:
	rm -f *.o $(PROGS) $(PROTO_BUF_SRC) $(PROTO_BUF_HEADER) *~ .depend
	$(MAKE) -C $(TESTDIRS) clean
