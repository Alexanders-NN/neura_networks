#pragma once

#include <iostream>
#include <vector>
#include <exception>


//It is necessary to realize until the evening of Sunday (deadline = 19.11.17 / 22: 00)

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
		{
			//It is necessary to realize until the evening of Sunday (deadline = 19.11.17 / 22: 00)
		}

		matrix(matrix&& obj)
		{
			//It is necessary to realize until the evening of Sunday (deadline = 19.11.17 / 22: 00)
			std::swap(heigth, obj.heigth);
			std::swap(width, obj.width);
			std::swap(matrix_data, obj.matrix_data);
		}

		matrix& operator=(const matrix& obj) 
		{
			//It is necessary to realize until the evening of Sunday (deadline = 19.11.17 / 22: 00)
            if ( this != &obj )
            {
                heigth = obj.heigth;
                width = obj.width;
                matrix_data = obj.matrix_data;
            }
            return  *this;
		}

		matrix& operator=(matrix&& obj) //improve!
		{
			//It is necessary to realize until the evening of Sunday (deadline = 19.11.17 / 22: 00)
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

		matrix(const std::initializer_list<std::initializer_list<value_type>>& rows)
		{
			//It is necessary to realize until the evening of Sunday (deadline = 19.11.17 / 22: 00)
			/*
				//It should work: 
				matrix m = {
					{ 0,   5,  3, 7  },
					{ 0,  42,  3, 7  },
					{ 50,  5, -3, 7  },
					{ 0,  15,  3, 7  },
					{ 0,   5,  3, 71 },
					{ 0,   5,  3, 73 },
				};
				
				//But it shouldn't:
				matrix m = {
					{ 0,   5,  3, 7  },
					{ 0,  42,  3, 7  },
					{ 50,  5, -3, 7  },
					{ 0,  15,  3 },    // <- Row size mismatch!!! Throw exception (any type U want)
					{ 0,   5,  3, 71 },
					{ 0,   5,  3, 73 },
				};

			*/
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
			, matrix_data( begin, end ) // Does it work?
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

}
