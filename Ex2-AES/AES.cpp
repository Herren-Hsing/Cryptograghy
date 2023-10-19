#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
using namespace std;
/*
000102030405060708090a0b0c0d0e0f
00112233445566778899aabbccddeeff
69C4E0D86A7B0430D8CDB78070B4C55A
*/
string keys[11];
string S_Box[16][16] = {
	{"63", "7C", "77", "7B", "F2", "6B", "6F", "C5", "30", "01", "67", "2B", "FE", "D7", "AB", "76"},
	{"CA", "82", "C9", "7D", "FA", "59", "47", "F0", "AD", "D4", "A2", "AF", "9C", "A4", "72", "C0"},
	{"B7", "FD", "93", "26", "36", "3F", "F7", "CC", "34", "A5", "E5", "F1", "71", "D8", "31", "15"},
	{"04", "C7", "23", "C3", "18", "96", "05", "9A", "07", "12", "80", "E2", "EB", "27", "B2", "75"},
	{"09", "83", "2C", "1A", "1B", "6E", "5A", "A0", "52", "3B", "D6", "B3", "29", "E3", "2F", "84"},
	{"53", "D1", "00", "ED", "20", "FC", "B1", "5B", "6A", "CB", "BE", "39", "4A", "4C", "58", "CF"},
	{"D0", "EF", "AA", "FB", "43", "4D", "33", "85", "45", "F9", "02", "7F", "50", "3C", "9F", "A8"},
	{"51", "A3", "40", "8F", "92", "9D", "38", "F5", "BC", "B6", "DA", "21", "10", "FF", "F3", "D2"},
	{"CD", "0C", "13", "EC", "5F", "97", "44", "17", "C4", "A7", "7E", "3D", "64", "5D", "19", "73"},
	{"60", "81", "4F", "DC", "22", "2A", "90", "88", "46", "EE", "B8", "14", "DE", "5E", "0B", "DB"},
	{"E0", "32", "3A", "0A", "49", "06", "24", "5C", "C2", "D3", "AC", "62", "91", "95", "E4", "79"},
	{"E7", "C8", "37", "6D", "8D", "D5", "4E", "A9", "6C", "56", "F4", "EA", "65", "7A", "AE", "08"},
	{"BA", "78", "25", "2E", "1C", "A6", "B4", "C6", "E8", "DD", "74", "1F", "4B", "BD", "8B", "8A"},
	{"70", "3E", "B5", "66", "48", "03", "F6", "0E", "61", "35", "57", "B9", "86", "C1", "1D", "9E"},
	{"E1", "F8", "98", "11", "69", "D9", "8E", "94", "9B", "1E", "87", "E9", "CE", "55", "28", "DF"},
	{"8C", "A1", "89", "0D", "BF", "E6", "42", "68", "41", "99", "2D", "0F", "B0", "54", "BB", "16"}};
string RCon[10] = {"01", "02", "04", "08", "10", "20", "40", "80", "1b", "36"};
int row_shift[16] = {0, 5, 10, 15, 4, 9, 14, 3, 8, 13, 2, 7, 12, 1, 6, 11};

int to_num(char s)
{
	if (s >= '0' && s <= '9')
	{
		return s - '0';
	}
	else if (s >= 'A' && s <= 'F')
	{
		return s - 'A' + 10;
	}
	else
	{
		return s - 'a' + 10;
	}
}

char to_char(int num)
{
	if (num <= 9)
	{
		return num + '0';
	}
	else
	{
		return num - 10 + 'a';
	}
}

char xor_hex_char(char a, char b)
{
	int num1 = to_num(a);
	int num2 = to_num(b);
	int res = num1 ^ num2;
	return to_char(res);
}

string xor_hex(string a, string b)
{
	int len = a.length();
	string res;
	for (int i = 0; i < len; i++)
	{
		res += xor_hex_char(a[i], b[i]);
	}
	return res;
}

void sub_bytes(char &first, char &second, int row, int column)
{
	first = S_Box[row][column][0];
	second = S_Box[row][column][1];
}

