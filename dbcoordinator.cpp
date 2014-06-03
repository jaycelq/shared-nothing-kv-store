#include "dbcoordinator.hpp"

dbcoordinator::dbcoordinator(int workerNums, int maxKeyNums) : workerNums(workerNums), maxKeyNums(maxKeyNums), keysPerWorker(maxKeyNums/workerNums) 
{
    int lo = 0;
    workers = new dbworker[workerNums];
    worker_threads = new pthread_t[workerNums];
    for(int i = 0; i < workerNums; i++) {
        workers[i].p.ceiling = lo;
        workers[i].p.floor = lo + keysPerWorker - 1;
        lo += keysPerWorker;
    }
}

void dbcoordinator::setupRPC(ExcuteTransaction* rpc_method)
{
    dbRegistry = new xmlrpc_c::registry();
    xmlrpc_c::methodPtr const ExcuteTransactionP(rpc_method);
    dbRegistry->addMethod("db.ExcuteTransaction", ExcuteTransactionP);
    dbServer = new xmlrpc_c::serverAbyss(
            xmlrpc_c::serverAbyss::constrOpt()
            .registryP(dbRegistry)
            .portNumber(8080));
}

void dbcoordinator::setupWorkers()
{
    long t;
    int rc;
    for(t=0; t < workerNums; t++){
        cout << "Coordinator: creating worker thread " << t << endl;
        long i = t;
        rc = pthread_create(&worker_threads[t], NULL, dbworker::worker_routine, (void *)(&workers[i]));
        if (rc){
            cout << "ERROR; return code from pthread_create() is " << rc << endl;
            exit(-1);
        }
    }
}

map<int, TransactionReq> dbcoordinator::mapTransaction(TransactionReq transreq)
{
    map<int, TransactionReq> transmap;

    for(int i = 0; i < transreq.size(); i++) {
        const InMemDB::TransReq::Op &op = transreq.Operation(i);
        switch(op.code()) {
            case InMemDB::TransReq_Op_OpCode_GET: {
                transmap[op.key()/keysPerWorker].addOperation(op.code(), op.key());
                break;
            }
            case InMemDB::TransReq_Op_OpCode_PUT: {
                transmap[op.key()/keysPerWorker].addOperation(op.code(), op.key(), op.value());
                break;
            } 
            case InMemDB::TransReq_Op_OpCode_GETRANGE: {
                for(int j = op.key() / keysPerWorker * keysPerWorker; j <= op.key2(); j += keysPerWorker) {
                    int begin = j;
                    int end = j + keysPerWorker - 1;
                    if(begin < op.key()) begin = op.key();
                    if(end > op.key2()) end = op.key2();
                    transmap[j/keysPerWorker].addOperation(op.code(), begin, end);
                }
                break;
            }
            default: break;
        }
    }
    return transmap;
}

void ExcuteTransaction::execute(xmlrpc_c::paramList const& paramList,
        xmlrpc_c::value *   const  retvalP) {
    TransactionReq transreq = TransactionReq(paramList.getString(0));
    paramList.verifyEnd(1);
    
    map<int, TransactionReq> transmap = rpc_method.mapTransaction(transreq);
    map<int,TransactionReq>::iterator it;
    
    for (it=transmap.begin(); it!=transmap.end(); ++it) {
        pthread_mutex_lock(&((rpc_method.workers[it->first]).work_mutex));
#ifdef DEBUG
        std::cout << "Acquire mutex of worker " <<it->first << ".\n";
#endif
        (rpc_method.workers[it->first]).trans_req = &it->second;
    }

    for (it=transmap.begin(); it!=transmap.end(); ++it) {
#ifdef DEBUG
        std::cout << "Wake up worker " <<it->first << ".\n";
#endif
        pthread_cond_signal(&(rpc_method.workers[it->first]).work_cv);
    }

    TransactionRsp transrsp;
    for(it=transmap.begin(); it!=transmap.end(); ++it) {
        while(rpc_method.workers[it->first].isComplete == false) {usleep(10);}
        rpc_method.workers[it->first].isComplete = false;
        transrsp.mergeFrom(rpc_method.workers[it->first].trans_rsp);
#ifdef DEBUG
        std::cout << "get result from worker:" << it->first << endl;
#endif
    }
    
    
    *retvalP = transrsp.toString();

    for (it=transmap.begin(); it!=transmap.end(); ++it) {
#ifdef DEBUG
        std::cout << "Release mutex of worker " <<it->first << ".\n";
#endif
        pthread_mutex_unlock(&((rpc_method.workers[it->first]).work_mutex));
        (rpc_method.workers[it->first]).trans_req = &it->second;
    }
}

