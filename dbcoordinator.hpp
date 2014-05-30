
class dbcoordinator {
public:
    /*The ticket mutex to ensure the sequence consistency*/
    pthread_mutex_t ticket_mutex;
    dbcoordinator();
    bool put(Key key, Value value);
    map<string, xmlrpc_c::value> get(Key key);
    map<string, xmlrpc_c::value> get_range(Key key1, Key key2);
private:
    int hash(string key);
}
