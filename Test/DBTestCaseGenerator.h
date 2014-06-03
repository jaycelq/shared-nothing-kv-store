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

class DBTestCaseGenerator
{
public:
    DBTestCaseGenerator(int worker);
    ~DBTestCaseGenerator();
    
    void generateTestCase();
    
private:
    void generateTransaction();
    
    std::string *stream;
    std::ofstream xml;
    
    int m_worker;
};


#endif
