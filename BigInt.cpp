#include "BigInt.h"

BigInt BinToDec(char* bin) //Hàm chuyển từ nhị phân sang thập phân theo thuật toán đã học
{
	string kq = "0";
	string pow = "1";
	BigInt res = { 0 };
	for (int i = strlen(bin)-1; i >= 0; i--)
	{
		if (bin[i] == '1')
		{
			kq = AdditionForString(kq, pow);
		}
		pow = AdditionForString(pow, pow);
	}
	StringToBigInt(kq, res);
	return res;
}

char* DecToBin(BigInt a) //Hàm chuyển từ thập phân sang nhị phân
{
	string bin;
	for (int i = 127; i >= 0; i--)
	{
		char bit = ((a.data[i / 32] >> (31 - i % 32)) & 1) + '0';;
		bin.insert(bin.begin(), bit);
	}
	bin.erase(bin.begin(), bin.begin() + bin.find('1', 0)); //Xóa các bit 0 từ đầu cho tới khi gặp bit 1
	char* res = new char[bin.length() + 1];
	strcpy(res, bin.c_str());
	return res;
}

int mu(int a)// Hàm lũy thừa 2 với cơ số a
{
	int kq = 1;
	for (int i = 0; i < a; i++)
	{
		kq = 2 * kq;
	}
	return kq;
}

char* BinToHex(char* bin) //Hàm chuyển từ nhị phân sang thập lục phân
{

	string s, hex;
	char c;
	for (int i = 0; i < strlen(bin); i++)
	{
		if (bin[i] == '1')
		{
			s.append("1");
		}
		else
		{
			s.append("0");
		}
	}
	if (s.length() % 4 != 0) //Thêm 0 vào chuỗi nhị phân nếu độ dài chuỗi chưa chia hết cho 4
	{
		for (int i = s.length() % 4; i < 4; i++)
		{
			s.insert(0, "0");
		}
	}
	int i = 0;
	while (i < s.length())
	{
		int buffer = 0;
		for (int j = 3; j >= 0; j--)
		{
			if (s[i] == '1')
				buffer = buffer + mu(j);
			i++;
		}

		if (buffer < 10)
			c = buffer + '0';
		else
		{
			switch (buffer)
			{
			case(10) :
				c = 'A';
				break;
			case(11) :
				c = 'B';
				break;
			case(12) :
				c = 'C';
				break;
			case(13) :
				c = 'D';
				break;
			case(14) :
				c = 'E';
				break;
			case(15) :
				c = 'F';
				break;
			}
		}
		hex.push_back(c);
	}
	char* kq = new char[hex.length() + 1];
	strcpy(kq, hex.c_str());
	return kq;
}

char* HexToBin(char* hexa)//Hàm chuyển từ thập lục phân sang nhị phân
{
	string s;
	string sub;
	for (int i = 0; i < strlen(hexa); i++)
	{
		if (hexa[i] == '0') sub = "0000";
		else if (hexa[i] == '1') sub = "0001";
		else if (hexa[i] == '2') sub = "0010";
		else if (hexa[i] == '3') sub = "0011";
		else if (hexa[i] == '4') sub = "0100";
		else if (hexa[i] == '5') sub = "0101";
		else if (hexa[i] == '6') sub = "0110";
		else if (hexa[i] == '7') sub = "0111";
		else if (hexa[i] == '8') sub = "1000";
		else if (hexa[i] == '9') sub = "1001";
		else if (hexa[i] == 'A') sub = "1010";
		else if (hexa[i] == 'B') sub = "1011";
		else if (hexa[i] == 'C') sub = "1100";
		else if (hexa[i] == 'D') sub = "1101";
		else if (hexa[i] == 'E') sub = "1110";
		else if (hexa[i] == 'F') sub = "1111";
		s.append(sub);
	}
	s.erase(s.begin(), s.begin() + s.find('1', 0));
	char* res = new char[s.length() + 1];
	strcpy(res, s.c_str());
	return res;
}
char* DecToHex(BigInt x) //hàm chuyển từ thập phân sang thập lục phân
{
	char *bin = DecToBin(x);
	char* res = BinToHex(bin);
	return res;

}
BigInt HexToDec(char * hexa) //Hàm chuyển từ thập lục phân sang thập phân
{
	char *bin = HexToBin(hexa);
	BigInt res = BinToDec(bin);
	return res;
}

