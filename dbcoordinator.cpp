#include "dbcoordinator.hpp"
#include "transaction.hpp"

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

void ExcuteTransaction::execute(xmlrpc_c::paramList const& paramList,
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

