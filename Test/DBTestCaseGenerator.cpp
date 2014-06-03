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

TransactionReq DBTestCaseGenerator::generateTestCase()
{
    srand(seed);
    seed = rand();
    
    TransactionReq req;
    generateTransaction(&req);
    xml << *this->stream << std::endl;	    
    return req;
    
//    int testCaseCount = rand() % DBTestCaseGeneratorTransactionModule;
//    
//    //std::cout << "Transaction is " << testCaseCount << std::endl;
//    
//    
//    this->stream->clear();
//    
//    for (int i = 0; i < testCaseCount; i++)
//    {
//        std::cout << "<Transaction>\n";
//        generateTransaction();
//        std::cout << "</Transaction>\n";
//    }
//    
//    std::cout << std::endl;
//    
//    xml << *this->stream << std::endl;
}

void DBTestCaseGenerator::generateTransaction(TransactionReq *req)
{
    srand(seed);
    seed = rand();
    
    int operationCount = rand() % DBTestCaseGeneratorOperationModule;
    //std::cout << "Operation is " << operationCount << std::endl;
    
    //this->stream->append("<Transaction>\n");
    
    for (int i = 0; i < operationCount; i++)
    {
        
        
        DBOperationGeneratorType type = DBOperationGeneratorType(rand() % 3);
        DBOperationTestCaseGenerator *generator = DBOperationGeneratorFactory::createOperationTestCaseGenerator(type,
                                                                                                                m_worker,
                                                                                                                m_partitionRange,
                                                                                                                m_crossProbabiltiy,
                                                                                                                stream,
														req);
        //generator->print();
        
        generator->generateOperationTestCase();
        delete generator;
    }
    
    //this->stream->append("</Transcation>\n");
}
