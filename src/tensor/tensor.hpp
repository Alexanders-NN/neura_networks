#pragma once

#include <iostream>
#include <vector>
#include <exception>

#include "matrix.hpp"


namespace math {

    template<class T>
    class tensor
    {
        using value_type = T;
        using size_t = std::size_t;
        using matrix_type = matrix<value_type>;
        using tensor_type = std::vector<matrix_type>;
        using init_func_type = std::function<value_type( size_t, size_t, size_t )>;

    public:
        tensor( size_t row_count = 0, size_t col_count = 0, size_t depth = 0,
                    value_type default_value = value_type( 0 ) )
	        : _rows_count( row_count )
	        , _cols_count( col_count )
	        , _depth( depth )
	        , _tensor_data( depth, matrix_type(row_count, col_count, default_value) )
        {}

        tensor( size_t row_count, size_t col_count, size_t depth, init_func_type init_func )
	        : _rows_count( row_count )
	        , _cols_count( col_count )
	        , _depth( depth )
	        , _tensor_data( depth, matrix_type(row_count, col_count) )
        {
            for( size_t d = 0; d < _depth; ++d )
                for( size_t r = 0; r < _rows_count; ++r )
                    for( size_t c = 0; c < _cols_count; ++c ) {
                        (*this)[d](r, c) = init_func(r, c, d);
                    }

        }

        template<class It>
        tensor( It begin, It end, size_t depth, size_t row_count, size_t col_count )
            : _rows_count( row_count )
            , _cols_count( col_count )
            , _depth( depth )
        {
            if( _rows_count * _cols_count * _depth != end - begin )
            {
                _rows_count = 0;
                _cols_count = 0;
                _depth = 0;

                throw std::logic_error( "Error! Incorrect initialization tensor" );
            }
            for( size_t i = 0; i < _depth; ++i )
            {
                matrix_type new_matrix( _rows_count, _cols_count,
	                	begin + i * _cols_count * _rows_count,
	                    begin + (i + 1) * _cols_count * _rows_count
                    );

                _tensor_data.push_back( std::move( new_matrix ) );
            }
        }

        tensor(std::initializer_list<matrix_type> matrixes)
        {
            _depth = matrixes.size();

            if( _depth ) {
                _cols_count = matrixes.begin()->cols_count();
	            _rows_count = matrixes.begin()->rows_count();

	            for( auto& matrix : matrixes )
	            {
	                if( matrix.rows_count() != _rows_count
                            || matrix.cols_count() != _cols_count )
	                {
	                    _cols_count = 0;
	                    _rows_count = 0;
	                    _depth = 0;
	                    _tensor_data.clear();

	                    throw std::logic_error( "Error! Incorrect initialization tensor" );
	                }
	                _tensor_data.push_back( matrix );
	            }
            }
            else {
                _cols_count = 0;
                _rows_count = 0;
                _depth = 0;
	        }
        }

        tensor( const tensor& obj )
            : _rows_count( obj._rows_count )
            , _cols_count( obj._cols_count )
            , _depth( obj._depth )
            , _tensor_data( obj._tensor_data )
        {}

        tensor( tensor&& obj )
            : _rows_count( 0 )
            , _cols_count( 0 )
            , _depth( 0 )
            , _tensor_data()
        {
            std::swap( _rows_count, obj._rows_count );
            std::swap( _cols_count, obj._cols_count );
            std::swap( _depth, obj._depth );
            std::swap( _tensor_data, obj._tensor_data );
        }

        tensor& operator=( const tensor& obj )
        {
            if( this != &obj )
            {
                _rows_count = obj._rows_count;
                _cols_count = obj._cols_count;
                _depth = obj._depth;

                _tensor_data = obj._tensor_data;
            }
            return *this;
        }

        tensor& operator=( tensor&& obj )
        {
            if( this != &obj )
            {
	            std::swap( _rows_count, obj._rows_count );
	            std::swap( _cols_count, obj._cols_count );
	            std::swap( _depth, obj._depth );
	            std::swap( _tensor_data, obj._tensor_data );
            }
            return *this;
        }


        const matrix_type& operator[]( size_t depth ) const
        {
            return _tensor_data[ depth ];
        }

        matrix_type& operator[]( size_t depth )
        {
            return const_cast<matrix_type&>(
            		const_cast<const tensor&>(*this)[depth]
            	);
        }

        const value_type& operator()( size_t row, size_t col, size_t depth ) const
        {
            return _tensor_data[ depth ]( row, col );
        }

        value_type& operator()( size_t row, size_t col, size_t depth )
        {
            return const_cast<value_type&>(
            		const_cast<const tensor&>(*this)( row, col, depth )
            	);
        }

        size_t cols_count() const
        {
            return _cols_count;
        }

        size_t rows_count() const
        {
            return _rows_count;
        }

        size_t depth() const
        {
            return _depth;
        }

        const tensor_type& data() const
        {
            return _tensor_data;
        }

        friend bool operator==( const tensor& lhs, const tensor& rhs )
        {
        	if( lhs.depth() != rhs.depth() )
                throw std::invalid_argument( "Tensor depths mismatch" );

        	for( size_t d = 0; d < lhs.depth(); ++d )
        		if( lhs[d] != rhs[d] )
        			return false;

        	return true;
        }

        friend std::ostream& operator <<( std::ostream& ostr, const tensor& t )
		{
            for( size_t d = 0; d < t.depth(); ++d )
        			ostr << t[d] << std::endl;
			return ostr;
		}

    protected:
        size_t _rows_count;
        size_t _cols_count;
        size_t _depth;

        tensor_type _tensor_data;
    };

    template< class T, class F = std::equal_to<T> >
	bool is_equal( const tensor<T>& lhs, const tensor<T>& rhs, F equal = F() )
	{
		if( lhs.depth() != rhs.depth() ||
            lhs.rows_count() != rhs.rows_count() ||
            lhs.cols_count() != rhs.cols_count() ) {
                throw std::invalid_argument( "Tensor sizes mismatch" );
        }

        for( size_t d = 0; d < lhs.depth(); ++d )
            for( size_t r = 0; r < lhs.rows_count(); ++r )
                for( size_t c = 0; c < lhs.cols_count(); ++c )
                    if( ! equal(lhs(r,c,d), rhs(r,c,d)) )
                        return false;

        return true;
	}

    template< class T, class F = std::not_equal_to<T> >
	bool is_not_equal( const tensor<T>& lhs, const tensor<T>& rhs, F not_equal = F() )
	{
		if( lhs.depth() != rhs.depth() ||
            lhs.rows_count() != rhs.rows_count() ||
            lhs.cols_count() != rhs.cols_count() ) {
                throw std::invalid_argument( "Tensor sizes mismatch" );
        }

        for( size_t d = 0; d < lhs.depth(); ++d )
            for( size_t r = 0; r < lhs.rows_count(); ++r )
                for( size_t c = 0; c < lhs.cols_count(); ++c )
                    if( not_equal(lhs(r,c,d), rhs(r,c,d)) )
                        return true;

        return false;
	}
}
