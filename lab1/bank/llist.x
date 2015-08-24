struct account {
	int accno;
	bool update;
	bool money;
};

program PRINTER {
	version PRINTER_V1 {
		int QUERY_BALANCE(account) = 1;
		int UPDATE_BALANCE(account) = 2;
	} = 1;
} = 0x2fffffff;
