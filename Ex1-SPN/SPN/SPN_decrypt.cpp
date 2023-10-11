#include <iostream>
#include <string>
using namespace std;
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

string Reverse_P_box(string s, int nr)
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

int main()
{
	string y, k, u, w, v, x;
	cin >> y >> k;
	int len = 16;
	int nr = 4;
	int index = nr * 4;
	for (int i = nr; i > 0; i--)
	{
		v.clear();
		if (i != nr)
		{
			v = Reverse_P_box(w, nr);
		}
		else
		{
			for (int j = 0; j < len; j++)
			{
				if (y[j] == k[index])
				{
					v += '0';
				}
				else
				{
					v += '1';
				}
				index++;
			}
		}
		u = Reverse_S_box(v, nr);
		int index = (i - 1) * 4;
		w.clear();
		for (int j = 0; j < len; j++)
		{
			if (u[j] == k[index])
			{
				w += '0';
			}
			else
			{
				w += '1';
			}
			index++;
		}
	}
	x = w;
	cout << x;
}