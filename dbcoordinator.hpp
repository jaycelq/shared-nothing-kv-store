#ifndef _dbcoordinator_hpp
#define _dbcoordinator_hpp

#define WIN32_LEAN_AND_MEAN  /* required by xmlrpc-c/server_abyss.hpp */

#include <cassert>
#include <stdexcept>
#include <iostream>
#include <unistd.h>
#include <pthread.h>

using namespace std;

#include <xmlrpc-c/base.hpp>
#include <xmlrpc-c/base64.hpp>
#include <xmlrpc-c/registry.hpp>
#include <xmlrpc-c/server_abyss.hpp>

#include "common.hpp"
#include "dbworker.hpp"
#include "transaction.hpp"

class ExcuteTransaction;

class dbcoordinator {
private:
    /*RPC Server*/
    xmlrpc_c::serverAbyss* dbServer;
    xmlrpc_c::registry* dbRegistry;

    /*DB Worker*/
    int workerNums;
    int maxKeyNums;
    int keysPerWorker;
    dbworker* workers;
    pthread_t* worker_threads;
    map<int, TransactionReq> mapTransaction(TransactionReq transreq);
public:
    friend class ExcuteTransaction;
    dbcoordinator(int workerNums, int maxKeyNums);
    void setupWorkers();
    void setupRPC(ExcuteTransaction* rpc_method);
    void runRPC() {dbServer->run();}
};


class ExcuteTransaction : public xmlrpc_c::method {
private:
    dbcoordinator& rpc_method;
public:
    ExcuteTransaction(dbcoordinator co) : rpc_method(co) {
        // signature and help strings are documentation -- the client
        // can query this information with a system.methodSignature and
        // system.methodHelp RPC.
        this->_signature = "s:s";
        // method's result and two arguments are integers
        this->_help = "This method receive a string and put it into db";
    }
    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value *   const  retvalP);
};

#endif
