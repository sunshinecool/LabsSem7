/*
  llist printer RPC client
  by Jeff Bezanson
*/

#include "llist.h"
int main(int argc, char *argv[])
{
    CLIENT *cl;
    int *result;

    if (argc < 2)
        return 1;

    cl = clnt_create(argv[1], PRINTER, PRINTER_V1, "tcp");
    if (cl == NULL) {
        printf("error: could not connect to server.\n");
        return 1;
    }
    account* acc;

    result = query_balance_1(acc, cl);
    printf("%d", *result);
    if (result == NULL) {
        printf("error: RPC failed!\n");
        return 1;
    }
    printf("client: server says it printed %d items.\n", *result);

    return 0;
}
