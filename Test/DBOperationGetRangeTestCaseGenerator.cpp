//
//  DBOperationGetRangeTestCaseGenerator.cpp
//  InMemDB
//
//  Created by satanwoo on 14-6-3.
//  Copyright (c) 2014年 Ziqi Wu. All rights reserved.
//

#include "DBOperationGetRangeTestCaseGenerator.h"

DBOperationGetRangeTestCaseGenerator::DBOperationGetRangeTestCaseGenerator(int start, int end, std::string *s, TransactionReq *req)
{
    this->m_start = start;
    this->m_end = end;
    this->stream = s;
    this->req = req;
}

void DBOperationGetRangeTestCaseGenerator::generateOperationTestCase()
{
    stream->append("  <Operation>\n");
    stream->append("    <Type>GETRANGE</Type>\n");
    stream->append("    <Start>");
    stream->append(std::to_string(this->m_start));
    stream->append("</Start>\n");
    stream->append("    <End>");
    stream->append(std::to_string(this->m_end));
    stream->append("</End>\n");
    stream->append("  </Operation>\n");
    
    this->req->addOperation(InMemDB::TransReq_Op_OpCode_GETRANGE, this->m_start, this->m_end);
}

void DBOperationGetRangeTestCaseGenerator::print()
{
     std::cout << "Operation: GetRange" << " Start: " << this->m_start << " End:" << this->m_end << std::endl;
}
