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

#include "transaction.hpp"

class ExcuteTransaction : public xmlrpc_c::method {
public:
    ExcuteTransaction() {
        // signature and help strings are documentation -- the client
        // can query this information with a system.methodSignature and
        // system.methodHelp RPC.
        this->_signature = "s:s";
        // method's result and two arguments are integers
        this->_help = "This method receive a string and put it into db";
    }
    void
    execute(xmlrpc_c::paramList const& paramList,
            xmlrpc_c::value *   const  retvalP) {
        TransactionReq transreq = TransactionReq(paramList.getString(0));
        paramList.verifyEnd(1);

        for (int i = 0; i < transreq.size(); i++) {
            const InMemDB::TransReq::Op &op = transreq.Operation(i);
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
        
        TransactionRsp transrsp;
        transrsp.addResponse(3, "ab");
        transrsp.addResponse(4,"cde");
        transrsp.addResponse(5,"fff");

        *retvalP = transrsp.toString();
    }
};



int 
main(int           const, 
     const char ** const) {

    try {
        xmlrpc_c::registry myRegistry;

        xmlrpc_c::methodPtr const ExcuteTransactionP(new ExcuteTransaction);

        myRegistry.addMethod("db.ExcuteTransaction", ExcuteTransactionP);
        
        xmlrpc_c::serverAbyss myAbyssServer(
            xmlrpc_c::serverAbyss::constrOpt()
            .registryP(&myRegistry)
            .portNumber(8080));
        
        myAbyssServer.run();
        // xmlrpc_c::serverAbyss.run() never returns
        assert(false);
    } catch (exception const& e) {
        cerr << "Something failed.  " << e.what() << endl;
    }
    return 0;
}
