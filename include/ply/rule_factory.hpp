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

template<typename Iterator, typename Skipper, typename Element>
qi::rule<Iterator, Skipper> ascii_factory(Element& dst,



template<typename Iterator, typename Skipper, typename Element>
qi::rule<Iterator, Skipper> ascii_rule_factory(Element& element,
		ply::property const& property)
{
	typedef boost::mpl::size<Element>::type size;
	typedef boost::mpl::range_c<int, 0, size::value> indices;

	qi::rule<Iterator, Skipper> rule;
	boost::mpl::for_each<indices>(assign_rule(rule));
	return rule;
}
