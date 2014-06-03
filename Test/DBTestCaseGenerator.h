//
//  DBTestCaseGenerator.h
//  InMemDB
//
//  Created by satanwoo on 14-6-3.
//  Copyright (c) 2014年 Ziqi Wu. All rights reserved.
//

#ifndef InMemDB_DBTestCaseGenerator_h
#define InMemDB_DBTestCaseGenerator_h

#include <fstream>
#include <string>
#include "../transaction.hpp"

class DBTestCaseGenerator
{
public:
    DBTestCaseGenerator(int worker, int rangeInPartion, int maxCrossProbability, std::string filename = "testcase.xml");
    ~DBTestCaseGenerator();
    
    TransactionReq generateTestCase();
    
    static int seed;
    
private:
    void generateTransaction(TransactionReq *req);
    
    std::string *stream;
    std::ofstream xml;
    
    int m_worker;
    int m_partitionRange;
    int m_crossProbabiltiy;
};


#endif
