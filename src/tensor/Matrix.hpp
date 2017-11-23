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
		using size_type = size_t;
		using matrix_type = std::vector<value_type>;

	public:

		matrix(size_type matrix_width = 0, size_type matrix_heigth = 0)
			: width( matrix_width )
			, heigth( matrix_heigth )
			, matrix_data( matrix_width * matrix_heigth )
		{}


		matrix(const matrix& obj)
            : width (obj.width)
            , heigth (obj.heigth)
            , matrix_data (obj.matrix_data)
        {}

		matrix(matrix&& obj)
		{
			std::swap(heigth, obj.heigth);
			std::swap(width, obj.width);
			std::swap(matrix_data, obj.matrix_data);
		}

		matrix& operator=(const matrix& obj) 
		{
            if ( this != &obj )
            {
                heigth = obj.heigth;
                width = obj.width;
                matrix_data = obj.matrix_data;
            }
            return  *this;
		}

		matrix& operator=(matrix&& obj)
		{
            if ( this != &obj )
            {
                heigth = obj.heigth;
                width = obj.width;
                matrix_data = obj.matrix_data;

                obj.heigth = 0;
                obj.width = 0;
                obj.matrix_data.clear();
            }
            return  *this;
		}

		matrix(std::initializer_list<std::initializer_list<value_type>> rows)
		{
            heigth = rows.size();
            width = rows.begin()->size();
            for ( auto& h : rows )
            {
                if (h.size() != width)
				{
					heigth = 0;
					width = 0;
					matrix_data.clear();
					throw std::logic_error("Error! Incorrect initialization matrix");
				}
                matrix_data.insert( matrix_data.end(), h.begin(), h.end()() );
            }
		}


		template<class It>
		matrix(size_type matrix_width, size_type matrix_heigth, It begin, It end)
			: width( matrix_width )
			, heigth( matrix_heigth )
			, matrix_data( begin, end )
		{
			if( matrix.size() != width * heigth ) {
				width = 0;
				heigth = 0;
				matrix_data.clear();
                throw std::logic_error( "Error! Incorrect initialization matrix" );
			}
		}

		template<class It>
		bool fill_by_sequence(It begin, It end) //???
		{
			matrix_type new_matrix( begin, end );

			if( matrix_data.size() != width * heigth ) {
				return false;
			}

			matrix_data = std::move(new_matrix);

			return true;
		}

        matrix& operator+=(const matrix& rhs)
        {
            for( size_t i = 0; i < this->matrix_data().size(); ++i)
            {
                this->matrix_data()[i] += rhs.matrix_data()[i];
            }
            return *this;
        }

		const value_type& operator()(size_type x, size_type y) const
		{
			return matrix_data[heigth * y + x];
		}

		value_type& operator()(size_type x, size_type y)
		{
			return static_cast<value_type&>( const_cast<const matrix&>(*this)( x, y ) );
		}

		size_type width() const
		{
			return width;
		}

		size_type heigth() const
		{
			return heigth;
		}

		const matrix_type& data() const
		{
			return matrix_data;
		}

	protected:
		size_type width;
		size_type heigth;
		matrix_type matrix_data;
	};


    matrix operator +(const matrix& a, const matrix& b)
    {
        matrix rez(a);
        rez += b;
        return rez;
    }
}
