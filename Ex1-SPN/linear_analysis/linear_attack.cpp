#include <iostream>
#include <bitset>
using namespace std;
const int size = 8000;

string S_box(string u, int nr)
{
	string res;
	string mapping[] = {
		"1110", "0100", "1101", "0001",
		"0010", "1111", "1011", "1000",
		"0011", "1010", "0110", "1100",
		"0101", "1001", "0000", "0111"};

	for (int i = 0; i < nr; i++)
	{
		string tmp = u.substr(i * 4, 4);
		res += mapping[stoi(tmp, 0, 2)];
	}

	return res;
}

string P_box(string s, int nr)
{
	string res;
	int mapping[] = {
		0, 4, 8, 12,
		1, 5, 9, 13,
		2, 6, 10, 14,
		3, 7, 11, 15};

	for (int i = 0; i < nr * 4; i++)
	{
		res += s[mapping[i]];
	}

	return res;
}

string SPN_Encrypt(string x, string k)
{
	string u, s_res, p_res;
	int len = 16;
	int nr = 4;
	for (int i = 0; i <= nr; i++)
	{
		int index = i * 4;
		u.clear();
		for (int j = 0; j < len; j++)
		{
			if (x[j] == k[index])
			{
				u += '0';
			}
			else
			{
				u += '1';
			}
			index++;
		}
		if (i == nr)
			break;
		s_res = S_box(u, nr);
		if (i != nr - 1)
		{
			p_res = P_box(s_res, nr);
		}
		else
		{
			p_res = s_res;
		}
		x.clear();
		x = p_res;
	}
	return u;
}

string Reverse_S_box(string u, int nr)
{
	string res;
	string mapping[] = {
		"1110", "0011", "0100", "1000",
		"0001", "1100", "1010", "1111",
		"0111", "1101", "1001", "0110",
		"1011", "0010", "0000", "0101"};

	for (int i = 0; i < nr; i++)
	{
		string tmp = u.substr(i * 4, 4);
		res += mapping[stoi(tmp, 0, 2)];
	}

	return res;
}

char nor(char a, char b)
{
	if (a == b)
		return '0';
	return '1';
}

void K24(string *plain, string *cipher, string *binaryArray, string &res2, string &res4)
{
	int count[16][16] = {0};
	string tmp1, tmp2, tmp3, tmp4;
	char z;
	char v[16] = {0}, u[16] = {0};
	for (int i = 0; i < size; i++)
	{
		for (int l1 = 0; l1 < 16; l1++)
		{
			for (int l2 = 0; l2 < 16; l2++)
			{
				for (int k = 0; k < 4; k++)
				{
					v[k + 4] = nor(binaryArray[l1][k], cipher[i][k + 4]);
					v[k + 12] = nor(binaryArray[l2][k], cipher[i][k + 12]);
				}
				tmp1.clear();
				tmp2.clear();
				for (int k = 0; k < 4; k++)
				{
					tmp1 += v[k + 4];
					tmp2 += v[k + 12];
				}
				tmp1 = Reverse_S_box(tmp1, 1);
				tmp2 = Reverse_S_box(tmp2, 1);
				for (int k = 0; k < 4; k++)
				{
					u[k + 4] = tmp1[k];
					u[k + 12] = tmp2[k];
				}
				z = nor(nor(nor(nor(nor(nor(plain[i][4], plain[i][6]), plain[i][7]), u[5]), u[7]), u[13]), u[15]);
				if (z == '0')
				{
					count[l1][l2]++;
				}
			}
		}
	}
	int max = -1;
	int a = 0, b = 0;
	for (int l1 = 0; l1 < 16; l1++)
	{
		for (int l2 = 0; l2 < 16; l2++)
		{
			count[l1][l2] = abs(count[l1][l2] - 4000);
			if (count[l1][l2] > max)
			{
				max = count[l1][l2];
				a = l1;
				b = l2;
			}
		}
	}
	res2 = bitset<4>(a).to_string();
	res4 = bitset<4>(b).to_string();
}

