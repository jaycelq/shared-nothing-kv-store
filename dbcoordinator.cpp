#include "dbcoordinator.hpp"

dbcoordinator::dbcoordinator(int workerNums, int maxKeyNums) : workerNums(workerNums), maxKeyNums(maxKeyNums), keysPerWorker(maxKeyNums/workerNums) 
{
    workers = new dbworker[workerNums];
    worker_threads = new pthread_t[workerNums];
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
        std::cout << "Transaction on site" <<it->first << ":\n";
        for(int i = 0; i < it->second.size(); i++) {
            const InMemDB::TransReq::Op &op = it->second.Operation(i);
            switch(op.code()) {
            case InMemDB::TransReq_Op_OpCode_GET: {
                cout << "Opration " << i << " GET, Key " <<op.key()<<endl;
                break;
            }
            case InMemDB::TransReq_Op_OpCode_PUT: {
                cout << "Opration " << i << " PUT, Key " <<op.key() << " Value "<< op.value() <<endl;
                break;
            }
            case InMemDB::TransReq_Op_OpCode_GETRANGE: {
                cout << "Opration " << i << " GETRANGE, Key1 " <<op.key() << " Key2 "<< op.key2() <<endl;
                break;
            }
            default: break;
            }
        }
    }
    
    TransactionRsp transrsp;
    transrsp.addResponse(3, "ab");
    transrsp.addResponse(4,"cde");
    transrsp.addResponse(5,"fff");

    *retvalP = transrsp.toString();
}

