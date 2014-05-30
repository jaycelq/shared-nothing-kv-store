#include "transaction.hpp"
#include "dbcoordinator.hpp"

int 
main(int           const, 
     const char ** const) {

    try {
        dbcoordinator coordinator;
        ExcuteTransaction* trans_method = new ExcuteTransaction(coordinator);
        coordinator.setupRPC(trans_method);
        coordinator.runRPC();
        assert(false);
    } catch (exception const& e) {
        cerr << "Something failed.  " << e.what() << endl;
    }
    return 0;

}
