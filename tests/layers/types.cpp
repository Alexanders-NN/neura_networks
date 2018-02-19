#include <cmath>
#include <functional>
#include <iostream>
#include <memory>

#include "../../src/tensor.hpp"
#include "../../src/layers.hpp"

#include "../main_test.hpp"


TEST_CASE( "Testing layer_info" )
{
	SECTION( "Stupid Test 1" )
	{
        using namespace layers;
    	auto info = layer_info( types::convolution );

		REQUIRE( info.who_am_i() == types::convolution );
        REQUIRE( info.type() == types::convolution );
	}

    SECTION( "Stupid Test 2" )
	{
        using namespace layers;
    	auto info = layer_info( types::linear );

		REQUIRE( info.who_am_i() == types::linear );
        REQUIRE( info.type() == types::linear );
	}
}

TEST_CASE( "Testing union_parameter" )
{
    using namespace layers;
	using union_t = union_parameter<float>;

	SECTION( "Testing function_layer_parameter : 1 steps" )
	{
        using namespace layers;
        auto ReLU = []( auto x ){ return x > 0 ? x : 0; };

		auto parameter =
			union_t( types::function, function_layer_parameter<float>(ReLU) );

		REQUIRE( parameter.who_am_i() == types::function );
        REQUIRE( parameter.type() == types::function );

        auto func = get<function_layer_parameter<float>>( parameter );

		auto REQUIRE_RELU = []( auto func ){
	        REQUIRE( func( 0.f ) == 0 );
	        REQUIRE( func( -142.07 ) == 0 );
	        REQUIRE( func( 11 ) == 11 );
	        REQUIRE( func( -4.5 ) == 0 );
	        REQUIRE( func( 3 ) == 3 );
	        REQUIRE( func( 2 ) == 2 );
	    };

        REQUIRE_RELU( ReLU );
        REQUIRE_RELU( func );
	}

	SECTION( "Testing function_layer_parameter : 2 steps" )
	{
        using namespace layers;
		auto sigmoid = []( auto x ){ return 1/( 1 + std::exp(-x) ); };

		auto sigmoid_wrapper = function_layer_parameter<float>(sigmoid);
    	auto parameter = union_t( types::function, sigmoid_wrapper );

		REQUIRE( parameter.who_am_i() == types::function );
        REQUIRE( parameter.type() == types::function );

        auto func = get<function_layer_parameter<float>>( parameter );

		auto REQUIRE_SIGMOID = []( auto func ){
			static const auto e = 1e-7;
			static auto eq = []( auto lhs, auto rhs )
					  { return std::abs(rhs - lhs) < e; };

			REQUIRE(eq( func( -3 ), 0.0474258731776 ));
			REQUIRE(eq( func( 0 ), 0.5 ));
			REQUIRE(eq( func( 11 ), 0.999983298578 ));
			REQUIRE(eq( func( -5 ), 0.00669285092428 ));
			REQUIRE(eq( func( -1.05 ), 0.259225101 ));
			REQUIRE(eq( func( 3 ), 0.952574126822 ));
			REQUIRE(eq( func( 2 ), 0.880797077978 ));
	    };

        REQUIRE_SIGMOID( sigmoid );
        REQUIRE_SIGMOID( func );
	}
}