BigInt operator+(BigInt a, BigInt b) //Hàm tính tổng 2 số kiểu BigInt
{
	BigInt res = { 0 };
	int k = 0;
	for (int i = 127; i >= 0; i--)
	{
		bool bit1 = (a.data[i / 32] >> (31 - i % 32)) & 1;
		bool bit2 = (b.data[i / 32] >> (31 - i % 32)) & 1;
		if ((bit1 == 1 && bit2 == 0) || (bit1 == 0 && bit2 == 1))
		{
			if (k == 1)
			{
				res.data[i / 32] = res.data[i / 32] | (0 << (31 - i % 32));
			}
			else
			{
				res.data[i / 32] = res.data[i / 32] | (1 << (31 - i % 32));
				k = 0;
			}
		}
		else if (bit1 == 0 && bit2 == 0)
		{
			res.data[i / 32] = res.data[i / 32] | (k << (31 - i % 32));
			k = 0;
		}
		else if (bit1 == 1 && bit2 == 1)
		{
			if (k == 1)
			{
				res.data[i / 32] = res.data[i / 32] | (1 << (31 - i % 32));
			}
			else
			{
				res.data[i / 32] = res.data[i / 32] | (0 << (31 - i % 32));
				k = 1;
			}
		}
	}
	return res;
}

BigInt operator-(BigInt a, BigInt b) //Hàm tính hiệu 2 số kiểu BigInt
{
	BigInt res = { 0 };
	int k = 0;
	for (int i = 127; i >= 0; i--)
	{
		bool bit1 = (a.data[i / 32] >> (31 - i % 32)) & 1;
		bool bit2 = (b.data[i / 32] >> (31 - i % 32)) & 1;
		if (bit1 == 1 && bit2 == 0)
		{
			if (k == 1)
			{
				res.data[i / 32] = res.data[i / 32] | (0 << (31 - i % 32));
				k = 0;
			}
			else
			{
				res.data[i / 32] = res.data[i / 32] | (1 << (31 - i % 32));
			}
		}
		else if (bit1 == 0 && bit2 == 1)
		{
			if (k == 1)
			{
				res.data[i / 32] = res.data[i / 32] | (0 << (31 - i % 32));
			}
			else
			{
				res.data[i / 32] = res.data[i / 32] | (1 << (31 - i % 32));
				k = 1;
			}
		}
		else if (bit1 == 0 && bit2 == 0)
		{
			res.data[i / 32] = res.data[i / 32] | (k << (31 - i % 32));
		}
		else if (bit1 == 1 && bit2 == 1)
		{
			if (k == 1)
			{
				res.data[i / 32] = res.data[i / 32] | (1 << (31 - i % 32));

			}
			else
			{
				res.data[i / 32] = res.data[i / 32] | (0 << (31 - i % 32));
			}
		}
	}
	return res;
}

