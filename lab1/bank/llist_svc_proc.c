/*
  llist printer RPC server implementation
  by Jeff Bezanson
*/

#include <stdlib.h>
#include "llist.h"
#include <stdio.h>
int result;
/* print out a list, returning the number of items printed */
int *query_balance_1_svc(account *acc, struct svc_req *req)
{
	result = 1;
	printf("hahaha");
   return &result;
}

int *update_balance_1_svc(account *acc, struct svc_req *req)
{
	result = 1;
	printf("update");
   return &result;
}
