#include <cmath>
#include <sstream>
#include <functional>
#include <iostream>
#include <memory>

#include "../../src/tensor.hpp"
#include "../../src/layers.hpp"

#include "../main_test.hpp"



TEST_CASE( "Testing linear_layer" )
{
	using matrix_t = math::matrix<float>;
	using tensor_t = math::tensor<float>;

	const auto e = 1e-7;
	auto eq = [ e ]( auto lhs, auto rhs ){
		REQUIRE( std::abs(rhs - lhs) < e );
		return std::abs(rhs - lhs) < e;
	};


	SECTION( "Testing linear 1" )
	{
		auto weights = matrix_t {
			{ -0.01,  0.04,  0.51,  0.33 },
			{ 0.017, -0.23, -0.11,  0.89 },
			{  0.15, -0.74, 0.225, 0.001 }
		};
		auto bias = matrix_t {
			{ 0.4 },
			{ 0.002 },
			{ -0.009 }
		};
		auto tensor_x = tensor_t {
			matrix_t {
				{ 0.03  },
				{ 0.997 },
				{ 0.123 },
				{ 0.42  }
			},
		};
		auto tensor_y = tensor_t {
			matrix_t {
				{ 0.64091 },
				{ 0.13347 },
				{ -0.714185 },
			},
		};

		auto layer = layers::make_linear_layer<float>(
			 weights,
			 std::move(bias)
		 );

        REQUIRE( layer->type() == layers::types::linear );

		auto result = (*layer)( tensor_x );

		REQUIRE( is_equal(result, tensor_y, eq) );



	}
}
