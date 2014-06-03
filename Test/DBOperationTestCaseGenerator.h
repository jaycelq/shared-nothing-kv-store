//
//  DBOperationTestCaseGenerator.h
//  InMemDB
//
//  Created by satanwoo on 14-6-3.
//  Copyright (c) 2014年 Ziqi Wu. All rights reserved.
//

#ifndef InMemDB_DBOperationTestCaseGenerator_h
#define InMemDB_DBOperationTestCaseGenerator_h
#include <fstream>
#include <sstream>
#include <iostream>
#include "../transaction.hpp"

class DBOperationTestCaseGenerator
{
public:
    virtual void generateOperationTestCase() = 0;
    virtual void print() = 0;
    virtual ~DBOperationTestCaseGenerator(){};
protected:
    std::string *stream;
    TransactionReq *req;
};

#endif
