//

#include <boost/fusion/mpl/size.hpp>
#include <boost/mpl/range_c.hpp>
#include <boost/mpl/for_each.hpp>

/*
 * create a rule based on:
 * format
 * property
 * Element
 */

//for each property generate rule
//


//generate rule depending on property, ignoring attribute

void ascii_ignore_rule(ply::property const& property)
{

}

// generate the rule for a single property
template<typename Iterator, typename Skipper, typename Element>
boost::spirit::qi::rule<Iterator, void(Element&), Skipper> //
ascii_rule_factory(Element& element, ply::property const& property)
{
	typedef boost::mpl::size<Element>::type size;
	typedef boost::mpl::range_c<int, 0, size::value> indices;

	qi::rule<Iterator, void(Element&), Skipper> rule;

	boost::mpl::for_each<indices>(assign_rule(rule));
	return rule;
}

template<typename Rule, int I, typename Semantic>
Rule ascii_scalar_with_semantic(ply::scalar const& scalar, Semantic semantic)
{
	using namespace boost::phoenix;

	switch (scalar)
	{
	case ply::uint8:
		return qi::uint_parser<unsigned char>()[at_c<I> (_r1) = _1];
	case ply::uint16:
		return qi::ushort_[at_c<I> (_r1) = _1];
	case ply::uint32:
		return qi::uint_[at_c<I> (_r1) = _1];
	case ply::uint64:
		return qi::ulong_long[at_c<I> (_r1) = _1];
	case ply::int8:
		return qi::int_parser<char>()[at_c<I> (_r1) = _1];
	case ply::int16:
		return qi::short_[at_c<I> (_r1) = _1];
	case ply::int32:
		return qi::int_[at_c<I> (_r1) = _1];
	case ply::int64:
		return qi::long_long[at_c<I> (_r1) = _1];
	case ply::float32:
		return qi::float_[at_c<I> (_r1) = _1];
	case ply::float64:
		return qi::double_[at_c<I> (_r1) = _1];
	}
}

template<typename Rule, >
Rule ascii_scalar_without_semantic(ply::scalar const& scalar)
{
	using namespace boost::phoenix;

	switch (scalar)
	{
	case ply::uint8:
		return qi::uint_parser<unsigned char>()[at_c<I> (_r1) = _1];
	case ply::uint16:
		return qi::ushort_[at_c<I> (_r1) = _1];
	case ply::uint32:
		return qi::uint_[at_c<I> (_r1) = _1];
	case ply::uint64:
		return qi::ulong_long[at_c<I> (_r1) = _1];
	case ply::int8:
		return qi::int_parser<char>()[at_c<I> (_r1) = _1];
	case ply::int16:
		return qi::short_[at_c<I> (_r1) = _1];
	case ply::int32:
		return qi::int_[at_c<I> (_r1) = _1];
	case ply::int64:
		return qi::long_long[at_c<I> (_r1) = _1];
	case ply::float32:
		return qi::float_[at_c<I> (_r1) = _1];
	case ply::float64:
		return qi::double_[at_c<I> (_r1) = _1];
	}
}
