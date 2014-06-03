//
//  DBTestCaseGenerator.cpp
//  InMemDB
//
//  Created by satanwoo on 14-6-3.
//  Copyright (c) 2014年 Ziqi Wu. All rights reserved.
//

#include <iostream>

#include "DBTestCaseGenerator.h"
#include "DBOperationTestCaseGenerator.h"
#include "DBOperationGetTestCaseGenerator.h"
#include "DBOperationGeneratorFactory.h"

#define DBTestCaseGeneratorTransactionModule 15
#define DBTestCaseGeneratorOperationModule 20

int DBTestCaseGenerator::seed = time(NULL);

DBTestCaseGenerator::DBTestCaseGenerator(int worker, int rangeInPartion, int maxCrossProbability, std::string filename)
{
    this->m_worker = worker;
    this->m_partitionRange = rangeInPartion;
    this->m_crossProbabiltiy = maxCrossProbability;
    
    this->stream = new std::string();
    xml.open(filename);
}

DBTestCaseGenerator::~DBTestCaseGenerator()
{
    xml.close();
    delete this->stream;
    this->m_worker = 0;
}

void DBTestCaseGenerator::generateTestCase()
{
    srand(seed);
    seed = rand();
    
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
    srand(seed);
    seed = rand();
    
    int operationCount = rand() % DBTestCaseGeneratorOperationModule;
    std::cout << "Operation is " << operationCount << std::endl;
    
    this->stream->append("<Transaction>\n");
    
    for (int i = 0; i < operationCount; i++)
    {
        DBOperationGeneratorType type = DBOperationGeneratorType(i % 3);
        DBOperationTestCaseGenerator *generator = DBOperationGeneratorFactory::createOperationTestCaseGenerator(type,
                                                                                                                m_worker,
                                                                                                                m_partitionRange,
                                                                                                                m_crossProbabiltiy,
                                                                                                                stream);
        generator->generateOperationTestCase();
        delete generator;
    }
    
    this->stream->append("</Transcation>\n");
}