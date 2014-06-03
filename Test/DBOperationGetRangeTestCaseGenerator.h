//
//  DBOperationGetRangeTestCaseGenerator.h
//  InMemDB
//
//  Created by satanwoo on 14-6-3.
//  Copyright (c) 2014年 Ziqi Wu. All rights reserved.
//

#ifndef InMemDB_DBOperationGetRangeTestCaseGenerator_h
#define InMemDB_DBOperationGetRangeTestCaseGenerator_h

#include "DBOperationTestCaseGenerator.h"
class DBOperationGetRangeTestCaseGenerator : public DBOperationTestCaseGenerator
{
public:
    DBOperationGetRangeTestCaseGenerator(int start, int end, std::string *s);
    virtual void generateOperationTestCase();
private:
    int m_start;
    int m_end;
};

#endif
