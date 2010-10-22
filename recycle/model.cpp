/*
 * model.cpp
 *
 *  Created on: Aug 26, 2010
 *      Author: danielp
 */

#include <vector>
#include <ply/adapted.hpp>
#include <ply/model.hpp>
#include <boost/array.hpp>
#include <boost/test/unit_test.hpp>

struct vertex
{
	float x;
	float y;
	float z;
	float confidence;
	float intensity;
};

typedef std::vector<int> face_indices;
//typedef boost::array<int, 3> face_indices;

struct face
{
	face_indices vertex_indices;
};

PLY_ADAPT(vertex,
		(float, x)
		(float, y)
		(float, z)
		(float, confidence)
		(float, intensity)
)

PLY_ADAPT(face,
		(face_indices, vertex_indices)
)

BOOST_AUTO_TEST_CASE(model)
{
	ply::model<vertex, face> model("bunny.ply");
}
