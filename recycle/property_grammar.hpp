/*
 * property_grammar.hpp
 *
 *  Created on: 21.10.2010
 *      Author: daniel
 */

#ifndef PLY_PROPERTY_GRAMMAR_HPP
#define PLY_PROPERTY_GRAMMAR_HPP

#include <ply/types.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/fusion/sequence/intrinsic/at.hpp>
#include <boost/fusion/mpl/size.hpp>
#include <boost/mpl/range_c.hpp>
#include <boost/mpl/for_each.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <iostream>

namespace qi = boost::spirit::qi;

template<typename Iterator, typename Element, typename Skipper>
class property_grammar:
	public boost::spirit::qi::grammar<Iterator, Skipper>
{
	BOOST_STATIC_CONSTANT(int, size = boost::mpl::size<Element>::value);

	struct assign_rule
	{
		assign_rule(property_grammar& self) :
			self(self)
		{
		}

		template<typename I>
		void operator()(I)
		{
			using namespace boost::fusion::extension;

			if(self.name() == struct_member_name<Element, I::value>::call())
			{
				typedef typename boost::fusion::result_of::at<Element, I>::type type;

				using namespace qi::labels;
				self.start = qi::float_[boost::phoenix::ref(boost::fusion::at<I>(self.element)) = _1];
			}
		}

		property_grammar& self;
	};

public:
	property_grammar(Element& element, ply::property const& property) :
		property_grammar::base_type(start, property.name), element(element)
	{
		typedef boost::mpl::range_c<int, 0, size> indices;
		boost::mpl::for_each<indices>(assign_rule(*this));
	}

private:
	boost::spirit::qi::rule<Iterator, Skipper> start;
	Element& element;
};

#endif /* PLY_PROPERTY_GRAMMAR_HPP */
