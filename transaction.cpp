#include "transaction.hpp"

TransactionReq::TransactionReq(string s) {
    vector<unsigned char> data = xmlrpc_c::bytesFromBase64(s);
    string r = string(data.begin(), data.end());
    req.ParseFromString(r);
}

void TransactionReq::addOperation(InMemDB::TransReq_Op_OpCode opcode, int key)
{
    InMemDB::TransReq_Op* op = NULL;
    switch(opcode) {
    case  InMemDB::TransReq_Op_OpCode_GET: {
        op = req.add_op();
        op->set_code(opcode);
        op->set_key(key);
        break;
    }
    default:
        break;
    } 
    return;
}

void TransactionReq::addOperation(InMemDB::TransReq_Op_OpCode opcode, int key, string value)
{
    InMemDB::TransReq_Op* op = NULL;
    switch(opcode) {
    case  InMemDB::TransReq_Op_OpCode_PUT: {
        op = req.add_op();
        op->set_code(opcode);
        op->set_key(key);
        op->set_value(value);
        break;
    }
    default:
        break;
    }
    return;
}

void TransactionReq::addOperation(InMemDB::TransReq_Op_OpCode opcode, int key, int key2)
{
    InMemDB::TransReq_Op* op = NULL;
    switch(opcode) {
    case  InMemDB::TransReq_Op_OpCode_GETRANGE: {
        op = req.add_op();
        op->set_code(opcode);
        op->set_key(key);
        op->set_key2(key2);
        break;
    }
    default:
        break;
    }
    return;
}

xmlrpc_c::value_string TransactionReq::toString()
{
    string result;
    req.SerializeToString(&result);
    vector<unsigned char> const data(result.begin(), result.end());
    string mybase64(xmlrpc_c::base64FromBytes(data));
    return (xmlrpc_c::value_string(mybase64)) ;
}

TransactionRsp::TransactionRsp(xmlrpc_c::value s)
{
    xmlrpc_c::value_string str(s);
    rsp.set_status(true);
    vector<unsigned char> data = xmlrpc_c::bytesFromBase64(str.cvalue());
    string r = string(data.begin(), data.end());
    rsp.ParseFromString(r);
}

void TransactionRsp::addResponse(int key, string value)
{
    InMemDB::TransRsp_Rsp* ret = NULL;
    
    ret = rsp.add_rsp();
    ret->set_key(key);
    ret->set_value(value);
    
    return;
}

xmlrpc_c::value_string TransactionRsp::toString()
{
    string result;
    rsp.SerializeToString(&result);
    vector<unsigned char> const data(result.begin(), result.end());
    string mybase64(xmlrpc_c::base64FromBytes(data));
    return (xmlrpc_c::value_string(mybase64)) ;
}
