//
//  DBOperationGetTestCaseGenerator.cpp
//  InMemDB
//
//  Created by satanwoo on 14-6-3.
//  Copyright (c) 2014年 Ziqi Wu. All rights reserved.
//

#include "DBOperationGetTestCaseGenerator.h"

DBOperationGetTestCaseGenerator::DBOperationGetTestCaseGenerator(int key, std::string *s, TransactionReq *req)
{
    this->stream = s;
    this->m_key = key;
    this->req = req;
}

void DBOperationGetTestCaseGenerator::generateOperationTestCase()
{
    stream->append("  <Operation>\n");
    stream->append("    <Type>GET</Type>\n");
    stream->append("    <Key>");
    stream->append(std::to_string(this->m_key));
    stream->append("</key>\n");
    stream->append("  </Operation>\n");
    
    this->req->addOperation(InMemDB::TransReq_Op_OpCpde_GET, this->m_key);
}

void DBOperationGetTestCaseGenerator::print()
{
     std::cout << "Operation: Get" << " Key: " << this->m_key << std::endl;
}
