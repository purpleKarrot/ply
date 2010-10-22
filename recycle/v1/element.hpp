/*
 * element.hpp
 *
 *  Created on: Aug 26, 2010
 *      Author: danielp
 */

#ifndef PLY_V1_ELEMENT_HPP
#define PLY_V1_ELEMENT_HPP

#include <iostream>
#include <typeinfo>
#include <boost/fusion/sequence/intrinsic/at.hpp>
#include <boost/fusion/mpl/size.hpp>
#include <boost/mpl/range_c.hpp>
#include <boost/mpl/for_each.hpp>

template<typename T>
struct bar
{
	static const char* call()
	{
		return typeid(T).name();
	}
};

template<class T, std::size_t N>
struct bar<boost::array<T, N>&>
{
	static std::string call()
	{
		return std::string("list uchar ") + bar<T>::call();
	}
};

template<typename T, typename Alloc>
struct bar<std::vector<T, Alloc>&>
{
	static std::string call()
	{
		return std::string("list uchar ") + bar<T>::call();
	}
};

template<typename Seq>
struct foo
{
	template<typename I>
	void operator()(I i)
	{
		using namespace boost::fusion::extension;

		typedef typename boost::fusion::result_of::at<Seq, I>::type type;
		char const* name = struct_member_name<Seq, I::value>::call();

		std::cout << bar<type>::call() << " " << name << std::endl;
	}
};

namespace ply
{

template<typename Properties>
class element
{
	BOOST_STATIC_CONSTANT(int, size = boost::mpl::size<Properties>::value);

public:
	element()
	{
		typedef boost::mpl::range_c<int, 0, size> indices;

		boost::mpl::for_each<indices>(foo<Properties> ());
	}

private:
};

} // namespace ply

#endif /* PLY_V1_ELEMENT_HPP */
