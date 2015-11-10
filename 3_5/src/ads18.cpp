#include <iostream>
#include <limits.h>

using namespace std;

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

void min2(pair_t a, pair_t b, int &min1, int &min2)
{
	if (a.min1 <= b.min1)
	{
		min1 = a.min1;

		if (a.min2 <= b.min1 && a.min2 != a.min1)
		{
			min2 = a.min2;
		}
		else if (a.min2 > b.min1 && b.min1 != a.min1)
		{
			min2 = b.min1;
		}
		else
		{
			min2 = b.min2;
		}
	}
	else
	{
		min1 = b.min1;

		if (b.min2 <= a.min1 && b.min2 != b.min1)
		{
			min2 = b.min2;
		}
		else if (b.min2 > a.min1 && a.min1 != b.min1)
		{
			min2 = a.min1;
		}
		else
		{
			min2 = a.min2;
		}
	}
}

int RMQUp(pair_t *a, int n, int l, int r)
{
	pair_t min(INT_MAX, INT_MAX);

    l += n - 1;
    r += n - 1;

    while( l <= r )
    {
        if(!(l & 1))
        {
        	min2(a[l], min, min.min1, min.min2);
        }

        if(r & 1)
        {
        	min2(a[r], min, min.min1, min.min2);
        }

        if (r - 2 < 0) break;

        l = (l) / 2;
        r = (r - 2) / 2;
    }

    return min.min2;
}

int main() {
	int n;

	std::cin >> n;

	int m;

	std::cin >> m;

	int full_n;
	int levels = 1;

	for (full_n = 1; full_n < n; full_n *= 2, ++levels) { }

	pair_t *a = new pair_t[2 * full_n - 1];

	for (int i = full_n - 1; i < 2 * full_n - 1; ++i)
	{
		if (i - (full_n - 1) < n)
		{
			int value;

			std::cin >> value;

			a[i] = pair_t(value, INT_MAX);
		}
		else
		{
			a[i] = pair_t(INT_MAX, INT_MAX);
		}
	}

	for (int j = levels - 2; j >= 0; --j)
	{
		int current_full_n = full_n >> (levels - j - 1);

		for (int i = current_full_n - 1; i < 2 * current_full_n - 1; ++i)
		{
			int min1, min2;

			if (a[2 * i  + 1].min1 <= a[2 * i  + 2].min1)
			{
				if (a[2 * i  + 1].min2 <= a[2 * i  + 2].min1)
				{
					min1 = a[2 * i  + 1].min1;
					min2 = a[2 * i  + 1].min2;
				}
				else
				{
					min1 = a[2 * i  + 1].min1;
					min2 = a[2 * i  + 2].min1;
				}
			}
			else
			{
				if (a[2 * i  + 1].min1 <= a[2 * i  + 2].min2)
				{
					min1 = a[2 * i  + 2].min1;
					min2 = a[2 * i  + 1].min1;
				}
				else
				{
					min1 = a[2 * i  + 2].min1;
					min2 = a[2 * i  + 2].min2;
				}
			}

			a[i] = pair_t(min1, min2);
		}
	}

	for (int i = 0; i < m; ++i)
	{
		int l;

		std::cin >> l;

		int r;

		std::cin >> r;

		std::cout << RMQUp(a, full_n, l - 1, r - 1) << std::endl;
	}

	return 0;
}
