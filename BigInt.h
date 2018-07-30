#include <iostream>
#include <conio.h>
#include <string>
#include <limits.h>
#include <fstream>
#include <sstream>
using namespace std;

struct BigInt
{
	int data[4];
};

void ScanBigInt(BigInt &x); //R
void PrintBigInt(BigInt x,ostream &os); //R
void StringToBigInt(string X, BigInt &a); //R
string StringDiv2(string X); //R
void SetBit(BigInt &a, int bit, int i); //R
string AdditionForString(string A, string B); //R
string power(int n); //R
int mu(int a);
BigInt operator+(BigInt a, BigInt b); //R
BigInt operator-(BigInt a, BigInt b); //R
BigInt operator*(BigInt a, BigInt b); //R
BigInt operator/(BigInt a, BigInt b);
BigInt operator<<(BigInt a, int x); //R
BigInt operator>>(BigInt a, int x); //R
BigInt operator&(BigInt a, BigInt b); //R
BigInt operator|(BigInt a, BigInt b); //R
BigInt operator^(BigInt a, BigInt b); //R
BigInt operator~(BigInt a); //R
BigInt(*GetOperator(string oper))(BigInt a, BigInt b); //R
BigInt BinToDec(char* bin); //R
char *DecToBin(BigInt a); //R
char* BinToHex(char * bin); //R
char* HexToBin(char* hex); //R
char* DecToHex(BigInt x); //R
BigInt HexToDec(char * hexa); //R