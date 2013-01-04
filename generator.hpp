#pragma once

#include <string>
#include <map>
#include <set>
#include <utility>
#include <functional>
#include <yaml-cpp/yaml.h>
#include <integer.hpp>
#include <integer.yaml.hpp>

class Generator
{
	public:
		Generator ( const Generator & ) = delete;
		Generator ( Generator && ) = delete;
		Generator & operator= ( const Generator & ) = delete;
		Generator & operator= ( Generator && ) = delete;
	public:
		Generator ( );
		const std::string operator() ( const std::string & );
		~Generator();
	private:
		const std::map<std::string, std::function<YAML::Node & ( const YAML::Node &, YAML::Node& ) >> on;
		YAML::Node& on_generate_votes ( const YAML::Node &, YAML::Node& );
};
