#pragma once

#include <iostream>
#include <vector>
#include <exception>



namespace types {

	template<class T>
	class matrix
	{

	public:
		using value_type = T;
		using size_type = std::size_t;
		using matrix_type = std::vector<value_type>;

	public:


		matrix( size_type height = 0, size_type width = 0,
			value_type default_value = value_type(0))
			: _width( width )
			, _height( height )
			, _matrix_data( width * height, default_value )
		{}


		matrix( const matrix& obj )
            : _width( obj._width )
            , _height( obj._height )
            , _matrix_data( obj._matrix_data )
        {}

		matrix( matrix&& obj )
		{
			std::swap( _height, obj._height);
			std::swap( _width, obj._width);
			std::swap( _matrix_data, obj._matrix_data);
		}

		matrix& operator=( const matrix& obj ) 
		{
            if ( this != &obj )
            {
                _height = obj._height;
                _width = obj._width;
                _matrix_data = obj._matrix_data;
            }
            return  *this;
		}

		matrix& operator=( matrix&& obj )
		{
            if ( this != &obj )
            {
                std::swap( _height, obj._height);
				std::swap( _width, obj._width);
				std::swap( _matrix_data, obj._matrix_data);
            }
            return  *this;
		}

		matrix( const std::initializer_list<std::initializer_list<value_type>>& rows )
		{
            _height = rows.size();

            if( _height ) {

	          	_width  = rows.begin()->size();

	            for ( auto& row : rows )
	            {
	                if ( row.size() != _width )
					{
						_height = 0;
						_width = 0;
						_matrix_data.clear();

						throw std::logic_error( "Error! Incorrect initialization matrix" );
					}
	                _matrix_data.insert( _matrix_data.end(), std::begin(row), std::end(row) );
	            }
	       	}
	       	else {
	       		_width = 0;
	       	}
		}


		template<class It>
		matrix( size_type height, size_type width, It begin, It end )
			: _width( width )
			, _height( height )
			, _matrix_data( begin, end )
		{
			if( _matrix_data.size() != _width * _height ) {
				_width = 0;
				_height = 0;
				_matrix_data.clear();
                
                throw std::logic_error( "Error! Incorrect initialization matrix" );
			}
		}

        matrix& operator+=( const matrix& rhs )
        {
            for( size_t i = 0; i < this->_matrix_data.size(); ++i )
            {
                this->_matrix_data[i] += rhs._matrix_data[i];
            }
            return *this;
        }

		const value_type& operator()( size_type row, size_type col ) const
		{
			return _matrix_data[ _width * row + col ];
		}

		value_type& operator()( size_type row, size_type col )
		{
			return const_cast<value_type&>( const_cast<const matrix&>(*this)( row, col ) );
		}

		size_type width() const
		{
			return _width;
		}

		size_type height() const
		{
			return _height;
		}

		const matrix_type& data() const
		{
			return _matrix_data;
		}

	protected:
		size_type   _width;
		size_type   _height;
		matrix_type _matrix_data;
	};

	template< class T >
    matrix<T> operator+( const matrix<T>& lhs, const matrix<T>& rhs )
    {
        auto tmp = lhs;
        tmp += rhs;
        return tmp;
    }
}