void key_expansion(string key, int Nr)
{
	// w: 8位 16进制
	string w[4];
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			w[i] += key[8 * i + j];
		}
	}
	string tmp; // 8位16进制，32bits
	// 移位
	for (int i = 0; i < 6; i++)
	{
		tmp += w[3][i + 2];
	}
	tmp = tmp + w[3][0] + w[3][1];
	// S盒
	for (int i = 0; i < 4; i++)
	{
		int row = to_num(tmp[2 * i]);
		int column = to_num(tmp[2 * i + 1]);
		sub_bytes(tmp[2 * i], tmp[2 * i + 1], row, column);
	}
	// 异或RCon
	tmp[0] = xor_hex_char(tmp[0], RCon[Nr][0]);
	tmp[1] = xor_hex_char(tmp[1], RCon[Nr][1]);
	string res[4];
	res[0] += xor_hex(w[0], tmp);
	res[1] += xor_hex(w[1], res[0]);
	res[2] += xor_hex(w[2], res[1]);
	res[3] += xor_hex(w[3], res[2]);
	keys[Nr + 1] = keys[Nr + 1] + res[0] + res[1] + res[2] + res[3];
}

int hex_string_to_num(string x)
{
	istringstream hexStream(x);
	int num;
	hexStream >> hex >> num;
	return num;
}

string num_to_hex_string(int x)
{
	stringstream stream;
	stream << hex << setw(2) << setfill('0') << x;
	return stream.str();
}

int mul(int a, int b)
{
	if (a == 2)
	{
		if ((b & 128) != 128)
		{
			return b << 1;
		}
		else
		{
			return ((b << 1) & ((1 << 8) - 1)) ^ 0x1b;
		}
	}
	else if (a == 3)
	{
		return mul(2, b) ^ b;
	}
	else
	{
		return 0;
	}
}
void mul_matrix(int num[4])
{
	int res[4];
	res[0] = mul(2, num[0]) ^ mul(3, num[1]) ^ num[2] ^ num[3];
	res[1] = num[0] ^ mul(2, num[1]) ^ mul(3, num[2]) ^ num[3];
	res[2] = num[0] ^ num[1] ^ mul(2, num[2]) ^ mul(3, num[3]);
	res[3] = mul(3, num[0]) ^ num[1] ^ num[2] ^ mul(2, num[3]);
	for (int i = 0; i < 4; i++)
	{
		num[i] = res[i];
	}
}

void mix_columns(string a[4])
{
	int num[4];
	for (int i = 0; i < 4; i++)
	{
		num[i] = hex_string_to_num(a[i]);
	}
	mul_matrix(num);
	for (int i = 0; i < 4; i++)
	{
		a[i] = num_to_hex_string(num[i]);
	}
}

int main()
{
	// x和key:32位16进制, 128bits
	string x;
	cin >> keys[0] >> x;

	for (int i = 0; i < 10; i++)
	{
		key_expansion(keys[i], i);
	}

	x = xor_hex(x, keys[0]); // 轮密钥加

	for (int i = 0; i < 10; i++)
	{

		// sub_bytes
		for (int j = 0; j < 16; j++)
		{
			int row = to_num(x[2 * j]);
			int column = to_num(x[2 * j + 1]);
			sub_bytes(x[2 * j], x[2 * j + 1], row, column);
		}

		// shift_rows
		string shifted = x;
		for (int j = 0; j < 16; j++)
		{
			shifted[j * 2] = x[row_shift[j] * 2];
			shifted[j * 2 + 1] = x[row_shift[j] * 2 + 1];
		}

		// mix_columns
		string mixed = shifted;
		if (i != 9)
		{
			mixed.clear();
			for (int k = 0; k < 4; k++)
			{
				string tmp[4];
				for (int j = 0; j < 4; j++)
				{
					tmp[j] = tmp[j] + shifted[8 * k + j * 2] + shifted[8 * k + j * 2 + 1];
				}
				mix_columns(tmp);
				mixed = mixed + tmp[0] + tmp[1] + tmp[2] + tmp[3];
			}
		}

		// add_round_key
		x = xor_hex(mixed, keys[i + 1]);
	}
	int len = x.length();
	for (int i = 0; i < len; i++)
	{
		if (x[i] >= 'a' && x[i] <= 'f')
		{
			x[i] = x[i] - 'a' + 'A';
		}
	}
	cout << x;
	return 0;
}
