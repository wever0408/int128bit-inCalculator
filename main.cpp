#include <iostream>
#include <conio.h>
#include <string>
#include <limits.h>
#include <fstream>
#include <sstream>
#include "BigInt.h"
using namespace std;

int main(int argc,char* argv[])
{
	fstream fIn,fOut;
	fIn.open("input.txt", ios::in);
	fOut.open("output.txt",ios::out);
	string input;
	while (getline(fIn, input))
	{
		BigInt a = { 0 };
		stringstream sin;
		sin << input;
		string s1, s2, s3, s4;
		getline(sin, s1, ' ');
		getline(sin, s2, ' ');
		getline(sin, s3, ' ');
		getline(sin, s4);
		if (s3 == "+" || s3 == "-" || s3 == "/" || s3 == "*" || s3 == "AND" || s3 == "OR" || s3 == "XOR" || s3 == "<<" || s3 == ">>")
		{
			
			BigInt(*operate)(BigInt, BigInt) = NULL;
			if (s1 == "2")
			{
				BigInt res = { 0 };
				a = BinToDec((char*)s2.c_str());
				if (s3 == ">>")
				{
					int radix = atoi(s4.c_str());
					res = a >> radix;
					fOut << DecToBin(res) << endl;
				}
				else if (s3 == "<<")
				{
					int radix = atoi(s4.c_str());
					res = a << radix;
					fOut << DecToBin(res) << endl;
				}
				else
				{
					BigInt b = { 0 };
					b = BinToDec((char*)s4.c_str());
					operate = GetOperator(s3);
					res = operate(a, b);
					fOut << DecToBin(res) << endl;
				}

			}
			else if (s1 == "10")
			{
				StringToBigInt(s2, a);
				if (s3 == ">>")
				{
					int radix = atoi(s4.c_str());
					PrintBigInt(a >> radix,fOut);
				}
				else if (s3 == "<<")
				{
					int radix = atoi(s4.c_str());
					PrintBigInt(a << radix,fOut);
				}
				else
				{
					BigInt b = { 0 };
					StringToBigInt(s4, b);
					operate = GetOperator(s3);
					PrintBigInt(operate(a, b),fOut);
				}

			}
			else if (s1 == "16")
			{
				BigInt res;
				a = HexToDec((char*)s2.c_str());
				if (s3 == ">>")
				{
					int radix = atoi(s4.c_str());
					res = a >> radix;
					fOut << DecToHex(res) << endl;
				}
				else if (s3 == "<<")
				{
					int radix = atoi(s4.c_str());
					res = a << radix;
					fOut << DecToHex(res) << endl;
				}
				else
				{
					BigInt b = { 0 };
					b = HexToDec((char*)s4.c_str());
					operate = GetOperator(s3);
					res = operate(a, b);
					fOut << DecToHex(res) << endl;
				}
			}
		}
		else
		{	
			if (s2 == "~")
			{
				if (s1 == "2")
				{
					a = BinToDec((char*)s3.c_str());
					a = ~a;
					fOut << DecToBin(a) << endl;
				}
				else if (s1 == "10")
				{
					StringToBigInt(s3, a);
					a = ~a;
					PrintBigInt(a,fOut);
				}
				else if (s1 == "16")
				{
					a = HexToDec((char*)s3.c_str());
					a = ~a;
					fOut << DecToHex(a) << endl;
				}
			}
			else
			{
				if (s1 == "2" && s2 == "10")
				{
					a = BinToDec((char*)s3.c_str());
					PrintBigInt(a,fOut);
				}
				else if (s1 == "10" && s2 == "2")
				{
					StringToBigInt(s3, a);
					fOut << DecToBin(a) << endl;
				}
				else if (s1 == "10" && s2 == "16")
				{
					StringToBigInt(s3, a);
					fOut << DecToHex(a) << endl;
				}
				else if (s1 == "16" && s2 == "10")
				{
					a = HexToDec((char*)s3.c_str());
					PrintBigInt(a,fOut);
				}
				else if (s1 == "2" && s2 == "16")
				{
					fOut << BinToHex((char*)s3.c_str()) << endl;
				}
				else if (s1 == "16" && s2 == "2")
				{
					fOut << HexToBin((char*)s3.c_str()) << endl;
				}
			}
		}
	}
	system("pause");
}