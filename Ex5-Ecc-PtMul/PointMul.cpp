#include <iostream>
using namespace std;
long long a, b, p;
struct Point
{
	long long x;
	long long y;
	bool isInfinity = false;
};
// 快速乘，防止溢出和超时，类似快速幂
long long quickMultiply(long long x, long long m, long long n)
{
	bool changeSym = false;
	if (x == 0 || m == 0)
	{
		return 0;
	}
	if (x < 0)
	{
		x = -x;
		changeSym = changeSym ? false : true;
	}
	if (m < 0)
	{
		m = -m;
		changeSym = changeSym ? false : true;
	}
	long long res = 0;
	while (m > 0)
	{
		if (m & 1)
		{
			res = (res + x) % n;
		}
		x = (x + x) % n;
		m >>= 1;
	}
	if (changeSym)
	{
		return n - res;
	}
	return res;
}

// 快速幂
long long squareMultiply(long long a, long long m, long long n)
{
	bool symChange = false;
	if (a == 1)
	{
		return 1;
	}
	if (m == 0)
	{
		return 1;
	}
	if (a < 0)
	{
		a = -a;
		if (m % 2 != 0)
		{
			symChange = true;
		}
	}
	long long res = 1;
	while (m > 0)
	{
		if (m & 1)
		{
			res = quickMultiply(res, a, n);
		}
		a = quickMultiply(a, a, n);
		m >>= 1;
	}
	if (symChange)
	{
		return n - res;
	}
	return res;
}
Point addPoint(Point p1, Point p2)
{
	Point res = {0, 0};
	long long k, k1, k2, k2Inverse;
	// p1 or p2 is infinity
	if (p1.isInfinity || p2.isInfinity)
	{
		res = p1.isInfinity ? p2 : p1;
		return res;
	}
	// p1==-p2
	if ((p1.x == p2.x) && (p1.y != p2.y))
	{
		res.isInfinity = true;
		return res;
	}
	if (p1.x == p2.x)
	{
		long long tmp = quickMultiply(3, p1.x, p);
		k1 = (quickMultiply(p1.x, tmp, p) + a) % p;
		k2 = (quickMultiply(2, p1.y, p)) % p;
	}
	else
	{
		k1 = (p2.y - p1.y) % p;
		k2 = (p2.x - p1.x) % p;
	}
	while (k1 < 0)
	{
		k1 += p;
	}
	while (k2 < 0)
	{
		k2 += p;
	}
	k2Inverse = squareMultiply(k2, p - 2, p);
	k = quickMultiply(k1, k2Inverse, p);
	res.x = (quickMultiply(k, k, p) - p1.x - p2.x) % p;
	while (res.x < 0)
	{
		res.x += p;
	}
	long long tmp = p1.x - res.x;
	while (tmp < 0)
	{
		tmp += p;
	}
	res.y = (quickMultiply(k, tmp, p) - p1.y) % p;
	while (res.y < 0)
	{
		res.y += p;
	}
	return res;
}
Point mulPoint(Point pt, long long n)
{
	Point res = {0, 0};
	res.isInfinity = true;
	if (n == 0)
	{
		return res;
	}
	if (n == 1)
	{
		return pt;
	}
	long long i = 0;
	Point pp = pt;
	while (n != 0)
	{
		if (i == 0)
		{
			pp = pt;
		}
		else
		{
			pp = addPoint(pp, pp);
		}
		if (n & 1)
		{
			res = addPoint(res, pp);
		}
		n >>= 1;
		i++;
	}
	return res;
}
int main()
{
	long long x, y, k;
	cin >> a >> b >> p >> x >> y >> k;
	while (x < 0)
	{
		x = (x + p) % p;
	}
	while (y < 0)
	{
		y = (y + p) % p;
	}
	Point pt = {x, y};
	Point res = mulPoint(pt, k);
	if (res.isInfinity)
	{
		res.x = -1;
		res.y = -1;
	}
	cout << res.x << " " << res.y;
}