// Three different POSIX happy allocators for C++ STL objects and some
// measurements.


extern "C"
{
#include <sys/types.h>
#include <sys/mman.h>
}

#include <limits>
#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <boost/system/system_error.hpp>

namespace leimyalloc
{

template<typename T>
struct mmap_allocator
{
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;
	typedef T* pointer;
	typedef const T* const_pointer;
	typedef T& reference;
	typedef const T& const_reference;
	typedef T value_type;

	//rebind
	template<typename U>
	struct rebind
	{
		typedef mmap_allocator<U> other;
	};

	mmap_allocator() throw ()
	{
	}

	mmap_allocator(mmap_allocator const &) throw ()
	{
	}

	template<typename U>
	mmap_allocator(mmap_allocator<U> const &) throw ()
	{
	}

	~mmap_allocator() throw ()
	{
	}

	pointer address(reference value) const
	{
		return &value;
	}

	const_pointer address(const_reference value) const
	{
		return &value;
	}

	size_type max_size() const throw ()
	{
		return ::std::numeric_limits<size_type>::max() / sizeof(T);
	}

	pointer allocate(size_type num, void* hint = 0)
	{
		void* p = ::mmap(hint, num * sizeof(T), PROT_READ | PROT_WRITE,
				MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

		if (p == MAP_FAILED)
		{
			throw boost::system::system_error(boost::system::error_code(errno,
					boost::system::get_system_category()));
		}

		return reinterpret_cast<pointer> (p);
	}

	void deallocate(pointer p, size_type num)
	{
		::munmap(p, num * sizeof(T));
	}

	void construct(pointer p, const_reference value)
	{
		new (p) T(value);
	}

	void destroy(pointer p)
	{
		p->~T();
	}
};

template<typename T1, typename T2>
bool operator ==(mmap_allocator<T1> const&, mmap_allocator<T2> const&) throw ()
{
	return true;
}

template<typename T1, typename T2>
bool operator !=(mmap_allocator<T1> const&, mmap_allocator<T2> const&) throw ()
{
	return false;
}

}

#include <cstdlib>
#include <ctime>

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
	std::vector<int, leimyalloc::mmap_allocator<int> > v;
	v.reserve(v.max_size() / 4);

	for (size_t i(0); i < (v.max_size() / 4); ++i)
	{
		v.push_back(0);
	}
}
