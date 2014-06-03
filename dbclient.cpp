#include "transaction.hpp"
#include "Test/DBTestCaseGenerator.h"

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
	
	DBTestCaseGenerator* test = new DBTestCaseGenerator(4, 1, 199);
	transreq = test->generateTestCase();
        //transreq.addOperation(InMemDB::TransReq_Op_OpCode_GET, 1);
        // Test Case 1
        //transreq.addOperation(InMemDB::TransReq_Op_OpCode_PUT, 1, "a");
        //transreq.addOperation(InMemDB::TransReq_Op_OpCode_PUT, 3, "b");
	//transreq.addOperation(InMemDB::TransReq_Op_OpCode_PUT, 1, "c");
	//transreq.addOperation(InMemDB::TransReq_Op_OpCode_GET, 150);
	//transreq.addOperation(InMemDB::TransReq_Op_OpCode_GET, 90);
	//transreq.addOperation(InMemDB::TransReq_Op_OpCode_GETRANGE, 0, 3);
        //transreq.addOperation(InMemDB::TransReq_Op_OpCode_GETRANGE, 30, 120);
        //transreq.addOperation(InMemDB::TransReq_Op_OpCode_GETRANGE, 10, 100);
        transcParam.addc(transreq.toString());

        dbClient.call(serverUrl, methodName, transcParam, &result);

        TransactionRsp transrsp = TransactionRsp(result);

        for (int i = 0; i < transrsp.size(); i++) {
            const InMemDB::TransRsp::Rsp &ret = transrsp.Response(i);
            cout << "Key: " << ret.key() << ", value: " << ret.value() << endl;
        }

        // Test Case 2
/*        xmlrpc_c::value result2;
       	xmlrpc_c::paramList transcParam2;
        TransactionReq transreq2;

        transreq2.addOperation(InMemDB::TransReq_Op_OpCode_GET, 1002);
        transreq2.addOperation(InMemDB::TransReq_Op_OpCode_PUT, 1);
       	transreq2.addOperation(InMemDB::TransReq_Op_OpCode_GETRANGE, 10, 1856);
       	transreq2.addOperation(InMemDB::TransReq_Op_OpCode_PUT, 998);
       	transreq2.addOperation(InMemDB::TransReq_Op_OpCode_PUT, 1098);
       	transreq2.addOperation(InMemDB::TransReq_Op_OpCode_GET, 7);
       	transcParam2.addc(transreq2.toString());
       
       	dbClient.call(serverUrl, methodName, transcParam2, &result2);

        TransactionRsp transrsp2 = TransactionRsp(result);

        for (int i = 0; i < transrsp.size(); i++) {
            const InMemDB::TransRsp::Rsp &ret = transrsp2.Response(i);
            cout << "Key: " << ret.key() << ", value: " << ret.value() << endl;
        }
*/
    } catch (exception const& e) {
        cerr << "Client threw error: " << e.what() << endl;
    } catch (...) {
        cerr << "Client threw unexpected error." << endl;
    }

    return 0;
}
