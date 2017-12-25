#include <cmath>
#include <functional>
#include <iostream>
#include <memory>

#include "../../src/tensor.hpp"
#include "../../src/layers.hpp"
#include "../../src/models.hpp"

#include "../main_test.hpp"


TEST_CASE( "Testing linear_layer" )
{
	using matrix_t = math::matrix<float>;
	using tensor_t = math::tensor<float>;
    using sequence_t = models::sequence<float>;


	const auto e = 1e-7;
	auto eq = [ e ]( auto lhs, auto rhs ){
        CAPTURE( rhs - lhs );
		REQUIRE( std::abs(rhs - lhs) < e );
		return std::abs(rhs - lhs) < e;
	};


	SECTION( "Testing model : Frank Rosenblatt" )
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
        auto sigmoid = []( auto x )
            {
                return 1 / ( 1 + std::exp(-x) );
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
				{ 0.65495913 },
				{ 0.53331805 },
				{ 0.32867476 },
			},
		};


        auto linear_layer = layers::make_linear_layer<float>(
         std::move(weights), bias
        );
        auto sigmoid_layer = layers::make_function_layer<float>( sigmoid );

        auto model = sequence_t();

        model.add_layer( linear_layer );
        model.add_layer( sigmoid_layer );


        REQUIRE( model.length() == 2 );

		auto result = model( tensor_x );

		REQUIRE( is_equal(result, tensor_y, eq) );

	}
}
