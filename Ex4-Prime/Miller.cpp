#include <iostream>
#include <random>
#include <chrono>
using namespace std;

long long k = 0;
long long getDecomposition(long long n)
{
	while (!(n & 1))
	{
		n >>= 1;
		k++;
	}
	return n;
}
long long quickMultiply(long long a, long long m, long long n)
{
	long long res = 0;
	while (m > 0)
	{
		if (m & 1)
			res = (res + a) % n;
		a = (a + a) % n;
		m >>= 1;
	}
	return res;
}

long long getRandom(long long min, long long max)
{
	auto seed = chrono::system_clock::now().time_since_epoch().count();
	default_random_engine generator(seed);
	uniform_int_distribution<long long> distribution(min, max);
	return distribution(generator);
}

long long squareMultiply(long long a, long long m, long long n)
{
	long long res = 1;
	while (m > 0)
	{
		if (m & 1)
			res = quickMultiply(res, a, n);
		a = quickMultiply(a, a, n);
		m >>= 1;
	}
	return res;
}

int main()
{
	long long n;
	cin >> n;
	if ((n % 2 == 0 && n > 2) || n < 2)
	{
		cout << "No";
		return 0;
	}
	long long m = getDecomposition(n - 1);
	long long a = getRandom(1, n - 1);
	// 计算 a^m mod n
	long long b = squareMultiply(a, m, n);
	if (b == 1)
	{
		cout << "Yes";
		return 0;
	}
	for (int i = 0; i < k; i++)
	{
		if ((b % n) == n - 1)
		{
			cout << "Yes";
			return 0;
		}
		b = quickMultiply(b, b, n);
	}
	cout << "No";
	return 0;
}