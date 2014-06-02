#include "dbworker.hpp"
#include <algorithm>

dbworker::dbworker()
{
    isComplete = false;
    pthread_mutex_init(&work_mutex, NULL);
    pthread_mutex_init(&buf_mutex, NULL);
    pthread_cond_init(&work_cv, NULL);
}

void* dbworker::worker_routine(void *args)
{
    dbworker* worker;
    worker = (dbworker *)args;
    map<int, string> result;
    map<int, string>::iterator it;
    cout <<"Worker thread start! "<< endl;
    pthread_mutex_lock(&(worker->buf_mutex));
    while(true) {
        pthread_cond_wait(&(worker->work_cv), &(worker->buf_mutex));
        worker->trans_rsp.clear();
        for(int i = 0; i < (worker->trans_req)->size(); i++) {
            const InMemDB::TransReq::Op &op = (worker->trans_req)->Operation(i);
            switch(op.code()) {
            case InMemDB::TransReq_Op_OpCode_GET: {
                string value;
                bool found = worker->partitionedDB.get(op.key(), value);
                if(found) result[op.key()] = value;
                cout << "Opration " << i << " GET, Key " <<op.key()<<endl;
                break;
            }
            case InMemDB::TransReq_Op_OpCode_PUT: {
                worker->partitionedDB.put(op.key(), op.value());
                cout << "Opration " << i << " PUT, Key " <<op.key() << " Value "<< op.value() <<endl;
                break;
            }
            case InMemDB::TransReq_Op_OpCode_GETRANGE: {
                cout << "before get range" << endl;
                cout << "Opration " << i << " GETRANGE, Key1 " <<op.key() << " Key2 "<< op.key2() <<endl;
                map<int, string> range = worker->partitionedDB.getrange(op.key(), op.key2());
                cout << "after get range" << endl;
                swap(result, range);
                result.insert(range.begin(), range.end());
                
                break;
            }
            default: break;
            }
        }
        for(it = result.begin(); it != result.end(); it++) {
            worker->trans_rsp.addResponse(it->first, it->second);
        }
        worker->isComplete = true;
    }
    return NULL;
}
