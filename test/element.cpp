//

#include <boost/spirit/include/qi.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/fusion/adapted/struct/define_struct.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>

#include <boost/array.hpp>
#include <vector>

#include <ply/element_grammar.hpp>

BOOST_FUSION_DEFINE_STRUCT(, vertex,
		(float, x)
		(float, y)
		(float, z)
		(float, confidence)
		(float, intensity)
)

BOOST_FUSION_DEFINE_STRUCT(, face,
		(std::vector<int>, vertex_indices)
)

BOOST_AUTO_TEST_CASE(element)
{
	namespace qi = boost::spirit::qi;
	namespace ascii = boost::spirit::ascii;
	using namespace qi::labels;

	typedef std::string::iterator iterator;

	qi::rule<iterator, std::vector<float>(), qi::locals<std::size_t>, ascii::space_type> g;
	g %= qi::omit[qi::int_[_a = _1]] > qi::repeat(_a)[qi::float_];

	std::string intensity = "3 4.5 5.5 6.5 8.15";
	iterator start = intensity.begin();
	iterator end = intensity.end();

	//boost::array<float, 3> v;
	std::vector<float> v;

	boost::spirit::qi::phrase_parse(start, end, g, ascii::space, v);

	std::cout << "size: " << v.size() << std::endl;
	std::cout << v[0] << std::endl;
	std::cout << v[1] << std::endl;
	std::cout << v[2] << std::endl;
}
