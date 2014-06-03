//
//  DBOperationGetTestCaseGenerator.h
//  InMemDB
//
//  Created by satanwoo on 14-6-3.
//  Copyright (c) 2014年 Ziqi Wu. All rights reserved.
//

#ifndef InMemDB_DBOperationGetTestCaseGenerator_h
#define InMemDB_DBOperationGetTestCaseGenerator_h
#include "DBOperationTestCaseGenerator.h"

class DBOperationGetTestCaseGenerator : public DBOperationTestCaseGenerator
{
public:
    DBOperationGetTestCaseGenerator(int key, std::string *s, TransactionReq *req);
    virtual void generateOperationTestCase();
    virtual void print();
private:
    int m_key;
};

#endif
