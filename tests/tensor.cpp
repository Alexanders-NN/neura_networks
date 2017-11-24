#include "../src/tensor/Matrix.hpp"
#include "../src/tensor/Tensor.hpp"

#include "main_test.hpp"


TEST_CASE( "Testing matrix's methods" )
{
	SECTION( "Testing constructors ( and operator = )" )
	{
		SECTION( "Null constructor" )
		{
			auto empty_matrix = types::matrix<float>();

			INFO( "Constructor requires row counts, column counts and default value." );
			INFO( "Default is ( 0, 0, vlaue_type(0) ) ." );

			REQUIRE( empty_matrix.width() == 0 );
			REQUIRE( empty_matrix.height() == 0 );
		}

		SECTION( "Constructor with default value" )
		{

			INFO( "Constructing matrix 3x15" );
			auto matrix = types::matrix<float>( 3, 15, 42. );


			SECTION( "Checking size" )
			{
				REQUIRE( matrix.width() == 15 );
				REQUIRE( matrix.height() == 3 );
			}

			SECTION( "Chcecking cells, default value is, of course, 42.0 ." )
			{
				REQUIRE( matrix( 2, 1 ) == 42 );
				REQUIRE( matrix( 1, 2 ) == 42 );
				REQUIRE( matrix( 2, 14 ) == 42 );
			}
		}

		SECTION( "Constructor from init_lists" )
		{
			INFO( "Constructing matrix 6x4" );

			types::matrix<float> matrix = {
				{ 0,    2,  5 ,  0  },
				{ 1,    2,  3,   4  },
				{ -.07, 4,  3,   15 },
				{ -31,  8,  0,   1  },
				{ 1,    6,  -2,  28 },
				{ 31,   5,  0.5, 1  }
			};

			SECTION( "Checking size" )
			{
				REQUIRE( matrix.width() == 4 );
				REQUIRE( matrix.height() == 6 );
			}

			SECTION( "Checking cells" )
			{
				REQUIRE( matrix( 0, 0 ) == 0 );
				REQUIRE( matrix( 1, 2 ) == 3 );
				REQUIRE( matrix( 3, 1 ) == 8 );
				REQUIRE( matrix( 5, 3 ) == 1 );
				REQUIRE( matrix( 2, 3 ) == 15 );
			}
		}

		SECTION( "{ copy, move } x { constructor, operator= }" )
		{
			INFO( "Constructing matrix 6x4" );

			types::matrix<float> matrix = {
				{ 0,    2,  5 ,  0  },
				{ 1,    2,  3,   4  },
				{ -.07, 4,  3,   15 },
				{ -31,  8,  0,   1  },
				{ 1,    6,  -2,  28 },
				{ 31,   5,  0.5, 1  }
			};

			SECTION( "Checking size" )
			{
				REQUIRE( matrix.width() == 4 );
				REQUIRE( matrix.height() == 6 );
			}

			SECTION( "Checking cells" )
			{
				REQUIRE( matrix( 0, 0 ) == 0 );
				REQUIRE( matrix( 1, 2 ) == 3 );
				REQUIRE( matrix( 3, 1 ) == 8 );
				REQUIRE( matrix( 5, 3 ) == 1 );
				REQUIRE( matrix( 2, 3 ) == 15 );
			}
		}	
	}
}
