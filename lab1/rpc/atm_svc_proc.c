#include <my_global.h>
#include "atm.h"
#include <mysql.h>


void * deposit_1_svc(transaction *transact, struct svc_req *request){
	
printf("Request to Deposit To %d amount %d\n", (*transact).account_no, (*transact).amount);


MYSQL *con = mysql_init(NULL);

if (con == NULL) 
{
  fprintf(stderr, "%s\n", mysql_error(con));
  exit(1);
}

if (mysql_real_connect(con, "localhost", "root", "", "bank", 0, NULL, 0) == NULL) 
{
  fprintf(stderr, "%s\n", mysql_error(con));
  mysql_close(con);
  exit(1);
}  	

char query_buffer[1024];
int acc_no = (*transact).account_no;
int amt = ((*transact).amount);

snprintf(query_buffer, sizeof(query_buffer), "SELECT balance FROM account_info WHERE account_no=%d", acc_no);

if (mysql_query(con, query_buffer)) {
		fprintf(stderr, "%s\n", mysql_error(con));
  mysql_close(con);
  exit(1);
}

MYSQL_RES *result = mysql_store_result(con);

if (result == NULL) 
{
  fprintf(stderr, "%s\n", mysql_error(con));
  mysql_close(con);
  exit(1);
}

MYSQL_ROW row;
row = mysql_fetch_row(result);
int bal;


printf("%s ", row[0]);  
sscanf(row[0], "%d", &bal); 
printf("\n");

bal = bal + (transact->amount);
printf("Balance After: %d\n", bal);
snprintf(query_buffer, sizeof(query_buffer), "UPDATE account_info SET balance=%d WHERE account_no=%d", bal,acc_no);
if (mysql_query(con, query_buffer)) {
		fprintf(stderr, "%s\n", mysql_error(con));
  mysql_close(con);
  exit(1);
}
printf("Deposited\n");

mysql_free_result(result);
 mysql_close(con);
return transact;
}

void * withdraw_1_svc(transaction *transact, struct svc_req *request){
	printf("Request to Withdraw From %d amount %d\n", (*transact).account_no, (*transact).amount);
	MYSQL *con = mysql_init(NULL);

if (con == NULL) 
{
  fprintf(stderr, "%s\n", mysql_error(con));
  exit(1);
}

if (mysql_real_connect(con, "localhost", "root", "", "bank", 0, NULL, 0) == NULL) 
{
  fprintf(stderr, "%s\n", mysql_error(con));
  mysql_close(con);
  exit(1);
}  	

char query_buffer[1024];
int acc_no = (*transact).account_no;
int amt = ((*transact).amount);

snprintf(query_buffer, sizeof(query_buffer), "SELECT balance FROM account_info WHERE account_no=%d", acc_no);

if (mysql_query(con, query_buffer)) {
		fprintf(stderr, "%s\n", mysql_error(con));
  mysql_close(con);
  exit(1);
}

MYSQL_RES *result = mysql_store_result(con);

if (result == NULL) 
{
  fprintf(stderr, "%s\n", mysql_error(con));
  mysql_close(con);
  exit(1);
}

MYSQL_ROW row;
row = mysql_fetch_row(result);
int bal;


printf("%s ", row[0]);  
sscanf(row[0], "%d", &bal); 
printf("\n");

if(bal >= transact->amount)
	bal = bal - (transact->amount);
printf("Balance After: %d\n", bal);
snprintf(query_buffer, sizeof(query_buffer), "UPDATE account_info SET balance=%d WHERE account_no=%d", bal,acc_no);
if (mysql_query(con, query_buffer)) {
		fprintf(stderr, "%s\n", mysql_error(con));
  mysql_close(con);
  exit(1);
}
printf("Withdrawn\n");

mysql_free_result(result);
 mysql_close(con);
return transact;
}

int * balance_1_svc(int* account_no, struct svc_req *request){
	MYSQL *con = mysql_init(NULL);

if (con == NULL) 
{
  fprintf(stderr, "%s\n", mysql_error(con));
  exit(1);
}

if (mysql_real_connect(con, "localhost", "root", "", "bank", 0, NULL, 0) == NULL) 
{
  fprintf(stderr, "%s\n", mysql_error(con));
  mysql_close(con);
  exit(1);
}  	

char query_buffer[1024];
int acc_no = *account_no;

snprintf(query_buffer, sizeof(query_buffer), "SELECT balance FROM account_info WHERE account_no=%d", acc_no);

if (mysql_query(con, query_buffer)) {
		fprintf(stderr, "%s\n", mysql_error(con));
  mysql_close(con);
  exit(1);
}

MYSQL_RES *result = mysql_store_result(con);

if (result == NULL) 
{
  fprintf(stderr, "%s\n", mysql_error(con));
  mysql_close(con);
  exit(1);
}

MYSQL_ROW row;
row = mysql_fetch_row(result);
int bal;


printf("Balance: %s\n", row[0]);  
	//printf("Balance : %d\n", bal);
	mysql_free_result(result);
 mysql_close(con);
	return account_no;
}
