#include "transaction.hpp"
#include "Test/dbTest.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>


static void print_usage()
{
    printf("Usage: ./dbclient -n(--worker) worker_number -k(--key) key -c(--crossPartition) cross_partition -l(--transLenght) length -h(--header) header\n\
                 -n or --worker to define worker number\n\
                 -k or --key to define the keys number every worker is responsible\n\
                 -c or --crossPartition to define the cross Partitions numbers of the transaction\n\
                 -l or --transLenght to define the operation number every transaction includes\n\
                 -h or --header to define the worker to access\n");
}

int
main(int argc, char **argv) {

    const char *optstring="n:k:c:l:h:";
    int worker_num = 0, key = 0, crossP = 0, transLength = 0, header = -1 ,c, index;
    struct option opts[]={{"worker",required_argument,NULL,'n'},
                          {"key",required_argument,NULL,'k'},
                          {"crossPartition", required_argument, NULL, 'c'},
                          {"transLength", required_argument, NULL, 'l'},
                          {"header", required_argument, NULL, 'h'},
                          {0, 0, 0, 0,}};
    
    while((c=getopt_long(argc,argv,optstring,opts,&index))!=-1)
    {

        switch(c)
        {
        case 'n'://-n or --worker to define worker number 
            worker_num = atoi(optarg);
#ifdef DEBUG
            printf("worker number is %d \n", worker_num);
#endif
            break;
        case 'k'://-k or --key to define max key range
            key =atoi(optarg);
#ifdef DEBUG
            printf("key range is %d \n", key);
#endif
            break;
        case 'c':
            crossP = atoi(optarg);
#ifdef DEBUG
            printf("cross Partition is %d \n", crossP);
#endif
            break;
        case 'l':
            transLength = atoi(optarg);
#ifdef DEBUG
            printf("transaction length %d \n", transLength);
#endif
            break;
        case 'h':
            header = atoi(optarg);
#ifdef DEBUG
            printf("hit site header is %d \n", header);
#endif
            break;
        case '?':
            print_usage();
            exit(0);
        }
    }

    try {
        string const serverUrl("http://localhost:8080/RPC2");
        string const methodName("db.ExcuteTransaction");

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
     
	
	dbTest* test = new dbTest(worker_num, key, crossP, transLength, header);
	xmlrpc_c::clientSimple dbClient;
        
	for (int t = 0; t < 10000; t++) {
            xmlrpc_c::value result;
            xmlrpc_c::paramList transcParam;
            TransactionReq transreq;

            transreq = test->generateTrans();
            transcParam.addc(transreq.toString());

            dbClient.call(serverUrl, methodName, transcParam, &result);

            TransactionRsp transrsp = TransactionRsp(result);

#ifdef DEBUG
            for (int i = 0; i < transrsp.size(); i++) {
                const InMemDB::TransRsp::Rsp &ret = transrsp.Response(i);
                cout << "Key: " << ret.key() << ", value: " << ret.value() << endl;
            }
#endif
            transreq.clear();
            transrsp.clear();
        }

        cout << "dbClient finished !\n";
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
