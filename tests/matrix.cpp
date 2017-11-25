#include <string>

#include "../src/tensor/Matrix.hpp"

#include "main_test.hpp"



TEST_CASE( "Testing constructors ( and operator = )" )
{
	SECTION( "Null constructor" )
	{
		auto empty_matrix = types::matrix<float>();

		INFO( "Constructor requires row counts, column counts and default value." );
		INFO( "Default is ( 0, 0, value_type(0) ) ." );

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
}


TEST_CASE( "Testing operator + " )
{
	SECTION( "type = <int>" )
	{
		types::matrix<int> squares( 3, 8 );
		types::matrix<int> numbers = squares;
		types::matrix<int> units( squares.height(), numbers.width(), 1 );

		auto f = []( auto x, auto y ){ return 3*x + y; };

		for( size_t i = 0; i < 3; ++i )
			for( size_t j = 0; j < 8; ++j ) {
				numbers( i, j ) = f( i, j );
				squares( i, j ) = f( i, j ) * numbers( i, j );
			}

		auto result = squares;

		result += numbers + numbers + units;

		for( size_t i = 0; i < 3; ++i )
			for( size_t j = 0; j < 8; ++j ) 
				REQUIRE( result( i, j ) ==  ((f( i, j ) + 1) * (f( i, j ) + 1)) );
	}

	SECTION( "type = <std::string>" )
	{
		types::matrix<std::string> words1 = {
			{ std::string( "Neural" ), std::string( "are" ) },
			{ std::string( "q1" ), std::string( "q3" ) },
		};

		types::matrix<std::string> spaces( 2, 2, std::string(" ") );

		types::matrix<std::string> words2 = {
			{ std::string( "networks" ), std::string( "cool" ) },
			{ std::string( "q2" ), std::string( "q4" ) },
		};

		auto result = words1 + spaces;
		result += words2;

		REQUIRE( result( 0, 0 ) + " " + result( 0, 1 ) == "Neural networks are cool" );
		REQUIRE( result( 1, 0 ) == "q1 q2" );
	}
}



