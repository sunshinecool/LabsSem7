#include "atm.h"

int main(int argc, char *argv[])
{

    transaction  *transact;
    CLIENT *cl;

    if (argc < 2)
        return 1;

    transact = (transaction* ) malloc(sizeof(transaction));
    transact->account_no = 1011;

    //printf("%d\n", transact->account_no);
    transact->amount = 1010;

    cl = clnt_create(argv[1], ATM, ATM_v1, "tcp");
    if (cl == NULL) {
        printf("error: could not connect to server.\n");
        return 1;
    }
    
    balance_1(&(transact->account_no), cl);
    deposit_1(transact, cl);
    balance_1(&(transact->account_no), cl);
    transact->amount = 2000;
    withdraw_1(transact, cl); 
    balance_1(&(transact->account_no), cl);  
    exit(0);
}
