#include <iostream>
#include <string>
using namespace std;
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

int main()
{
	string x, w, k, u, s_res, p_res;
	cin >> x >> k;
	int len = 16;
	int nr = 4;
	w = x;
	for (int i = 0; i <= nr; i++)
	{
		int index = i * 4;
		u.clear();
		for (int j = 0; j < len; j++)
		{
			if (w[j] == k[index])
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
		w.clear();
		w = p_res;
	}
	cout << u;
}