BigInt operator*(BigInt a, BigInt b) //Hàm tính tích 2 số kiểu BigInt
{
	BigInt res = { 0 };
	int signed1 = (a.data[0] >> 31) & 1;
	int signed2 = (b.data[0] >> 31) & 1;
	BigInt mot = { 0, 0, 0, 1 };
	if (signed1 == 1 && signed2 == 1)
	{
		a = ~(a - mot);
		b = ~(b - mot);
	}
	else if (signed1 == 1 && signed2 == 0)
	{
		a = ~(a - mot);
	}
	else if (signed1 == 0 && signed2 == 1)
	{
		b = ~(b - mot);
	}
	for (int i = 127; i >= 0; i--)
	{
		int bit = (b.data[i / 32] >> (31 - i % 32)) & 1;
		if (bit == 1)
		{
			res = res + (a << (127 - i));
		}
	}
	if (signed1 == 1 && signed2 == 0)
	{
		res = ~res + mot;
	}
	else if (signed1 == 0 && signed2 == 1)
	{
		res = ~res + mot;
	}
	return res;
}
BigInt operator/(BigInt a, BigInt b) //Hàm tính thương 2 số kiểu BigInt
{ 
	BigInt r = { 0 };
	int signed1 = (a.data[0] >> 31) & 1;
	int signed2 = (b.data[0] >> 31) & 1;
	int n = 128;
	if (signed1^signed2 == 1)
	{
		BigInt mot = { 0, 0, 0, 1 };
		b = ~b + mot;
	}

	while (n > 0)
	{
		int bit = (a.data[0] >> 31) & 1;

		//Shift Left r,a
		a = a << 1;
		r = r << 1;
		r.data[3] = r.data[3] | bit;
		r = r - b;
		int signed3 = r.data[0] >> 31 & 1;
		if (signed3 == 1)
		{
			a = (a >> 1) << 1;
			r = r + b;
		}
		else
		{
			a.data[3] = a.data[3] | 1;
		}
		n--;
	}
	return a;
}

BigInt operator<<(BigInt a, int x) //Hàm dịch trái 1 số nguyên kiểu BigInt
{
	for (int i = 0; i < x; i++)
	{
		a.data[0] = a.data[0] << 1;
		for (int j = 1; j < 4; j++)
		{
			int bit = a.data[j] & (1 << 31);
			a.data[j] = a.data[j] << 1;
			a.data[j - 1] = a.data[j - 1] | bit;
		}
	}
	return a;
}

BigInt operator>>(BigInt a, int x) //Hàm dịch phải 1 số nguyên kiểu BigInt
{
	for (int i = 0; i < x; i++)
	{
		a.data[3] = a.data[3] >> 1;
		for (int j = 2; j >= 0; j--)
		{
			int bit = a.data[j] & 1;
			a.data[j] = a.data[j] >> 1;
			a.data[j + 1] = a.data[j + 1] | (bit << 31);
		}
	}
	return a;
}

BigInt operator&(BigInt a, BigInt b) //Hàm tính AND 2 số kiểu BigInt với nhau
{
	BigInt c = { 0 };
	for (int i = 0; i < 4; i++)
	{
		c.data[i] = a.data[i] & b.data[i];
	}
	return c;
}

BigInt operator|(BigInt a, BigInt b) //Hàm tính OR 2 số kiểu BigInt với nhau
{
	BigInt c = { 0 };
	for (int i = 0; i < 4; i++)
	{
		c.data[i] = a.data[i] | b.data[i];
	}
	return c;
}

BigInt operator^(BigInt a, BigInt b) //Hàm tính XOR 2 số kiểu BigInt với nhau
{
	BigInt c = { 0 };
	for (int i = 0; i < 4; i++)
	{
		c.data[i] = a.data[i] ^ b.data[i];
	}
	return c;
}

BigInt operator~(BigInt a) //Hàm tính NOT 1 số kiểu BigInt
{
	BigInt kq = { 0 };
	for (int i = 0; i < 4; i++)
	{
		kq.data[i] = ~a.data[i];
	}
	return kq;
}

