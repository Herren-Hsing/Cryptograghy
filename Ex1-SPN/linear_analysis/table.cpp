#include <iostream>
#include <iomanip>
#include <bitset>
using namespace std;
const int size = 16;
string X[size] = {"0000", "0001", "0010", "0011",
				  "0100", "0101", "0110", "0111",
				  "1000", "1001", "1010", "1011",
				  "1100", "1101", "1110", "1111"};
string Y[size] = {"1110", "0100", "1101", "0001",
				  "0010", "1111", "1011", "1000",
				  "0011", "1010", "0110", "1100",
				  "0101", "1001", "0000", "0111"};
int table[size][size] = {0};
char or_bit(char a, char b)
{
	if (a == '0' || b == '0')
		return '0';
	return '1';
}
int countOnes(string str, int len)
{
	int count = 0;
	for (int i = 0; i < len; i++)
	{
		if (str[i] == '1')
		{
			count++;
		}
	}
	return count;
}
void output_table()
{
	cout << "    ";
	for (int j = 0; j < size; j++)
	{
		cout << setw(3) << j << " ";
	}
	cout << endl;

	for (int i = 0; i < size; i++)
	{
		cout << setw(3) << i << " ";
		for (int j = 0; j < size; j++)
		{
			cout << setw(3) << table[i][j] << " ";
		}
		cout << endl;
	}
}
int main()
{
	string l1, l2;
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			for (int k = 0; k < size; k++)
			{
				l1.clear();
				l2.clear();
				string i_string = bitset<4>(i).to_string();
				string j_string = bitset<4>(j).to_string();
				for (int m = 0; m < 4; m++)
				{
					l1 += or_bit(i_string[m], X[k][m]);
					l2 += or_bit(j_string[m], Y[k][m]);
				}
				if ((countOnes(l1, 4) + countOnes(l2, 4)) % 2 == 0)
				{
					table[i][j]++;
				}
			}
		}
	}
	output_table();
}