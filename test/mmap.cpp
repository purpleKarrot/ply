#include <vector>
#include <mmap_allocator.hpp>

template<int low, int high>
struct RandomGen
{
	RandomGen()
	{
		srand(time(0));
	}

	int operator ()() const
	{
		return rand() % high + low;
	}
};

// vector dumper

template<typename T, template<typename T> class alloc>
std::ostream& operator <<(std::ostream & os,
		std::vector<T, alloc<T> > const & v)
{
	std::copy(v.begin(), v.end(), std::ostream_iterator<T>(os, " "));
	return os;
}

int main()
{
	//	std::vector<int> v1(1073741823);
	//	std::vector<int, leimyalloc::mmap_allocator<int> > v2(100);
	//
	//	std::cout << v1.max_size() << std::endl;
	//	std::cout << v2.max_size() << std::endl;
	//
	//	// fill
	//	std::generate(v1.begin(), v1.end(), RandomGen<0, 200> ());
	//	std::generate(v2.begin(), v2.end(), RandomGen<0, 200> ());
	//
	//	std::cout << v1 << std::endl;
	//	std::cout << v2 << std::endl;

	//std::vector<int> v;
	std::vector<int, mmap_allocator<int> > v;
	v.reserve(v.max_size() / 4);

	for (size_t i(0); i < (v.max_size() / 4); ++i)
	{
		v.push_back(0);
	}
}
