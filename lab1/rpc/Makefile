.SUFFIXES:
.SUFFIXES: .c .o

CLNT = atm
SRVR = atm_svc
CFLAGS = -g -Wall
MYSQL_LIB = `mysql_config --cflags --libs`

SRVR_OBJ = atm_svc_proc.o atm_xdr.o atm_svc.o
CLNT_OBJ = atm.o atm_xdr.o atm_clnt.o

.c.o:; gcc -c  -o $@  $(MYSQL_LIB) $(CFLAGS)  $<

default: $(CLNT) $(SRVR)

$(CLNT): $(CLNT_OBJ)
	gcc -o $(CLNT) $(CLNT_OBJ) $(MYSQL_LIB) 

$(SRVR): $(SRVR_OBJ)
	gcc -o $(SRVR) $(SRVR_OBJ) $(MYSQL_LIB) 