void ScanBigInt(BigInt &x) //Hàm nhập vào 1 chuỗi số và chuyển chuổi thành kiểu BigInt
{
	string X;
	string temp;
	do
	{
		cout << "Nhap so nguyen: "; //Nhập vào 1 chuỗi số
		cin >> X;
		if (X.front() == '-') //Nếu số vừa nhập là số âm
		{
			temp = X.substr(1,X.length()-1);
		}
		else
		{
			temp = X;
		}
	} while (temp.length() > power(127).length() || (temp.length() == power(127).length() && temp >= power(127))); 
	//Kiểm tra chuỗi số có nằm trong khoảng [-2^127 + 1; 2^127 - 1]
	memset(x.data, 0, sizeof(x.data));
	StringToBigInt(X, x);
}

string power(int n) //Hàm tính giá trị của 2 lũy thừa n với kết quả trả về là chuỗi
{
	string sum = "0";
	string pow = "1";
	for (int i = 0; i < n; i++)
	{
		pow = AdditionForString(pow, pow); // 2^n = 2.(2^(n-1))
	}
	return pow;
}

void PrintBigInt(BigInt x,ostream &os) //Hàm in ra số nguyên kiểu BigInt
{
	string kq = "0";
	string pow = "1";
	int signedbit = (x.data[0] >> 31) & 1;
	if (signedbit == 0) //Nếu bit dấu bằng 0
	{
		for (int i = 127; i >= 0; i--)
		{
			int bit = (x.data[i / 32] >> (31 - i % 32)) & 1;

			if (bit == 1)
			{
				kq = AdditionForString(kq, pow);
			}
			pow = AdditionForString(pow, pow);
		}
		os << kq << endl;
	}
	else //Nếu bit dấu là 1
	{
		BigInt mot = { 0, 0, 0, 1 };
		x = x - mot;
		x = ~x;
		for (int i = 127; i >= 0; i--)
		{
			int bit = (x.data[i / 32] >> (31 - i % 32)) & 1;

			if (bit == 1)
			{
				kq = AdditionForString(kq, pow);
			}
			pow = AdditionForString(pow, pow);
		}
		os << "-" + kq << endl;
	}
}

