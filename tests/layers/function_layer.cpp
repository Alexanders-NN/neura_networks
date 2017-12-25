#include <cmath>
#include <functional>
#include <iostream>
#include <memory>

#include "../../src/tensor.hpp"
#include "../../src/layers.hpp"

#include "../main_test.hpp"


TEST_CASE( "Testing function_layer" )
{
	using matrix_t = math::matrix<float>;

	auto tensor = math::tensor<float> {
		matrix_t {
			{ 0,   1,  -1,  2 },
			{ 1,  -2,   3,  5 },
		},
		matrix_t {
			{ 1,  -2,  -3,  -5 },
			{ 2,  -4,   7,  12 },
		},
		matrix_t {
			{ 2,  0,  -5,  8 },
			{ 3,  6,  11, 19 },
		},
	};

	SECTION( "Testing ReLU" )
	{
		SECTION( "Checking init tensor" )
		{
			REQUIRE( tensor( 0, 2, 1 ) == -3 );
			REQUIRE( tensor( 0, 0, 0 ) == 0 );
			REQUIRE( tensor( 1, 2, 2 ) == 11 );
			REQUIRE( tensor( 0, 3, 1 ) == -5 );
			REQUIRE( tensor( 1, 2, 0 ) == 3 );
			REQUIRE( tensor( 1, 0, 1 ) == 2 );
		}

		auto ReLU = []( auto x ){ return x > 0 ? x : 0;	};

		auto layer = layers::make_function_layer<float>( ReLU );

		REQUIRE( layer->type() == layers::types::function );

		auto result = (*layer)( tensor );

		SECTION( "Checking result tensor" )
        {
    		REQUIRE( result( 0, 2, 1 ) == 0 );
    		REQUIRE( result( 0, 0, 0 ) == 0 );
    		REQUIRE( result( 1, 2, 2 ) == 11 );
    		REQUIRE( result( 0, 3, 1 ) == 0 );
    		REQUIRE( result( 1, 2, 0 ) == 3 );
    		REQUIRE( result( 1, 0, 1 ) == 2 );
        }
	}

	SECTION( "Testing sigmoid" )
	{
		static const auto e = 1e-7;

		SECTION( "Checking init tensor" )
		{
			REQUIRE( tensor( 0, 2, 1 ) == -3 );
			REQUIRE( tensor( 0, 0, 0 ) == 0 );
			REQUIRE( tensor( 1, 2, 2 ) == 11 );
			REQUIRE( tensor( 0, 3, 1 ) == -5 );
			REQUIRE( tensor( 1, 2, 0 ) == 3 );
			REQUIRE( tensor( 1, 0, 1 ) == 2 );
		}

		auto sigmoid = []( auto x ){ return 1 / ( 1 + std::exp(-x) ); };

		auto eq = []( auto lhs, auto rhs ){ return std::abs(rhs - lhs) < e; };

		auto layer = layers::function_layer<float>( sigmoid );

		REQUIRE( layer.type() == layers::types::function );

		SECTION( "Testing result tensor" )
		{
			auto result = layer(tensor);

			REQUIRE(eq( result( 0, 2, 1 ), 0.0474258731776 ));
			REQUIRE(eq( result( 0, 0, 0 ), 0.5 ));
			REQUIRE(eq( result( 1, 2, 2 ), 0.999983298578 ));
			REQUIRE(eq( result( 0, 3, 1 ), 0.00669285092428 ));
			REQUIRE(eq( result( 1, 2, 0 ), 0.952574126822 ));
			REQUIRE(eq( result( 1, 0, 1 ), 0.880797077978 ));
		}
	}
}
