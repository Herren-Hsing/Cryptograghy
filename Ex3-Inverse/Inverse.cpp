#include <iostream>
using namespace std;
int main()
{
	int a, p;
	cin >> a >> p;
	if (a < 0)
	{
		a = (a + p) % p;
	}
	int t0 = 0, t1 = 1;
	int r0 = p, r1 = a;
	int q1, t2, r2;
	while (r1 != 0)
	{
		q1 = r0 / r1;
		r2 = r0 - q1 * r1;
		t2 = t0 - q1 * t1;

		t0 = t1;
		r0 = r1;
		t1 = t2;
		r1 = r2;
	}
	if (t0 < 0)
	{
		cout << (t0 + p) % p;
	}
	else
	{
		cout << t0 % p;
	}
}