void K13(string *plain, string *cipher, string *binaryArray, string res2, string res4, string &res1, string &res3)
{
	int count1[16] = {0}, count3[16] = {0};
	string tmp1, tmp2, tmp3, tmp4;
	char z;
	char v[16] = {0}, u[16] = {0};
	for (int i = 0; i < size; i++)
	{
		cin >> plain[i] >> cipher[i];
	}
	for (int i = 0; i < size; i++)
	{
		for (int l1 = 0; l1 < 16; l1++)
		{
			for (int k = 0; k < 4; k++)
			{
				v[k] = nor(binaryArray[l1][k], cipher[i][k]);
				v[k + 8] = nor(binaryArray[l1][k], cipher[i][k + 8]);
				v[k + 4] = nor(res2[k], cipher[i][k + 4]);
				v[k + 12] = nor(res4[k], cipher[i][k + 12]);
			}
			tmp1.clear();
			tmp2.clear();
			tmp3.clear();
			tmp4.clear();
			for (int k = 0; k < 4; k++)
			{
				tmp1 += v[k];
				tmp2 += v[k + 4];
				tmp3 += v[k + 8];
				tmp4 += v[k + 12];
			}
			tmp1 = Reverse_S_box(tmp1, 1);
			tmp2 = Reverse_S_box(tmp2, 1);
			tmp3 = Reverse_S_box(tmp3, 1);
			tmp4 = Reverse_S_box(tmp4, 1);
			for (int k = 0; k < 4; k++)
			{
				u[k] = tmp1[k];
				u[k + 4] = tmp2[k];
				u[k + 8] = tmp3[k];
				u[k + 12] = tmp4[k];
			}
			z = nor(nor(nor(nor(nor(nor(nor(nor(nor(nor(nor(plain[i][8], plain[i][10]), plain[i][11]), u[4]), u[5]), u[6]), u[8]), u[9]), u[10]), u[12]), u[13]), u[14]);
			if (z == '0')
			{
				count3[l1]++;
			}
			z = nor(nor(nor(nor(nor(nor(nor(plain[i][4], plain[i][6]), plain[i][7]), u[1]), u[5]), u[7]), u[13]), u[15]);
			if (z == '0')
			{
				count1[l1]++;
			}
		}
	}
	int max1 = -1, max3 = -1;
	int a = 0, b = 0;
	for (int l1 = 0; l1 < 16; l1++)
	{
		count1[l1] = abs(count1[l1] - 4000);
		count3[l1] = abs(count3[l1] - 4000);
		if (count1[l1] > max1)
		{
			max1 = count1[l1];
			a = l1;
		}
		if (count3[l1] > max3)
		{
			max3 = count3[l1];
			b = l1;
		}
	}
	res1 = bitset<4>(a).to_string();
	res3 = bitset<4>(b).to_string();
}

string K_all(string *plain, string *cipher, string *binaryArray, string K5)
{
	string K;
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			for (int ii = 0; ii < 16; ii++)
			{
				for (int jj = 0; jj < 16; jj++)
				{
					K = binaryArray[i] + binaryArray[j] + binaryArray[ii] + binaryArray[jj] + K5;
					int k = 0;
					for (; k < 16; k++)
					{
						if (SPN_Encrypt(plain[k], K) != cipher[k])
						{
							break;
						}
					}
					if (k == 16)
					{
						return K;
					}
				}
			}
		}
	}
	return "failed";
}

int main()
{
	string binaryArray[16];
	for (int i = 0; i < 16; ++i)
	{
		binaryArray[i] += bitset<4>(i).to_string();
	}
	string plain[size], cipher[size];
	for (int i = 0; i < size; i++)
	{
		cin >> plain[i] >> cipher[i];
	}
	string res1, res2, res3, res4;
	K24(plain, cipher, binaryArray, res2, res4);
	K13(plain, cipher, binaryArray, res2, res4, res1, res3);
	string K5 = res1 + res2 + res3 + res4;
	cout << "K5 is " << K5 << endl;
	string K = K_all(plain, cipher, binaryArray, K5);
	cout << "K is " << K << endl;
}