#include<iostream>
#include<algorithm>
#include<cstdlib>
#include<cmath>
#include<bitset>
using namespace std;
int noOfFragments=0;
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
int binary(string s)
{
	int n=s.length();
	int res = 1;
	int total=0;
	for(int i=n-1;i>=0;i--)
	{
		if(s[i] =='1')
			total += res;
		res = res * 2;
	}
	return total;
}

string* fragment(string ip,int MTU)
{

	string length = ip.substr(4,4);
	string restHeader = ip.substr(16,16);
	string identification = ip.substr(8,4);
	/*string flag=ip.substr(12,4);
	  cout<<flag<<endl;
	  string f =string(1, flag[0]);
	  string  flag_field = bitset<4>(hextodec(f)).to_string();
	  cout<<"Flag _ field "<<flag[0]<<flag_field<<endl;*/
	int l = hextodec(length)-20;
	noOfFragments = ceil(double(l)/double(MTU));
	string *fragments= new string[noOfFragments];
	int left=l;
	int k=1;
	int offset =0;
	int head=32;
	while(k <= noOfFragments)
	{
		string fraglength="";
		if(k != noOfFragments)
			fraglength = dectohex(MTU + 20);
		else
			fraglength = dectohex(left + 20);
		left = left - MTU;
		while(fraglength.length() < 4)
		{
			fraglength = "0"+fraglength;
		}
		string frag_flag =  bitset<13>(offset/8).to_string();
		if(k != noOfFragments)
			frag_flag = "000"+frag_flag;
		else
			frag_flag="001"+frag_flag;
		int f_flag = binary(frag_flag); 
		offset = offset + MTU;
		string final_flag = dectohex(f_flag);
		while(final_flag.length() < 4)
		{
			final_flag = "0"+final_flag;
		}
		string data = ip.substr(head,MTU);
		head = head + MTU;
		string final_fragment =ip.substr(0,4)+fraglength+identification+final_flag+restHeader;
		cout<<"Fragment header : "<<final_fragment<<endl;
		final_fragment = final_fragment + data;
		cout<<data.length()<<endl;
		fragments[k-1] = final_fragment;
		k++;
	}
	return fragments;

}

int offset(string fragment)
{
	string flag = fragment.substr(12,4);
	int off = hextodec(flag);
	//cout<<flag<<endl;
	//cout<<off<<endl;
	flag = bitset<16>(off).to_string();
	flag = flag.substr(3);
	return binary(flag);
}

int iplengthWithoutHeader(string fragment)
{
	string l = fragment.substr(4,4);
	int len = hextodec(l);
	len = len-20;
	return len;
}

void reassemble(string s[],int n,int MTU)
{
	int *arr=new int[n];
	for(int i=0;i<n;i++)
	{
		arr[i] = offset(s[i]);
		cout<<"offset : "<<arr[i]<<endl;
	}

	sort(arr,arr+n);
	int ip_length=0;
	string data="";
	for(int i=0;i<n;i++)
	{
		for(int e=0;e<n;e++)
		{
			if(arr[i] == offset(s[e]))
			{
				ip_length=ip_length+iplengthWithoutHeader(s[e]);
				data = data + s[i].substr(32);
			}
		}
	}
	//cout<<"IP length : "<<ip_length<<endl;
	//cout<<"Data length : "<<data.length()<<endl;
	ip_length = ip_length + 20;
	cout<<"length : "<<ip_length << "  "<<dectohex(ip_length)<<endl;
	string beforeLength = s[0].substr(0,4);
	string length = dectohex(ip_length);
	string indentification = s[0].substr(8,4);
	string restHeader = s[0].substr(16,16);
	string offsetFlag = "0000";
	while(length.length() < 4)
	{
		length = "0"+length;
	}
	string final_ip = beforeLength + length + indentification + offsetFlag + restHeader;

	cout<<final_ip<<endl; 


}

int main()
{
	cout<<hextodec("0FB4")<<endl;
	string ip="01010FB412340000";
	cout<<"Original Packet : "<<ip<<endl;
	for(int i=0;i<(2800*3);i++)
	{
		ip += "1";
	}
	string *f=new string[noOfFragments];
	f = fragment(ip,1000);
	reassemble(f,noOfFragments,1000);
	// offset("010103FC123400FA1111111111111111");
	return 0;
}
