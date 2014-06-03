//
//  DBTestCaseGenerator.cpp
//  InMemDB
//
//  Created by satanwoo on 14-6-3.
//  Copyright (c) 2014年 Ziqi Wu. All rights reserved.
//

#include <iostream>
#include <ctime>
#include "DBTestCaseGenerator.h"
#include "DBOperationTestCaseGenerator.h"
#include "DBOperationGetTestCaseGenerator.h"
#include "DBOperationGeneratorFactory.h"

#define DBTestCaseGeneratorTransactionModule 15
#define DBTestCaseGeneratorOperationModule 20

DBTestCaseGenerator::DBTestCaseGenerator(int worker)
{
    this->m_worker = worker;
    this->stream = new std::string();
    xml.open("testcase.xml");
}

DBTestCaseGenerator::~DBTestCaseGenerator()
{
    xml.close();
    delete this->stream;
    this->m_worker = 0;
}

void DBTestCaseGenerator::generateTestCase()
{
    srand((unsigned)time(0));
    int testCaseCount = rand() % DBTestCaseGeneratorTransactionModule;
    
    std::cout << "Transaction is " << testCaseCount << std::endl;
    
    this->stream->clear();
    
    for (int i = 0; i < testCaseCount; i++)
    {
        generateTransaction();
    }
    
    xml << *this->stream << std::endl;
}

void DBTestCaseGenerator::generateTransaction()
{
    srand((unsigned)time(0));
    int operationCount = rand() % DBTestCaseGeneratorOperationModule;
    std::cout << "Operation is " << operationCount << std::endl;
    
    this->stream->append("<Transaction>\n");
    
    for (int i = 0; i < operationCount; i++)
    {
        DBOperationGeneratorType type = DBOperationGeneratorType(i % 3);
        DBOperationTestCaseGenerator *generator = DBOperationGeneratorFactory::createOperationTestCaseGenerator(type, this->m_worker, this->stream);
        generator->generateOperationTestCase();
        delete generator;
    }
    
    this->stream->append("</Transcation>\n");
}