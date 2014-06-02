#ifndef _dbworker_hpp
#define _dbworker_hpp

#include <cassert>
#include <stdexcept>
#include <iostream>
#include <unistd.h>
#include <pthread.h>

#include "common.hpp"
#include "transaction.hpp"
#include "BPlusTree.hpp"

using namespace std;

class dbcoordinator;
class ExcuteTransaction;

class dbworker {
private:
    partition p;
    pthread_mutex_t buf_mutex;
    pthread_mutex_t work_mutex;
    pthread_cond_t work_cv;
    TransactionReq* trans_req;
    /*B+ tree of the partitioned key value store*/
    BPlusTree partitionedDB;
public:
    friend class dbcoordinator;
    friend class ExcuteTransaction;
    dbworker();
    /*work cv, coordinator must signal work cv to wake up the worker*/
    /*map that store the result of get and get_range for coordinator*/
    //map<string, xmlrpc_c::value> buf;
    /*bool that store the result of put*/
    //bool* result;
    /*condition variable to wake up worker or inform coordinator*/
    pthread_cond_t buf_cv;
    /*Key range the worker is responsible for*/
    //Key lower_bound, upper_bound;
    /*
    dbworker();
    void put(Key key, Value value);
    map<string, xmlrpc_c::value> get(Key key);
    map<string, xmlrpc_c::value> get_range(Key key1, Key key2);
    */
    static void *worker_routine(void *args) ;
};

#endif
