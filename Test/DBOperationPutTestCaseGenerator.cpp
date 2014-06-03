//
//  DBOperationPutTestCaseGenerator.cpp
//  InMemDB
//
//  Created by satanwoo on 14-6-3.
//  Copyright (c) 2014年 Ziqi Wu. All rights reserved.
//

#include "DBOperationPutTestCaseGenerator.h"

DBOperationPutTestCaseGenerator::DBOperationPutTestCaseGenerator(int key, std::string value, std::string *s, TransactionReq *req)
{
    this->stream = s;
    this->m_key = key;
    this->m_value = value;
    this->req = req
}

void DBOperationPutTestCaseGenerator::generateOperationTestCase()
{
    stream->append("  <Operation>\n");
    stream->append("    <Type>PUT</Type>\n");
    stream->append("    <Key>");
    stream->append(std::to_string(this->m_key));
    stream->append("</Key>\n");
    stream->append("    <Value>");
    stream->append(this->m_value);
    stream->append("</Value>\n");
    stream->append("  </Operation>\n");
    
    this->req->addOperation(InMemDB::TransReq_Op_OpCpde_PUT, this->m_key, this->m_value);
}

void DBOperationPutTestCaseGenerator::print()
{
    std::cout << "Operation: Put" << " Key: " << this->m_key << " Value:" << this->m_value << std::endl;
}