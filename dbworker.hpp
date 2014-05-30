
class dbworker {
private:
    /*B tree of the partitioned key value store*/
    Btree partition;
public:
    /*job priority queue*/
    /*work mutex, coordinator must hold the mutex when worker is working for him*/
    pthread_mutex_t work_mutex;
    /*work cv, coordinator must signal work cv to wake up the worker*/
    pthread_cond_t work_cv;
    /*map that store the result of get and get_range for coordinator*/
    map<string, xmlrpc_c::value> buf;
    /*bool that store the result of put*/
    bool* result;
    /*mutex that protect the map*/
    pthread_mutex_t buf_mutex;
    /*condition variable to wake up worker or inform coordinator*/
    pthread_cond_t buf_cv;
    /*Key range the worker is responsible for*/
    Key lower_bound, upper_bound;

    dbworker();
    void put(Key key, Value value);
    map<string, xmlrpc_c::value> get(Key key);
    map<string, xmlrpc_c::value> get_range(Key key1, Key key2);
}
