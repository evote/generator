#include "generator.hpp"

Generator::Generator ( ) :
	on (
	{
		{"generate_votes", std::bind ( &Generator::on_generate_votes, std::ref ( *this ), std::placeholders::_1, std::placeholders::_2 ) },
		{"count_votes", std::bind ( &Generator::on_count_votes, std::ref ( *this ), std::placeholders::_1, std::placeholders::_2 ) },
	} )
{
}

Generator::~Generator()
{

}

const std::string Generator::operator() ( const std::string & message )
{
	YAML::Node msg = YAML::Load ( message );
	YAML::Node ret;
	ret["error"] = "OK";
	try
	{
		on.at ( msg["type"].as<std::string>() ) ( msg, ret );
	}
	catch ( ... )
	{
		ret["error"] = "unknown";
	}
	return YAML::Dump ( ret );
}

YAML::Node& Generator::on_generate_votes ( const YAML::Node & msg, YAML::Node & ret )
{
	ret["type"] = "votes_generated";
	uint V = msg["data"][0].as<uint>();
	uint O = msg["data"][1].as<uint>();
	Integer p = msg["data"][2].as<Integer>();
	Integer g = msg["data"][3].as<Integer>();
	Integer k = Integer::Random ( p / 2, p );
	ret["data"][0][0] = k;
	std::set<Integer> T;
	while ( T.size() < V )
	{
		T.insert ( Integer::Random ( p / 2, p ) );
	}
	for ( Integer t: T )
	{
		YAML::Node card;
		Integer y;
		do
		{
			y = Integer::Random ( p / 2, p - Integer ( 1 ) );
		}
		while ( Integer::Call ( mpz_gcd, y, p - Integer ( 1 ) ) != 1 ) ;
		Integer gt = Integer::Call ( mpz_powm, g, t, p );
		Integer gy = Integer::Call ( mpz_powm, g, y, p );
		Integer P ( 1 );
		for ( uint i = 0; i < O; ++i )
		{
			YAML::Node option;
			P = Integer::NextPrime ( P );
			Integer o = ( P * Integer::Call ( mpz_powm, g, k * t, p ) ) % p;
			Integer s = ( ( o - t * gy ) * Integer::Call ( mpz_powm, y, Integer ( -1 ), p - Integer ( 1 ) ) ) % ( p - Integer ( 1 ) );
			option[0] = gt;
			option[1] = o;
			option[2] = gy;
			option[3] = s;
			card.push_back ( option );
		}
		ret["data"][0][1].push_back ( gt );
		ret["data"][1].push_back ( card );
	}
	return ret;
}

YAML::Node& Generator::on_count_votes ( const YAML::Node& msg, YAML::Node& ret )
{
	ret["type"] = "votes_counted";
	uint O = msg["data"][1].as<uint>();
	Integer p = msg["data"][1].as<Integer>();
	Integer k = msg["data"][2].as<Integer>();
	Integer G = msg["data"][3].as<Integer>();
	Integer P = msg["data"][4].as<Integer>();
	Integer v = ( Integer::Call ( mpz_powm, G, -k, p ) * P ) % p;
	Integer o = 1;
	while ( v != Integer ( 1 ) )
	{
		uint c = 0;
		o = o.NextPrime ( o );
		while ( ( v % o ) == Integer() and v != Integer ( 1 ) )
		{
			++c;
			v /= o;
		}
		ret["data"].push_back ( c );
	}
	for ( uint i = ret["data"].size(); i < O; ++i )
	{
		ret["data"].push_back ( 0 );
	}
	return ret;
}

