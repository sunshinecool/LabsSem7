struct transaction{
	int account_no;
	int amount;	
};
program ATM{
	version ATM_v1 {
		void deposit(transaction) = 1;
		void withdraw(transaction) = 2;
		int balance(int) = 3;
	} = 1;
} = 0x2fffffff;