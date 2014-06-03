#include "dbcoordinator.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>

static void print_usage()
{
    printf("Usage: ./dbserver -n(--worker) worker_number -k(--key) max_key\n\
                 -n or --worker to define worker number\n\
                 -k or --key to define max key(0 inclusive and max_key exclusive)\n");
}

int 
main(int const argc, 
     char * const argv []) {

    const char *optstring="n:k:";
    int worker_num = 0, max_key = 0, c, index;
    struct option opts[]={{"worker",required_argument,NULL,'n'},
                          {"key",no_argument,NULL,'k'},
                          {0, 0, 0, 0,}};

    if(argc != 5) {
        print_usage();
        exit(0);
    }

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
            max_key =atoi(optarg);
#ifdef DEBUG
            printf("max key range is %d \n", max_key);
#endif
            break;
        case '?':
            print_usage();
            exit(0);
        }
    }

    try {
        dbcoordinator coordinator(worker_num, max_key);
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
