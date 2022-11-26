#include <iostream>
#include <vector>
#include <thread>
#include <future>
#include <cmath>

using namespace std;

template<typename Iterator, typename F>
void parallel_for_each(Iterator first, Iterator last, F sroot)
{
	unsigned long const length = distance(first, last);
	unsigned long const max_chunk_size = 2;
    if (length <= max_chunk_size)
	{
		for_each(first, last, sroot);
	}
    else
    {
		Iterator mid_point = first;
		advance(mid_point, length / 2);
		future<void> res = async(parallel_for_each<Iterator, F>, first, mid_point, sroot);
		parallel_for_each(mid_point, last, sroot);
	}
}

void sroot(int &num)
{
    if (num > 0) num = sqrt(num);
}

int main()
{
    vector<int> vec(10, 9);
    parallel_for_each(vec.begin(),vec.end(),sroot);
    for (int n : vec)
    {
        cout << n << " ";
    }
    cout << endl;
    return 0;
}
