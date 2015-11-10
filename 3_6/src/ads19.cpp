#include <iostream>
#include <limits.h>
#include <queue>

using namespace std;

int rmq(int *a, int n, int l, int r, std::queue<int> &viewed)
{
	int min = INT_MAX;
	int last_l, last_r;

    l += n - 1;
    r += n - 1;

    while (l <= r)
    {
    	viewed.push(l);
    	viewed.push(r);

        if(!(l & 1))
        {
        	min = std::min(a[l], min);
        	//if (l < n - 1) a[l] = std::min(a[2 * l + 1], a[2 * l  + 2]);
        }

        if(r & 1)
        {
        	min = std::min(a[r], min);
        	//if (r < n - 1) a[r] = std::min(a[2 * r + 1], a[2 * r  + 2]);
        }

        last_l = l;
        last_r = r;

        if (r - 1 - 1 < 0) break;

        l = (l - 1 + 1) / 2;
        r = (r - 1 - 1) / 2;
    }

    l = last_l;
    r = last_r;

    while (l <= r)
    {
    	l = (l - 1) / 2;
    	r = (r - 1) / 2;

    	viewed.push(l);
    	//a[l] = std::min(a[2 * l + 1], a[2 * l  + 2]);

    	if (r != l)
		{
    		viewed.push(r);
    		//a[r] = std::min(a[2 * r + 1], a[2 * r  + 2]);
		}

    	if (l == 0 || r == 0)
    	{
    		break;
    	}
    }

    return min;
}

int main() {
	int n;

	std::cin >> n;

	int full_n;
	int levels = 1;

	for (full_n = 1; full_n < n; full_n *= 2, ++levels) { }

	int *a = new int[2 * full_n - 1];

	for (int i = full_n - 1; i < 2 * full_n - 1; ++i)
	{
		if (i - (full_n - 1) < n - 1)
		{
			int value;

			std::cin >> value;

			a[i] = value;
		}
		else if (i - (full_n - 1) == n - 1)
		{
			a[i] = 0;
		}
		else
		{
			a[i] = INT_MAX;
		}
	}

	int capacity;

	std::cin >> capacity;

	for (int i = full_n - 1; i - (full_n - 1) < n; ++i)
	{
		a[i] = capacity - a[i];
	}

	for (int j = levels - 2; j >= 0; --j)
	{
		int current_full_n = full_n >> (levels - j - 1);

		for (int i = current_full_n - 1; i < 2 * current_full_n - 1; ++i)
		{
			a[i] = std::min(a[2 * i  + 1], a[2 * i  + 2]);
		}
	}

	int m;

	std::cin >> m;

	for (int q = 0; q < m; ++q)
	{
		int l;

		std::cin >> l;

		int r;

		std::cin >> r;

		int count;

		std::cin >> count;

		std::queue<int> viewed;

		int free = rmq(a, full_n, l, r - 1, viewed);

		if (free >= count)
		{
			for (int j = l; j < r; ++j)
			{
				a[full_n - 1 + j] -= count;
			}

			while (viewed.size())
			{
				int vertex = viewed.front();

				viewed.pop();

				if (vertex < full_n - 1)
				{
					a[vertex] = std::min(a[2 * vertex + 1], a[2 * vertex  + 2]);
				}
			}

/*
			for (int j = levels - 2; j >= 0; --j)
			{
				int from = (full_n - 1 + l - (1 << (levels - 1 - j)) + 1) / (1 << (levels - 1 - j));
				int to = (full_n - 1 + r - 1 - (1 << (levels - 1 - j)) + 1) / (1 << (levels - 1 - j));

				for (int i = from; i <= to; ++i)
				{
					a[i] = std::min(a[2 * i + 1], a[2 * i  + 2]);
				}
			}
*/
		}
		else
		{
			std::cout << q << " ";
		}
	}

	return 0;
}
