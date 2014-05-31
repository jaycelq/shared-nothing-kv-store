#include "dbworker.hpp"

dbworker::dbworker()
{
    pthread_mutex_init(&work_mutex, NULL);
    pthread_mutex_init(&buf_mutex, NULL);
    pthread_cond_init(&work_cv, NULL);
}

void* dbworker::worker_routine(void *args)
{
    dbworker* worker;
    worker = (dbworker *)args;
    cout <<"Worker thread start! "<< endl;
    pthread_mutex_lock(&(worker->buf_mutex));
    while(true) {
        pthread_cond_wait(&(worker->work_cv), &(worker->buf_mutex));
        for(int i = 0; i < (worker->trans_req)->size(); i++) {
            const InMemDB::TransReq::Op &op = (worker->trans_req)->Operation(i);
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
    return NULL;
}