string AdditionForString(string A, string B)//Phép cộng 2 chuỗi số và trả về  chuỗi số kết quả
{
	string s, kq, res;
	_i64toa(LLONG_MAX, (char*)s.c_str(), 10);
	string a1, a2, b1, b2, kq1, kq2;
	__int64 m1 = 0, m2, n1 = 0, n2;
	//Nếu cả 2 chuỗi đều có độ dài < 2 lần độ dài số nguyên MAX 64bit - 2
	if (A.length() / 2 < strlen(s.c_str()) - 1 && B.length() / 2 < strlen(s.c_str()) - 1)
	{
		//Nếu cả 2 chuỗi đều có độ dài >= độ dài số nguyên MAX 64bit
		if (A.length() >= strlen(s.c_str()) && B.length() >= strlen(s.c_str()))
		{
			//Tách chuỗi thành 2 phần, phần thứ 2 có độ dài = độ dài số nguyên 64bit - 1
			a1 = A.substr(0, A.length() - strlen(s.c_str()) + 1);
			a2 = A.substr(A.length() - strlen(s.c_str()) + 1, A.length());
			b1 = B.substr(0, B.length() - strlen(s.c_str()) + 1);
			b2 = B.substr(B.length() - strlen(s.c_str()) + 1, B.length());

			if (a1 != "") m1 = stoll(a1); //Kiếm tra chuỗi có rỗng rồi mới chuyển chuỗi sang số nguyên 64bit
			m2 = stoll(a2);
			if (b1 != "") n1 = stoll(b1); ////Kiếm tra chuỗi có rỗng rồi mới chuyển chuỗi sang số nguyên 64bit
			n2 = stoll(b2);
			_i64toa(n2 + m2, (char*)kq2.c_str(), 10);//Cộng 2 số của phần thứ 2 
			//Nếu độ dài kq2 >  độ dài max trong 2 phần thứ hai thì kq1 + thêm 1
			if (strlen(kq2.c_str()) > std::fmax(a2.length(), b2.length()))
			{
				_i64toa(n1 + m1 + 1, (char*)kq1.c_str(), 10);
				strcpy((char*)kq2.c_str(), kq2.c_str() + 1);
			}
			else
			{
				_i64toa(n1 + m1, (char*)kq1.c_str(), 10);
			}
			kq.append(kq1.c_str());//append kq1 vào kq
			 //Nếu độ dài kq2 <  độ dài max trong 2 phần thứ hai thì thêm bù vào kq2 những số 0
			//VD:  a2 = "0025",b2 = "0025" => kq2 = "50" => sau khi thêm 0 => kq2 = "0050"
			if (strlen(kq2.c_str()) < std::fmax(a2.length(), b2.length()))
			{
				for (int i = strlen(kq2.c_str()); i < std::fmax(a2.length(), b2.length()); i++) kq.append("0");
			}
			kq.append(kq2.c_str());//append kq2 vào kq
		}
		else
		{
			//Nếu cả chuỗi A có độ dài >= độ dài số nguyên 64bit và chuỗi B thì ngược lại
			if (A.length() >= strlen(s.c_str()) && B.length() < strlen(s.c_str()))
			{
				__int64 n;

				a1 = A.substr(0, A.length() - strlen(s.c_str()) + 1);
				a2 = A.substr(A.length() - strlen(s.c_str()) + 1, A.length());


				if (a1 != "") m1 = stoll(a1);////Kiếm tra chuỗi có rỗng rồi mới chuyển chuỗi sang số nguyên 64bit
				m2 = stoll(a2);
				n = stoll(B);

				_i64toa(m2 + n, (char*)kq2.c_str(), 10);
				if (strlen(kq2.c_str()) > std::fmax(a2.length(), b2.length()))
				{
					_i64toa(m1 + 1, (char*)kq1.c_str(), 10);
					strcpy((char*)kq2.c_str(), kq2.c_str() + 1);
				}
				else
				{
					_i64toa(m1, (char*)kq1.c_str(), 10);
				}
				kq.append(kq1.c_str());
				if (strlen(kq2.c_str()) < std::fmax(a2.length(), b2.length()))
				{
					for (int i = strlen(kq2.c_str()); i < std::fmax(a2.length(), b2.length()); i++) kq.append("0");
				}
				kq.append(kq2.c_str());
			}
			//Nếu cả chuỗi B có độ dài >= độ dài số nguyên 64bit và chuỗi A thì ngược lại
			else if (A.length() < strlen(s.c_str()) && B.length() >= strlen(s.c_str()))
			{
				__int64 m;

				b1 = B.substr(0, B.length() - strlen(s.c_str()) + 1);
				b2 = B.substr(B.length() - strlen(s.c_str()) + 1, B.length());

				if (b1 != "") n1 = stoll(b1);////Kiếm tra chuỗi có rỗng rồi mới chuyển chuỗi sang số nguyên 64bit
				n2 = stoll(b2);
				m = stoll(A);

				_i64toa(m + n2, (char*)kq2.c_str(), 10);
				if (strlen(kq2.c_str()) > std::fmax(a2.length(), b2.length()))
				{
					_i64toa(n1 + 1, (char*)kq1.c_str(), 10);
					strcpy((char*)kq2.c_str(), kq2.c_str() + 1);
				}
				else
				{
					_i64toa(n1, (char*)kq1.c_str(), 10);
				}
				kq.append(kq1.c_str());
				if (strlen(kq2.c_str()) < std::fmax(a2.length(), b2.length()))
				{
					for (int i = strlen(kq2.c_str()); i < std::fmax(a2.length(), b2.length()); i++) kq.append("0");
				}
				kq.append(kq2.c_str());
			}
			else
			{
				__int64 m, n;
				m = stoll(A);
				n = stoll(B);
				_i64toa(m + n, (char*)kq.c_str(), 10);
			}
		}
		char * c = new char[strlen(kq.c_str()) + 1];
		strcpy(c, kq.c_str());
		res.append(c);
	}
	//Nếu 1 trong 2 chuỗi có độ dài >= 2 lần độ dài số nguyên MAX 64bit - 2
	else
	{
		if (A.length() / 2 >= strlen(s.c_str()) - 1 && B.length() / 2 >= strlen(s.c_str()) - 1)
		{
			//Tách chuỗi thành 2 phần, phần thứ 2 có độ dài = độ dài số nguyên MAX 64bit
			a1 = A.substr(0, A.length() - strlen(s.c_str()));
			a2 = A.substr(A.length() - strlen(s.c_str()), A.length());
			b1 = B.substr(0, B.length() - strlen(s.c_str()));
			b2 = B.substr(B.length() - strlen(s.c_str()), B.length());

			//Tiếp tục cộng 2 chuỗi đã được chia
			kq2 = AdditionForString(a2, b2);
			kq1 = AdditionForString(a1, b1);
			////Nếu độ dài kq2 >  độ dài max trong 2 phần thứ hai thì kq1 + thêm 1
			if (kq2.length() > std::fmax(a2.length(), b2.length()))
			{
				kq1 = AdditionForString(kq1, "1");
				kq2.erase(kq2.begin());

			}
			res.append(kq1);
			 //Nếu độ dài kq2 <  độ dài max trong 2 phần thứ hai thì thêm bù vào kq2 những số 0
			if (kq2.length() < std::fmax(a2.length(), b2.length()))
			{
				for (int i = kq2.length(); i < std::fmax(a2.length(), b2.length()); i++) res.append("0");
			}
			res.append(kq2);
		}
		//Nếu chuỗi A có độ dài >= 2 lần độ dài số nguyên 64bit - 2 và chuỗi B thì ngược lại
		else if ((A.length() / 2 >= strlen(s.c_str()) - 1) && (B.length() / 2 < strlen(s.c_str()) - 1))
		{
			a1 = A.substr(0, A.length() - strlen(s.c_str()));
			a2 = A.substr(A.length() - strlen(s.c_str()), A.length());

			kq2 = AdditionForString(a2, B);
			if (kq2.length() > std::fmax(a2.length(), B.length()))
			{
				a1 = AdditionForString(a1, "1");
				kq2.erase(kq2.begin());

			}
			res.append(a1);
			if (kq2.length() < std::fmax(a2.length(), B.length()))
			{
				for (int i = kq2.length(); i < std::fmax(a2.length(), B.length()); i++) res.append("0");
			}
			res.append(kq2);
		}
			//Nếu chuỗi A có độ dài < 2 lần độ dài số nguyên 64bit - 2 và chuỗi B thì ngược lại
		else if ((A.length() / 2 < strlen(s.c_str()) - 1) && (B.length() / 2 >= strlen(s.c_str()) - 1))
		{
			b1 = B.substr(0, B.length() - strlen(s.c_str()));
			b2 = B.substr(B.length() - strlen(s.c_str()), B.length());

			kq2 = AdditionForString(A, b2);
			if (kq2.length() > std::fmax(A.length(), b2.length()))
			{
				b1 = AdditionForString(b1, "1");
				kq2.erase(kq2.begin());

			}
			res.append(b1);
			if (kq2.length() < std::fmax(A.length(), b2.length()))
			{
				for (int i = kq2.length(); i < std::fmax(A.length(), b2.length()); i++) res.append("0");
			}
			res.append(kq2);
		}

	}
	return res;
}

