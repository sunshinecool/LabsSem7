#include<iostream>
#include<algorithm>
#include<cstdlib>
using namespace std;
string dectohex(long int decimalNumber){
	long int remainder,quotient;
	int i=1,j,temp;
	string hexadecimalNumber;
	quotient = decimalNumber;
	while(quotient!=0) {
		temp = quotient % 16;
		if( temp < 10)
		           temp =temp + 48; else
		         temp = temp + 55;
		hexadecimalNumber += temp;
		quotient = quotient / 16;
	}
	reverse(hexadecimalNumber.begin(), hexadecimalNumber.end());
	return hexadecimalNumber;
}
int hextodec(string hexNumber){
	char* ptr;
	return strtol(hexNumber.c_str(), &ptr, 16);
}
int main(){
	string IPHeader;
	cin>>IPHeader;
	cout<<"IP header: "<<IPHeader<<endl;
	int sum = 0;
	for(int i=0; i<IPHeader.length(); i+=4){
		string temp = IPHeader.substr(i,4);
		//cout<<temp<<" "<<hextodec(temp)<<endl;
		sum += hextodec(temp);
	}
	string sumhex = dectohex(sum);
	//cout<<sumhex<<" sumhex"<<endl;
	while(sumhex.length()>4){
		string temp = sumhex.substr(sumhex.length()-4, 4);
		string strcarry = sumhex.substr(0, sumhex.length()-4);
		sum = hextodec(strcarry) + hextodec(temp);
		sumhex = dectohex(sum);
		//cout<<temp<<" "<<strcarry<<" "<<sum<<" "<<sumhex<<endl;
	}
	if(sumhex == "FFFF") cout<<"Valid Header"<<endl;
	else cout<<"Corrupted Header"<<endl;
}


