#include "dbTest.hpp"
#include <ctime>
#include <iostream>
using namespace std;

dbTest::dbTest(int workerNum, int partitionSize, int crossSize, int transSize, int hitSite)
{
    struct timeval time; 
    gettimeofday(&time,NULL);
    srand((time.tv_sec * 1000) + (time.tv_usec / 1000));

    this->workerNum = workerNum;
    this->partitionSize = partitionSize;
    this->maxKey = workerNum * partitionSize;
    this->crossSize = crossSize;
    this->transSize = transSize;
    this->hitSite = hitSite;
}

TransactionReq dbTest::generateTrans()
{
    TransactionReq req;
    int head;
    int key, key2;
    string value;

    if(hitSite == -1) 
        head = rand() % workerNum;
    else head = hitSite;

    cout << endl <<"Generate Transaction:" << endl;
    for(int i = 0; i < transSize; i++) {
        int type = dbOpType(rand() % 3);
        switch(type) {
        case dbOpGet:
            key = (rand() % (crossSize * partitionSize) + head * partitionSize) % maxKey;
            req.addOperation(InMemDB::TransReq_Op_OpCode_GET, key);
            cout << "generate get key: " << key << endl;
            break;
        case dbOpPut:
            key = (rand() % (crossSize * partitionSize) + head * partitionSize) % maxKey;
            value = generateRandomValue(valueLength);
            req.addOperation(InMemDB::TransReq_Op_OpCode_PUT, key, value);
            cout << "generate put key:" << key << " value: " << value << endl;
            break;
        case dbOpGetRange:
            key = (rand() % (crossSize * partitionSize) + head * partitionSize);
            key2 = (rand() % (crossSize * partitionSize) + head * partitionSize);
            if(key2 < key) swap(key, key2);
            key = key % maxKey;
            key2 = key2 % maxKey;
            if(key2 >= key) {
                req.addOperation(InMemDB::TransReq_Op_OpCode_GETRANGE, key, key2);
                cout << "generate getrange key:" << key << " key2: " << key2 << endl;
            }
            else {
                req.addOperation(InMemDB::TransReq_Op_OpCode_GETRANGE, key, maxKey - 1);
                req.addOperation(InMemDB::TransReq_Op_OpCode_GETRANGE, 0, key2);
                cout << "generate getrange and divide key:" << key << " key2: " << key2 << endl;
            }
            break;
        default:
            break;
        }
    }
    return req;
}

string dbTest::generateRandomValue(int len)
{        
    string result = "";
        
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
        
    for (int i = 0; i < len; ++i) {
        result += alphanum[rand() % (sizeof(alphanum) - 1)];
    }
        
    return result;
}

void dbTest::swap(int &key, int &key2)
{
    int tmp;
    tmp = key;
    key = key2;
    key2 = tmp;
}
