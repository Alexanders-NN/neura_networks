#include <string>

#include "../../src/tensor.hpp"

#include "../main_test.hpp"


TEST_CASE( "Testing constructors ( and operator = )" )
{
	SECTION( "Null constructor" )
	{
		auto empty_tensor = math::tensor<float>();

		INFO( "Constructor requires layer count, row counts, column counts and default value." );
		INFO( "Default is ( 0, 0, 0, value_type(0) ) ." );

		REQUIRE( empty_tensor.rows_count() == 0 );
		REQUIRE( empty_tensor.cols_count() == 0 );
		REQUIRE( empty_tensor.depth() == 0 );
	}

	SECTION( "Constructor with default value" )
	{

		INFO( "Constructing matrix 3x15" );
		auto tensor = math::tensor<float>( 3, 15, 19, 42. );


		SECTION( "Checking size" )
		{
			REQUIRE( tensor.rows_count() == 3 );
			REQUIRE( tensor.cols_count() == 15 );
			REQUIRE( tensor.depth() == 19 );
		}

		SECTION( "Chcecking cells, default value is, of course, 42.0 ." )
		{
			REQUIRE( tensor[18]( 2, 14 ) == 42 );

			REQUIRE( tensor( 2, 14, 17 ) == 42 );
			REQUIRE( tensor( 1, 1, 1 ) == 42 );
		}
	}

	SECTION( "Constructor from init_lists" )
	{
		INFO( "Constructing tensor 2x4x3" );

		using matrix_t = math::matrix<float>;

		auto matrix0 = matrix_t {
			{ 0,  1,  1,  2 },
			{ 1,  2,  3,  5 },
		};
		auto matrix1 = matrix_t {
			{ 1,  2,  3,  5  },
			{ 2,  4,  7,  12 },
		};
		auto matrix2 = matrix_t {
			{ 2,  3,  5,  8  },
			{ 3,  6,  11, 19 },
		};

		auto tensor = math::tensor<float> {
			matrix0,
			matrix1,
			matrix2,
		};

		SECTION( "Checking size" )
		{
			REQUIRE( tensor.rows_count() == 2 );
			REQUIRE( tensor.cols_count() == 4 );
			REQUIRE( tensor.depth() == 3 );
		}

		SECTION( "Checking cells" )
		{
			REQUIRE( tensor( 0, 0, 0 ) == 0 );
			REQUIRE( tensor( 1, 2, 2 ) == 11 );
			REQUIRE( tensor( 0, 3, 1 ) == 5 );
			REQUIRE( tensor( 1, 2, 0 ) == 3 );
			REQUIRE( tensor( 1, 0, 1 ) == 2 );
		}
	}

	SECTION( "Constructor with init function" )
	{

		SECTION( " - lambda" )
		{
			static const int size_of_cube = 5;

			std::string __info__ = "Constructing tensor ";
			__info__ += std::to_string(size_of_cube) + "x";
			__info__ += std::to_string(size_of_cube) + "x";
			__info__ += std::to_string(size_of_cube);

			INFO( __info__ );

			int a = 42;
			auto tensor = math::tensor<int>(
							size_of_cube,
							size_of_cube,
							size_of_cube,
							[ &a ]( auto row, auto col, auto dep )
							{
								return a + row + col + dep;
							}
						 );


			SECTION( "Checking size" )
			{
				REQUIRE( tensor.cols_count() == size_of_cube );
				REQUIRE( tensor.rows_count() == size_of_cube );
				REQUIRE( tensor.depth() == size_of_cube );
			}

			SECTION( "Chcecking cells" )
			{
				for( size_t d = 0; d < tensor.depth(); ++d )
					for( size_t r = 0; r < tensor.rows_count(); ++r )
						for( size_t c = 0; c < tensor.cols_count(); ++c )
							REQUIRE( tensor[d]( r, c ) == 42 + r + c + d );
			}
		}
	}
	/*
	SECTION( "{ copy, move } x { constructor, operator= }" )
	{
		INFO( "Constructing matrix 6x4" );

		math::matrix<float> matrix = {
			{ 0,    2,  5 ,  0  },
			{ 1,    2,  3,   4  },
			{ -.07, 4,  3,   15 },
			{ -31,  8,  0,   1  },
			{ 1,    6,  -2,  28 },
			{ 31,   5,  0.5, 1  }
		};

		SECTION( "Testing copy constuctor" )
		{
			auto matrix_copy = matrix;

			for( size_t row = 0; row < matrix.height(); ++row )
				for( size_t col = 0; col < matrix.width(); ++col )
					REQUIRE( matrix(row, col) == matrix_copy(row, col) );
		}

		SECTION( "Testing move constuctor" )
		{
			auto moved_matrix = std::move( matrix );

			REQUIRE( moved_matrix.width() == 4 );
			REQUIRE( moved_matrix.height() == 6 );

			REQUIRE( matrix.width() == 0 );
			REQUIRE( matrix.height() == 0 );

			REQUIRE( moved_matrix( 0, 0 ) == 0 );
			REQUIRE( moved_matrix( 1, 2 ) == 3 );
			REQUIRE( moved_matrix( 3, 1 ) == 8 );
			REQUIRE( moved_matrix( 5, 3 ) == 1 );
			REQUIRE( moved_matrix( 2, 3 ) == 15 );
		}

		SECTION( "Testing copy operator=" )
		{
			decltype( matrix ) new_matrix; // default - empty matrix;

			new_matrix = matrix;

			SECTION( "Checking size" )
			{
				REQUIRE( new_matrix.width() == 4 );
				REQUIRE( new_matrix.height() == 6 );
			}

			SECTION( "Checking cells" )
			{
				REQUIRE( new_matrix( 0, 0 ) == 0 );
				REQUIRE( new_matrix( 1, 2 ) == 3 );
				REQUIRE( new_matrix( 3, 1 ) == 8 );
				REQUIRE( new_matrix( 5, 3 ) == 1 );
				REQUIRE( new_matrix( 2, 3 ) == 15 );
			}
		}

		SECTION( "Testing move operator=" )
		{
			decltype( matrix ) new_matrix( 3, 2, 1 );

			new_matrix = std::move( matrix );

			SECTION( "Checking sizes" )
			{
				REQUIRE( matrix.width() == 2 );
				REQUIRE( matrix.height() == 3 );

				REQUIRE( new_matrix.width() == 4 );
				REQUIRE( new_matrix.height() == 6 );
			}

			SECTION( "Checking cells" )
			{

				REQUIRE( matrix( 0, 0 ) == 1 );
				REQUIRE( matrix( 1, 2 ) == 1 );

				REQUIRE( new_matrix( 0, 0 ) == 0 );
				REQUIRE( new_matrix( 1, 2 ) == 3 );
				REQUIRE( new_matrix( 3, 1 ) == 8 );
				REQUIRE( new_matrix( 5, 3 ) == 1 );
				REQUIRE( new_matrix( 2, 3 ) == 15 );
			}
		}
	}
	*/
}
