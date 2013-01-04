#include "generator.hpp"
#include <boost/python.hpp>

BOOST_PYTHON_MODULE ( pygenerator )
{
	using namespace boost::python;
	class_<Generator,boost::noncopyable> ( "Generator" )
		.def ( "__call__", &Generator::operator() );
}