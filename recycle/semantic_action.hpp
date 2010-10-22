/*
 * semantic_action.hpp
 *
 *  Created on: 21.10.2010
 *      Author: daniel
 */

#ifndef PLY_SEMANTIC_ACTION_HPP
#define PLY_SEMANTIC_ACTION_HPP

template<typename Element>
void semantic_action(std::string const& name)
{
	using namespace qi::labels;

	boost::phoenix::at_c<i>( _r1) = _1;

}

template<typename Iterator, typename Skipper>
struct vector_property_grammar: qi::grammar<Iterator, std::vector<int>(), qi::locals<std::size_t>, Skipper>
{
	vector_property_grammar() :
		vector_property_grammar::base_type(start, "list property")
	{
		using namespace qi::labels;
		start %= qi::int_[_a = _1] > qi::repeat(_a)[qi::int_];
	}

	qi::rule<Iterator, std::vector<int>(), qi::locals<std::size_t>, Skipper> start;
};

template<typename Iterator, typename Skipper>
struct array_property_grammar: qi::grammar<Iterator, boost::array<int, 3>(), Skipper>
{
	array_property_grammar() :
		array_property_grammar::base_type(start, "list property")
	{
		using namespace qi::labels;
		start %= qi::int_(3) > qi::repeat(3)[qi::int_];
	}

	qi::rule<Iterator, boost::array<int, 3>(), Skipper> start;
};

template<typename Iterator, typename Skipper>
struct list_property_grammar: qi::grammar<Iterator, std::vector<int>(), //
		qi::locals<std::size_t>, Skipper>
{
	list_property_grammar() :
		list_property_grammar::base_type(start, "list property")
	{
		using namespace qi::labels;
		start %= qi::int_[_a = _1] > qi::repeat(_a)[qi::int_];
	}

	qi::rule<Iterator, Array(), qi::locals<std::size_t>, Skipper> start;
};

/*
 * create a rule based on:
 * format
 * property
 * Element
 */
template<typename Iterator, typename Skipper, typename Element>
qi::rule<Iterator, Skipper> ascii_rule_factory(Element& element, ply::list const& list)
{
	BOOST_STATIC_CONSTANT(int, size = boost::mpl::size<Element>::value);


}


/*
 * create a rule based on:
 *
 * format
 * property
 * Element
 *
 *
 */




void rule(ply::format format, ply::scalar scalar)
{
	switch (format)
	{
	case ply::ascii:
	{
		switch (scalar)
		{
		case ply::uint8:
			return qi::uint_parser<unsigned char>();
		case ply::uint16:
			return qi::ushort_;
		case ply::uint32:
			return qi::uint_;
		case ply::uint64:
			return qi::ulong_long;
		case ply::int8:
			return qi::int_parser<char>();
		case ply::int16:
			return qi::short_;
		case ply::int32:
			return qi::int_;
		case ply::int64:
			return qi::long_long;
		case ply::float32:
			return qi::float_;
		case ply::float64:
			return qi::double_;
		}
	}
	case ply::binary_little_endian:
	{
	}
	case ply::binary_big_endian:
	{
	}
	}
}

#endif /* PLY_SEMANTIC_ACTION_HPP */
