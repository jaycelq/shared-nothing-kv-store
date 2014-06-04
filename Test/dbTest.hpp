#ifndef _DBTEST_HPP
#define _DBTEST_HPP

#include "../transaction.hpp"

class dbTest 
{
public:
    dbTest(int workerNum, int partitionSize, int crossSize, int transSize, int hitSite = -1);
    
    TransactionReq generateTrans();
private:
    typedef enum {
        dbOpGet = 0,
        dbOpPut = 1,
        dbOpGetRange = 2
    } dbOpType;
    static const int valueLength = 10;
    int workerNum;
    int partitionSize;
    int maxKey;
    int crossSize;
    int transSize;
    int hitSite;
    
    string generateRandomValue(int len);
    void swap(int &key, int &key2);
};

#endif
