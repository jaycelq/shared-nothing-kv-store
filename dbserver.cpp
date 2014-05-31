#include "dbcoordinator.hpp"

int 
main(int           const, 
     const char ** const) {

    try {
        dbcoordinator coordinator(4, 200);
        ExcuteTransaction* trans_method = new ExcuteTransaction(coordinator);
        coordinator.setupWorkers();
        coordinator.setupRPC(trans_method);
        coordinator.runRPC();
        assert(false);
    } catch (exception const& e) {
        cerr << "Something failed.  " << e.what() << endl;
    }
    return 0;

}
