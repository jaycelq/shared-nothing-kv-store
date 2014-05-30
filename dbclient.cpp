#include "transaction.hpp"

int
main(int argc, char **) {

    if (argc-1 > 0) {
        cerr << "This program has no arguments" << endl;
        exit(1);
    }

    try {
        string const serverUrl("http://localhost:8080/RPC2");
        string const methodName("db.ExcuteTransaction");

        xmlrpc_c::clientSimple dbClient;
        xmlrpc_c::value result;
        xmlrpc_c::paramList transcParam;
        TransactionReq transreq;

        transreq.addOperation(InMemDB::TransReq_Op_OpCode_GET, 1);
        transreq.addOperation(InMemDB::TransReq_Op_OpCode_PUT, 2, "a");
        transreq.addOperation(InMemDB::TransReq_Op_OpCode_GETRANGE, 1, 3);
        transreq.addOperation(InMemDB::TransReq_Op_OpCode_GETRANGE, 1, 3);
        transcParam.addc(transreq.toString());

        dbClient.call(serverUrl, methodName, transcParam, &result);

        TransactionRsp transrsp = TransactionRsp(result);

        for (int i = 0; i < transrsp.size(); i++) {
            const InMemDB::TransRsp::Rsp &ret = transrsp.Response(i);
            cout << "Key: " << ret.key() << ", value: " << ret.value() << endl;
        }

    } catch (exception const& e) {
        cerr << "Client threw error: " << e.what() << endl;
    } catch (...) {
        cerr << "Client threw unexpected error." << endl;
    }

    return 0;
}