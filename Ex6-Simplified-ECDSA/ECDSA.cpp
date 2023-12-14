#include <iostream>
using namespace std;
long long a = 1, b = 6, p = 11, q = 13;
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
	while (n != 0)
	{
		if (i)
		{
			pt = addPoint(pt, pt);
		}
		if (n & 1)
		{
			res = addPoint(res, pt);
		}
		n >>= 1;
		i++;
	}
	return res;
}

long long getInverse(long long a, long long p)
{
	long long t0 = 0, t1 = 1;
	long long r0 = p, r1 = a;
	long long q1, t2, r2;
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
	return (t0 + p) % p;
}

long long twoPow(int exponent)
{
	if (exponent < 0)
	{
		return 0;
	}
	else
	{
		return 1LL << exponent;
	}
}

int main()
{
	long long x0, y0, m, x, k;
	cin >> x0 >> y0 >> m >> x >> k;
	while (x0 < 0)
	{
		x0 = (x0 + p) % p;
	}
	while (y0 < 0)
	{
		y0 = (y0 + p) % p;
	}
	Point pt = {x0, y0};
	Point res = mulPoint(pt, k);
	long long r = res.x % q;
	long long s = (twoPow(x) + m * r) % q;
	long long k1 = getInverse(k, q);
	cout << r << " " << k1 * s % q;
}