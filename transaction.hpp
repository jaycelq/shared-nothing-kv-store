#ifndef _transaction_hpp
#define _transaction_hpp

#include <cstdlib>
#include <string>
#include <iostream>

#include <xmlrpc-c/girerr.hpp>
#include <xmlrpc-c/base.hpp>
#include <xmlrpc-c/base64.hpp>
#include <xmlrpc-c/client_simple.hpp>

#include "transaction.pb.h"

using namespace std;

class TransactionReq {
private:
    InMemDB::TransReq req;
public:
    TransactionReq() {}
    TransactionReq(string s);
    void addOperation(InMemDB::TransReq_Op_OpCode opcode, int key);
    void addOperation(InMemDB::TransReq_Op_OpCode opcode, int key, string value);
    void addOperation(InMemDB::TransReq_Op_OpCode opcode, int key, int key2);
    xmlrpc_c::value_string toString();
    int size() {return req.op_size();}
    void clear() {req.Clear();}
    const InMemDB::TransReq::Op& Operation(int i) {return req.op(i);}
};

class TransactionRsp {
private:
    InMemDB::TransRsp rsp;
public:
    TransactionRsp() {rsp.set_status(true);}
    TransactionRsp(xmlrpc_c::value s);
    void addResponse(int key, string value);
    xmlrpc_c::value_string toString();
    int size() {return rsp.rsp_size();}
    void clear() {rsp.Clear();}
    void setStatus(bool status) {rsp.set_status(status);}
    const InMemDB::TransRsp::Rsp& Response(int i) {return rsp.rsp(i);}
};

#endif
