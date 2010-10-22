#include <boost/test/unit_test.hpp>
#include <ply/property_grammar.hpp>
#include <boost/fusion/adapted/struct.hpp>
//#include <boost/fusion.hpp>
#include <boost/fusion/container/list/convert.hpp>

struct vertex
{
	float x;
	float y;
	float z;
	float confidence;
	float intensity;
};

BOOST_FUSION_ADAPT_STRUCT(vertex,
		(float, x)
		(float, y)
		(float, z)
		(float, confidence)
		(float, intensity)
)

BOOST_AUTO_TEST_CASE(property)
{
	namespace ascii = boost::spirit::ascii;
	typedef std::string::iterator iterator;
	typedef property_grammar<iterator, vertex, ascii::space_type> grammar;

	std::string intensity = "8.15";
	iterator start = intensity.begin();
	iterator end = intensity.end();

	vertex v;
	grammar g(v, ply::property(ply::float32, "intensity"));

	boost::spirit::qi::phrase_parse(start, end, g, ascii::space);

	std::cout << v.intensity << std::endl;

}
