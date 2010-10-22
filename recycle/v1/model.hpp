/*
 * model.hpp
 *
 *  Created on: 02.08.2010
 *      Author: daniel
 */

#ifndef PLY_V1_MODEL_HPP
#define PLY_V1_MODEL_HPP

#include <ply/element.hpp>

namespace ply
{

template<typename Vertex, typename Face>
class model
{
public:
	model(char const* filename)
	{
	}

private:
	element<Vertex> vertex;
	element<Face> face;
};

} // namespace ply

#endif /* PLY_V1_MODEL_HPP */