void StringToBigInt(string X, BigInt &a) //Hàm chuyển từ chuỗi số sang số nguyên kiểu BigInt
{
	int i = 127;
	if (X.front() == '-') //Nếu chuỗi số là số âm thì SetBit bình thường như số dương rồi sau đó mới chuyển thành số bù 2
	{
		X.erase(X.begin());
		while (X != "0")
		{
			int bit = (X[X.length() - 1] - 48) % 2;
			SetBit(a, bit, i);
			X = StringDiv2(X);
			i--;
		}
		a = ~a;
		BigInt mot = { 0, 0, 0, 1 };
		a = a + mot;
	}
	else //Nếu chuỗi số là số dương
	{
		while (X != "0")
		{
			int bit = (X[X.length() - 1] - 48) % 2;
			SetBit(a, bit, i);
			X = StringDiv2(X);
			i--;
		}
	}
}

string StringDiv2(string X) //Hàm chia chuỗi số cho 2 và trả về chuỗi số kết quả
{

	string kq, kq1, kq2, s1, s2;
	string s;
	_i64toa(LLONG_MAX, (char*)s.c_str(), 10);
	//Nếu chuỗi X có độ dài < 2 lần độ dài số nguyên MAX 64bit - 2
	if (X.length() / 2 < strlen(s.c_str()) - 1)
	{
		//Chia chuỗi thành 2 nửa
		s1 = X.substr(0, X.length() / 2);
		__int64 a1 = 0;
		if (s1 != "") a1 = stoll(s1);
		s2 = X.substr(X.length() / 2, X.length());
		int size = s2.length();
		if (s2 != "")
		{
			//Nếu nửa thứ 1 chia 2 dư 1 thì nhớ thêm 1 vào nửa thứ 2
			if (a1 % 2 == 1)
			{
				s2.insert(0, "1");
			}
			__int64 a2;
			a2 = stoll(s2);
			if (a2 != 0)
			{
				a2 = a2 / 2;
				_i64toa(a2, (char*)kq2.c_str(), 10);
			}
			else
			{
				strcpy((char*)kq2.c_str(), (char*)s2.c_str());
			}

		}
		a1 = a1 / 2;
		if (a1 != 0)
		{
			_i64toa(a1, (char*)kq1.c_str(), 10);
			kq.append(kq1.c_str());
		}
		//	 //Nếu độ dài kq2 <  độ dài thì thêm bù vào kq2 những số 0
		if (strlen(kq2.c_str()) < size)
		{
			for (int i = strlen(kq2.c_str()); i < size; i++) kq.append("0");
		}
		kq.append(kq2.c_str());
	}
	//Nếu chuỗi X có độ dài >= 2 lần độ dài số nguyên MAX 64bit - 2
	else
	{
		s1 = X.substr(0, X.length() / 2);
		s2 = X.substr(X.length() / 2, X.length());
		int size = s2.length();
		kq1 = StringDiv2(s1);
		if ((s1[s1.length() - 1] - 48) % 2 != 0)
		{
			s2.insert(0, "1");
		}
		kq2 = StringDiv2(s2);

		kq.append(kq1);
		if (strlen(kq2.c_str()) < size)
		{
			for (int i = strlen(kq2.c_str()); i < size; i++) kq.append("0");
		}
		kq.append(kq2);

	}
	return kq;
}
void SetBit(BigInt &a, int bit, int i) //Hàm chuyển các bit 0,1 vào a có kiểu BigInt
{
	int r = i / 32;
	int index = i % 32;
	a.data[r] = a.data[r] | (bit << (31 - index));
}

BigInt(*GetOperator(string oper))(BigInt a, BigInt b) //Hàm lấy phép tính và trả về phép tính tương ứng với chuỗi oper
{
	BigInt(*operate)(BigInt, BigInt) = NULL;
	if (oper == "+")
	{
		operate = &operator+;
	}
	else if (oper == "-")
	{
		operate = &operator-;

	}
	else if (oper == "*")
	{
		operate = &operator*;
	}
	else if (oper == "/")
	{
		operate = &operator/;
	}
	else if (oper == "AND")
	{
		operate = &operator&;
	}
	else if (oper == "OR")
	{
		operate = &operator|;
	}
	else if (oper == "XOR")
	{
		operate = &operator^;
	}
	return operate;
}
