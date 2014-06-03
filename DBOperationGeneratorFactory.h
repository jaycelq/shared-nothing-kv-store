//
//  DBOperationGeneratorFactory.h
//  InMemDB
//
//  Created by satanwoo on 14-6-3.
//  Copyright (c) 2014年 Ziqi Wu. All rights reserved.
//

#ifndef InMemDB_DBOperationGeneratorFactory_h
#define InMemDB_DBOperationGeneratorFactory_h

#define DBWorkerKeyRange 100

#include <iostream>
#include <ctime>
#include "DBOperationGetTestCaseGenerator.h"
#include "DBOperationPutTestCaseGenerator.h"
#include "DBOperationGetRangeTestCaseGenerator.h"

typedef enum {
    DBOperationGeneratorTypeGet = 0,
    DBOperationGeneratorTypePut = 1,
    DBOperationGeneratorTypeGetRange = 2
} DBOperationGeneratorType;

class DBOperationGeneratorFactory
{
public:
    static DBOperationTestCaseGenerator *createOperationTestCaseGenerator(DBOperationGeneratorType type, int worker, std::string *s)
    {
        DBOperationTestCaseGenerator *gc = NULL;
        
        if (type == DBOperationGeneratorTypeGet)
        {
            gc = new DBOperationGetTestCaseGenerator(generateRandomInt(worker), s);
        }
        else if (type == DBOperationGeneratorTypePut)
        {
            gc = new DBOperationPutTestCaseGenerator(generateRandomInt(worker), generateRandomInt(worker), s);
        }
        else
        {
            gc = new DBOperationGetRangeTestCaseGenerator(generateRandomInt(worker), generateRandomInt(worker), s);
        }
        return gc;
    }
    
private:
    static int generateRandomInt(int worker)
    {
        srand((unsigned)time(0));
        return rand() % (worker * DBWorkerKeyRange);
    }
};

#endif
