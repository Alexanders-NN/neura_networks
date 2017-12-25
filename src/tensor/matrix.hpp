#pragma once

#include <exception>
#include <functional>
#include <iostream>
#include <iomanip>
#include <vector>



namespace math {

	template<class T>
	class matrix
	{

	public:
		using value_type = T;
		using size_type = std::size_t;
		using matrix_type = std::vector<value_type>;
		using init_func_type = std::function<value_type( size_type, size_type )>;

	public:
		matrix( size_type rows_count = 0, size_type cols_count = 0,
				value_type default_value = value_type(0))
			: _rows_count( rows_count )
			, _cols_count( cols_count )
			, _matrix_data( rows_count * cols_count, default_value )
		{}

		matrix( size_type rows_count, size_type cols_count, init_func_type function )
			: _rows_count( rows_count )
			, _cols_count( cols_count )
			, _matrix_data( rows_count * cols_count )
		{
			for( size_type row = 0; row < _rows_count; ++row )
				for( size_type col = 0; col < _cols_count; ++col )
					(*this)( row, col ) = function( row, col );
		}


		matrix( const matrix& obj )
            : _rows_count( obj._rows_count )
			, _cols_count( obj._cols_count )
            , _matrix_data( obj._matrix_data )
        {}

		matrix( matrix&& obj )
            : _rows_count( 0 )
			, _cols_count( 0 )
            , _matrix_data()
		{
			std::swap( _rows_count, obj._rows_count );
			std::swap( _cols_count, obj._cols_count );
			std::swap( _matrix_data, obj._matrix_data );
		}

		matrix& operator=( const matrix& obj )
		{
            if ( this != &obj )
            {
                _rows_count = obj._rows_count;
                _cols_count = obj._cols_count;
                _matrix_data = obj._matrix_data;
            }
            return *this;
		}

		matrix& operator=( matrix&& obj )
		{
            if ( this != &obj )
            {
                std::swap( _rows_count, obj._rows_count);
				std::swap( _cols_count, obj._cols_count);
				std::swap( _matrix_data, obj._matrix_data);
            }
            return *this;
		}

		matrix( const std::initializer_list<std::initializer_list<value_type>>& rows )
		{
            _rows_count = rows.size();

            if( _rows_count ) {

	          	_cols_count  = rows.begin()->size();

	            for ( auto& row : rows )
	            {
	                if ( row.size() != _cols_count )
					{
						_rows_count = 0;
						_cols_count = 0;
						_matrix_data.clear();

						throw std::logic_error( "Error! Incorrect initialization matrix" );
					}
	                _matrix_data.insert( _matrix_data.end(), std::begin(row), std::end(row) );
	            }
	       	}
	       	else {
	       		_cols_count = 0;
	       	}
		}


		template<class It>
		matrix( size_type rows_count, size_type cols_count, It begin, It end )
			: _rows_count( rows_count )
			, _cols_count( cols_count )
			, _matrix_data( begin, end )
		{
			if( _matrix_data.size() != _cols_count * _rows_count ) {
				_cols_count = 0;
				_rows_count = 0;
				_matrix_data.clear();

                throw std::logic_error( "Error! Incorrect initialization matrix" );
			}
		}

		const value_type& operator()( size_type row, size_type col ) const
		{
			return _matrix_data[ _cols_count * row + col ];
		}

		value_type& operator()( size_type row, size_type col )
		{
			return const_cast<value_type&>( const_cast<const matrix&>(*this)( row, col ) );
		}

		size_type cols_count() const
		{
			return _cols_count;
		}

		size_type rows_count() const
		{
			return _rows_count;
		}

		const matrix_type& data() const
		{
			return _matrix_data;
		}

		matrix& operator+=( const matrix& rhs )
        {
        	_check_size_with_exception( *this, rhs );

            for( size_t i = 0; i < this->_matrix_data.size(); ++i ) {
                this->_matrix_data[i] += rhs._matrix_data[i];
            }
            return *this;
        }

		matrix& operator-=( const matrix& rhs )
        {
        	_check_size_with_exception( *this, rhs );

            for( size_t i = 0; i < this->_matrix_data.size(); ++i ) {
                this->_matrix_data[i] -= rhs._matrix_data[i];
            }
            return *this;
        }




        friend bool operator==( const matrix& lhs, const matrix& rhs )
        {
        	_check_size_with_exception( lhs, rhs );

        	for( size_t i = 0; i < lhs._matrix_data.size(); ++i )
        		if( lhs._matrix_data[i] != rhs._matrix_data[i] )
        			return false;

        	return true;
        }

        friend bool operator!=( const matrix& lhs, const matrix& rhs )
        {
        	_check_size_with_exception( lhs, rhs );

        	for( size_t i = 0; i < lhs._matrix_data.size(); ++i )
        		if( lhs._matrix_data[i] != rhs._matrix_data[i] )
        			return true;

        	return false;
        }

	    friend matrix operator+( const matrix& lhs, const matrix& rhs )
	    {
	        auto tmp = lhs;
	        tmp += rhs;
	        return tmp;
	    }
		friend matrix operator-( const matrix& lhs, const matrix& rhs )
	    {
	        auto tmp = lhs;
	        tmp -= rhs;
	        return tmp;
	    }

	    friend matrix operator*( const matrix& lhs, const matrix& rhs )
	    {
	    	if( lhs.cols_count() != rhs.rows_count() )
				throw std::invalid_argument( "Matrix sizes mismatch" );

			size_type magic_number = lhs.cols_count();

	        return matrix( lhs.rows_count(), rhs.cols_count(),
	        				[magic_number, &lhs, &rhs]( auto r, auto c )
	        				{
	        					value_type val( 0 );
	        					for( size_type i = 0; i < magic_number; ++i )
	        						val += lhs( r, i ) * rhs( i, c );

	        					return val;
	        				}
	        	   );
	    }

		friend std::ostream& operator <<( std::ostream& ostr, const matrix& m )
		{
			for( size_type row = 0; row < m._rows_count; ++row ) {
				for( size_type col = 0; col < m._cols_count; ++col )
					std::cout << std::setw(3) << m( row, col ) << " ";

				std::cout << std::endl;
			}
			return ostr;
		}


	protected:
		size_type   _rows_count;
		size_type   _cols_count;
		matrix_type _matrix_data;

		static void _check_size_with_exception( const matrix& lhs, const matrix& rhs )
		{
			if( lhs._rows_count != rhs._rows_count
					|| lhs._cols_count != rhs._cols_count ) {
				throw std::invalid_argument( "Matrix sizes mismatch" );
			}
		}
	};
}
