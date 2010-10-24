#include <ply/header_grammar.hpp>
#include <ply/element_grammar.hpp>

#include <fstream>
#include <sstream>
#include <boost/test/unit_test.hpp>

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/support_multi_pass.hpp>
#include <boost/spirit/include/classic_position_iterator.hpp>
#include <boost/fusion/adapted/struct/define_struct.hpp>

namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;
namespace classic = boost::spirit::classic;

BOOST_FUSION_DEFINE_STRUCT(, vertex_,
		(float, intensity)
		(float, confidence)
)

BOOST_AUTO_TEST_CASE(complete)
{
	std::ifstream file("bunny.ply");
	BOOST_REQUIRE(file);

	// iterate over stream input
	typedef std::istreambuf_iterator<char> base_iterator_type;
	base_iterator_type in_begin(file);

	// convert input iterator to forward iterator, usable by spirit parser
	typedef boost::spirit::multi_pass<base_iterator_type> forward_iterator_type;
	forward_iterator_type fwd_begin = boost::spirit::make_default_multi_pass(
			in_begin);
	forward_iterator_type fwd_end;

	// wrap forward iterator with position iterator, to record the position
	typedef classic::position_iterator2<forward_iterator_type> iterator;
	iterator position_begin(fwd_begin, fwd_end, "bunny.ply");
	iterator position_end;

	// prepare output
	ply::header header;
	BOOST_AUTO(comment, qi::lit("comment") >> *(ascii::char_ - qi::eol) >> qi::eol);
	BOOST_AUTO(skip, ascii::blank | comment);

	// parse
	try
	{
		ply::header_grammar<iterator, BOOST_TYPEOF(skip)> header_g;
		qi::phrase_parse(position_begin, position_end, header_g, skip, header);

		std::vector<vertex_> vertices;
		vertices.reserve(header.elements[0].count);

		typedef ply::element_grammar<iterator, BOOST_TYPEOF(skip), vertex_> element_g;
		element_g elem_g(header.elements[0]);

		vertex_ v;
		qi::phrase_parse(position_begin, position_end, elem_g, skip, v);

		BOOST_MESSAGE(v.intensity);
		BOOST_MESSAGE(v.confidence);
	}
	catch (const qi::expectation_failure<iterator>& e)
	{
		const classic::file_position_base<std::string>& pos =
				e.first.get_position();

		std::stringstream msg;
		msg << "parse error at file " << pos.file << " line " << pos.line
				<< " column " << pos.column << std::endl;
		msg << "'" << e.first.get_currentline() << "'" << std::endl;
		msg << std::setw(pos.column) << " " << "^- here";

		BOOST_FAIL(msg.str());
	}
}
