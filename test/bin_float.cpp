/*
 * bin_float.cpp
 *
 *  Created on: 16.09.2010
 *      Author: daniel
 */

#include <boost/test/unit_test.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/home/phoenix/operator/self.hpp>
#include <boost/spirit/home/phoenix/object/reinterpret_cast.hpp>

namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;
namespace ph = boost::phoenix;
using namespace qi::labels;

BOOST_AUTO_TEST_CASE(bin_float)
{
	float v1[] =
	{ 50000.1f, 0.0023f, -234.456343462f };

	char *begin = (char*) v1, *end = ((char*) v1) + sizeof(v1);

	qi::rule<char*, float()> bin_float = qi::dword[_val
			= *ph::reinterpret_cast_<float*>(&_1)];

	qi::rule<char*, int()> my_int = bin_float;

	int value;
	while (begin != end && qi::parse(begin, end, my_int, value))
	{
		BOOST_MESSAGE(value);
	}
}
