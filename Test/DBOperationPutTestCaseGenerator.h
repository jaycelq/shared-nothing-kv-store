//
//  DBOperationPutTestCaseGenerator.h
//  InMemDB
//
//  Created by satanwoo on 14-6-3.
//  Copyright (c) 2014年 Ziqi Wu. All rights reserved.
//

#ifndef InMemDB_DBOperationPutTestCaseGenerator_h
#define InMemDB_DBOperationPutTestCaseGenerator_h

#include "DBOperationTestCaseGenerator.h"
class DBOperationPutTestCaseGenerator : public DBOperationTestCaseGenerator
{
public:
    DBOperationPutTestCaseGenerator(int key, std::string value, std::string *s);
    virtual void generateOperationTestCase();
    virtual void print();
private:
    int m_key;
    std::string m_value;
};

#endif
