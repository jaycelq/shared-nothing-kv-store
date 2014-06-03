//
//  DBOperationGeneratorFactory.h
//  InMemDB
//
//  Created by satanwoo on 14-6-3.
//  Copyright (c) 2014年 Ziqi Wu. All rights reserved.
//

#ifndef InMemDB_DBOperationGeneratorFactory_h
#define InMemDB_DBOperationGeneratorFactory_h

#include <iostream>
#include <ctime>
#include "DBOperationGetTestCaseGenerator.h"
#include "DBOperationPutTestCaseGenerator.h"
#include "DBOperationGetRangeTestCaseGenerator.h"
#include "DBTestCaseGenerator.h"

typedef enum {
    DBOperationGeneratorTypeGet = 0,
    DBOperationGeneratorTypePut = 1,
    DBOperationGeneratorTypeGetRange = 2
} DBOperationGeneratorType;

class DBOperationGeneratorFactory
{
public:
    static DBOperationTestCaseGenerator *createOperationTestCaseGenerator(DBOperationGeneratorType type,
                                                                          int worker,
                                                                          int rangeInPartition,
                                                                          int maxCross,
                                                                          std::string *s)
    {
        DBOperationTestCaseGenerator *gc = NULL;
        
        if (type == DBOperationGeneratorTypeGet)
        {
            gc = new DBOperationGetTestCaseGenerator(generateRandomKey(worker, rangeInPartition), s);
        }
        else if (type == DBOperationGeneratorTypePut)
        {
            gc = new DBOperationPutTestCaseGenerator(generateRandomKey(worker, rangeInPartition), generateRandomValue(8), s);
        }
        else
        {
            int start = generateRandomKey(worker, rangeInPartition);
            int end = generateRandomKeyAmongCross(start, rangeInPartition, generateRandomCross(maxCross), worker);
            gc = new DBOperationGetRangeTestCaseGenerator(start, end, s);
        }
        return gc;
    }
    
private:
    static int generateRandomKey(int worker, int rangeInPartition)
    {
        srand(DBTestCaseGenerator::seed);
        DBTestCaseGenerator::seed = rand();
        
        return rand() % (worker * rangeInPartition);
    }
    
    static int generateRandomKey(int range)
    {
        srand(DBTestCaseGenerator::seed);
        DBTestCaseGenerator::seed = rand();
        
        return rand() % range;
    }
    
    static std::string generateRandomValue(int len)
    {
        srand(DBTestCaseGenerator::seed);
        DBTestCaseGenerator::seed = rand();
        
        std::string result = "";
        
        static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
        
        for (int i = 0; i < len; ++i) {
            result += alphanum[rand() % (sizeof(alphanum) - 1)];
        }
        
        return result;
    }
    
    static int generateRandomCross(int cross)
    {
        srand(DBTestCaseGenerator::seed);
        DBTestCaseGenerator::seed = rand();
        
        return rand() % cross + 1;
    }
    
    static int locatePartitionID(int key, int rangeInPartition)
    {
        return key / rangeInPartition;
    }
    
    static int generateRandomKeyAmongCross(int key, int rangeInPartition, int cross, int worker)
    {
        //std::cout << "Cross " << cross << std::endl;
        
        int tempCross = cross;
        int location = locatePartitionID(key, rangeInPartition);
        
        if (location + tempCross > worker)
        {
            tempCross = worker - location;
        }
        
        int endLocation = tempCross - 1 + location;
        //std::cout << "End Location " << location << " " <<  endLocation << std::endl;
        int endKey = generateRandomKey(rangeInPartition) + endLocation * rangeInPartition;
        
        while (endKey <= key)
        {
            int remain = (location + 1) * rangeInPartition - key;
            endKey = generateRandomKey(remain) + key;
        }
        
        //std::cout << "EndKey is " << key << " " << endKey << std::endl;
        
        return endKey;
    }
};

#endif
