/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "bank.h"
#include<string.h>
#include<stdio.h>
int *
query_balance_1_svc(account *acc, struct svc_req *rqstp)
{
	printf("query\n");
	static int result=1;
	int accno = acc->accno;
	printf("%d\n", accno);
	char* name;
	sprintf(name, "%d", accno); 	
	printf("%s %d\n", name, accno);
//	FILE* fp = fopen(name, "r");	
//	char* buf;
//	fgets(buf, 20, fp);
//	printf("%s\n", buf);	
//	result = atoi(buf);
//	printf("%d\n", result);
	return &result;
}

int *
update_balance_1_svc(account *argp, struct svc_req *rqstp)
{
	static int  result=1;
	printf("update\n");
	/*
	 * insert server code here
	 */

	return &result;
}
