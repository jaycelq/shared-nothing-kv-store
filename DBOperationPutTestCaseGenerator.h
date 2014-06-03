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
    DBOperationPutTestCaseGenerator(int key, int value, std::string *s);
    virtual void generateOperationTestCase();
private:
    int m_key;
    int m_value;
};

#endif
