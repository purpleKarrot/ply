#include <ply/types.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/fusion/adapted/struct/define_struct.hpp>

#include <boost/scoped_array.hpp>

template<typename Rule>
Rule ascii_omit(ply::scalar const& scalar)
{
	namespace qi = boost::spirit::qi;

	switch (scalar)
	{
	case ply::uint8:
		return qi::omit[qi::uint_parser<unsigned char>()];
	case ply::uint16:
		return qi::omit[qi::ushort_];
	case ply::uint32:
		return qi::omit[qi::uint_];
	case ply::uint64:
		return qi::omit[qi::ulong_long];
	case ply::int8:
		return qi::omit[qi::int_parser<char>()];
	case ply::int16:
		return qi::omit[qi::short_];
	case ply::int32:
		return qi::omit[qi::int_];
	case ply::int64:
		return qi::omit[qi::long_long];
	case ply::float32:
		return qi::omit[qi::float_];
	case ply::float64:
		return qi::omit[qi::double_];
	}
}

template<typename Rule, typename Semantic>
Rule ascii_scalar(ply::scalar const& scalar, Semantic semantic)
{
	namespace qi = boost::spirit::qi;

	switch (scalar)
	{
	case ply::uint8:
		return qi::uint_parser<unsigned char>()[semantic];
	case ply::uint16:
		return qi::ushort_[semantic];
	case ply::uint32:
		return qi::uint_[semantic];
	case ply::uint64:
		return qi::ulong_long[semantic];
	case ply::int8:
		return qi::int_parser<char>()[semantic];
	case ply::int16:
		return qi::short_[semantic];
	case ply::int32:
		return qi::int_[semantic];
	case ply::int64:
		return qi::long_long[semantic];
	case ply::float32:
		return qi::float_[semantic];
	case ply::float64:
		return qi::double_[semantic];
	}
}

BOOST_FUSION_DEFINE_STRUCT(, vertex,
		(float, x)
		(float, y)
		(float, z)
)

BOOST_AUTO_TEST_CASE(semantic)
{
	namespace ph = boost::phoenix;
	namespace qi = boost::spirit::qi;
	namespace ascii = boost::spirit::ascii;
	using namespace qi::labels;

	typedef std::string::iterator iterator;
	typedef qi::rule<iterator, void(vertex&), ascii::space_type> rule;
	typedef qi::rule<iterator, vertex(), ascii::space_type> grammar;

	std::string string = "1.5 2.5 3.5";
	iterator f = string.begin();
	iterator l = string.end();

	boost::scoped_array<rule> rules(new rule[string.size()]);

	grammar g = qi::eps;

	for (int i = 0; i < 3; ++i)
	{
		rules[i] = ascii_omit<rule> (ply::float32);
		g = g.copy() > rules[i](_val);
	}

	{
		rules[0] = ascii_scalar<rule> (ply::float32, ph::at_c<0>(_r1) = _1);
		rules[1] = ascii_scalar<rule> (ply::float32, ph::at_c<1>(_r1) = _1);
		rules[2] = ascii_scalar<rule> (ply::float32, ph::at_c<2>(_r1) = _1);
	}

	vertex v;
	qi::phrase_parse(f, l, g, ascii::space, v);

	std::cout << v.x << std::endl;
	std::cout << v.y << std::endl;
	std::cout << v.z << std::endl;
}
