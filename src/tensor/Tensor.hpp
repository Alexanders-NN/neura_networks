#pragma once

#include <iostream>
#include <vector>
#include <exception>

#include "Matrix.hpp"


namespace types {

    template<class T>
    class tensor
    {
        using value_type = T;
        using size_type = size_t;
        using matrix_type = matrix<value_type>;
        using tensor_type = std::vector<matrix_type>;

    public:
        tensor()
	        : _width( 0 )
	        , _height( 0 )
	        , _depth( 0 )
	        , _tensor_data()
        {}

        /*
        tensor( const std::vector<T>& pixels, size_type depth, size_type width, size_type heigth)
                : _width( width )
                , _heigth( heigth )
                , _depth( depth )
        {
            for( size_type i = 0; i < _depth; ++i )
            {
                matrix_type new_matrix(width, heigth, pixels.begin() + i * width * heigth,
                                       pixels.begin() + (i + 1) * width * heigth);

                _tensor_data.push_back(new_matrix);
            }
        }
        */

        template<class It>
        tensor( It begin, It end, size_type depth, size_type height, size_type width )
                : _width( width )
                , _height( height )
                , _depth( depth )
        {
            if( _depth * _width * _height != end - begin )
            {
                _depth = 0;
                _width = 0;
                _height = 0;

                throw std::logic_error( "Error! Incorrect initialization tensor" );
            }
            for( size_type i = 0; i < _depth; ++i )
            {
                matrix_type new_matrix( _height, _width, 
	                	begin + i * width * height,
	                    begin + (i + 1) * width * height
                    );

                _tensor_data.push_back( std::move( new_matrix ) );
            }
        }

        tensor(std::initializer_list<matrix_type>& matrixes)
        {
            _depth = matrixes.size();

            if( ! _depth ) {
            	_width = matrixes.begin()->width();
	            _height = matrixes.begin()->height();

	            for( auto& matrix : matrixes )
	            {
	                if( ( matrix.height() != _height ) || ( matrix.width() != _width ) )
	                {
	                    _depth = 0;
	                    _width = 0;
	                    _height = 0;
	                    _tensor_data.clear();

	                    throw std::logic_error( "Error! Incorrect initialization tensor" );
	                }
	                _tensor_data.push_back( std::move( matrix ) );
	            }
            }
            else {
            	_depth = 0;
                _width = 0;
                _height = 0;
	        }
        }

        tensor( const tensor& obj )
                : _depth (obj._depth)
                , _width (obj._width)
                , _height( obj._height )
                , _tensor_data( obj._tensor_data )
        {}

        tensor( tensor&& obj )
        {
            std::swap( _depth, obj._depth );
            std::swap( _height, obj._height );
            std::swap( _width, obj._width );
            std::swap( _tensor_data, obj._tensor_data );
        }

        tensor& operator=( const tensor& obj )
        {
            if( this != &obj )
            {
                _depth = obj._depth;
                _width = obj._width;
                _height = obj._height;

                _tensor_data = obj._tensor_data;
            }
            return *this;
        }

        tensor& operator=( tensor&& obj )
        {
            if( this != &obj )
            {
	            std::swap( _depth, obj._depth );
	            std::swap( _height, obj._height );
	            std::swap( _width, obj._width );
	            std::swap( _tensor_data, obj._tensor_data );
            }
            return *this;
        }


        const value_type& operator()( size_type depth, size_type row, size_type col ) const
        {
            return _tensor_data[ depth ]( row, col );
        }

        value_type& operator()( size_type depth, size_type row, size_type col )
        {
            return static_cast<value_type&>( 
            		const_cast<const tensor&>(*this)( depth, row, col ) 
            	);
        }

        size_type width() const
        {
            return _width;
        }

        size_type height() const
        {
            return _height;
        }

        size_type depth() const
        {
            return _depth;
        }

        const tensor_type& data() const
        {
            return _tensor_data;
        }

    protected:
        size_type _width;
        size_type _height;
        size_type _depth;

        tensor_type _tensor_data;

    };
}