#include <iostream>
#include <limits.h>

struct pair_t {
	int min1;
	int min2;
	pair_t() { }
	pair_t(int _min1, int _min2)
	{
		min1 = _min1;
		min2 = _min2;
	}
};

void get_pairs_min(pair_t l, pair_t r, pair_t &result)
{
	if (l.min1 <= r.min1)
	{
		result.min1 = l.min1;

		if ((r.min1 <= l.min2 || l.min2 == result.min1) && r.min1 != result.min1)
		{
			result.min2 = r.min1;
		}
		else if (l.min2 <= r.min2 && l.min2 != result.min1)
		{
			result.min2 = l.min2;
		}
		else
		{
			result.min2 = r.min2;
		}
	}
	else
	{
		result.min1 = r.min1;

		if ((l.min1 <= r.min2 || r.min2 == result.min1) && l.min1 != result.min1)
		{
			result.min2 = l.min1;
		}
		else if (r.min2 <= l.min2 && r.min2 != result.min1)
		{
			result.min2 = r.min2;
		}
		else
		{
			result.min2 = l.min2;
		}
	}
}

void fill_first_row(pair_t **ST, int n)
{
	ST[0] = new pair_t[n];

	for (int i = 0; i < n; ++i)
	{
		int value;

		std::cin >> value;

		ST[0][i] = pair_t(value, INT_MAX);
	}
}

pair_t** build_table(int n)
{
	int levels;
	for (levels = 0; (1 << levels) <= n; ++levels) { }

	pair_t **ST = new pair_t*[levels];

	fill_first_row(ST, n);

	int prev_length = n;

	for (int k = 1; k <= levels; ++k)
	{
		int length = 0;
		int delta = (1 << (k - 1));

		ST[k] = new pair_t[n];

		for (int i = 0; i + delta < prev_length; ++i, ++length)
		{
			pair_t min(INT_MAX, INT_MAX);

			get_pairs_min(ST[k - 1][i], ST[k - 1][i + delta], min);

			ST[k][i] = min;
		}

		prev_length = length;
	}

	return ST;
}

int get_second_min(pair_t **ST, int l, int r)
{
	int k;
	for (k = 1; (r - l) + 1 > (1 << k) - 1; ++k) { }

	--k;

	int k_l = l;
	int k_r = r - (1 << k) + 1;

	pair_t min(INT_MAX, INT_MAX);

	if (k_r > k_l)
	{
		get_pairs_min(ST[k][k_l], ST[k][k_r], min);
	}
	else
	{
		get_pairs_min(ST[k][k_l], min, min);
	}

	return min.min2;
}

int main() {
	int n;

	std::cin >> n;

	int m;

	std::cin >> m;

	pair_t **ST = build_table(n);

	for (int i = 0; i < m; ++i)
	{
		int l;

		std::cin >> l;

		int r;

		std::cin >> r;

		std::cout << get_second_min(ST, l - 1, r - 1) << std::endl;
	}

	return 0;
}
