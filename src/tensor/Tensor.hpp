#pragma once

#include <iostream>
#include <vector>

#include "Matrix.hpp"


namespace types {

	template<class T>
	class tensor
	{
		using value_type = T;
		using size_type = size_t;
		using matrix_type = matrix;
		using tensor_type = std::vector<matrix_type>;

	public:
		tensor()
			: width(0)
			, heigth(0)
			, depth(0)
			, tensor_data()
		{}

		tensor(const std::vector<T> & pixels, size_type depth, size_type width, size_type heigth)
			: width(width)
			, heigth(heigth)
			, depth(depth)
		{
			for (size_type i = 0; i < depth; ++i)
			{
				tensor_data.push_back(std::vector<value_type>(pixels.begin() + i * width * heigth,
					pixels.begin() + (i + 1) * width * heigth));
			}
		}

		template<class It>
		tensor(size_type depth, size_type width, size_type heigth, It begin, It end) 
		{
			//It is necessary to realize until the evening of Sunday (deadline = 19.11.17 / 22: 00)
			//It should work: 
			/*	
				vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
				tensor t (2, 3, 2, v.begin(), v.end());
			*/
		}

		tensor(std::initializer_list<matrix_type>& matrixes) 
		{
			//It is necessary to realize until the evening of Sunday (deadline = 19.11.17 / 22: 00)
			//It should work: 
			/*	
				matrix m1 = {...}
				matrix m2 = {...}

				tensor t = {
					m1, 
					m2,
				};

				// m1 and m2 should have same dimensions !!!
			*/
		}

		tensor(const tensor& obj) 
		{
			//It is necessary to realize until the evening of Sunday (deadline = 19.11.17 / 22: 00)
		}

		tensor(tensor&& obj) 
		{
			//It is necessary to realize until the evening of Sunday (deadline = 19.11.17 / 22: 00)
		}

		tensor& operator=(const tensor& obj) 
		{
			//It is necessary to realize until the evening of Sunday (deadline = 19.11.17 / 22: 00)
		}

		tensor& operator=(tensor&& obj) 
		{
			//It is necessary to realize until the evening of Sunday (deadline = 19.11.17 / 22: 00)
		}


		value_type& operator()(size_type depth, size_type x, size_type y)
		{
			//Rework, using the Matrix class from Matrix.hpp 
			// until the evening of Sunday (deadline = 19.11.17 / 22: 00)
		}

		value_type operator()(size_type depth, size_type x, size_type y) const
		{
			//Rework, using the Matrix class from Matrix.hpp 
			// until the evening of Sunday (deadline = 19.11.17 / 22: 00)
		}


		size_type width() const
		{
			return width;
		}

		size_type heigth() const
		{
			return heigth;
		}

		size_type depth() const
		{
			return depth;
		}

		const tensor_type& data() const
		{
			return tensor_data;
		}

		~tensor() = default;

	protected:
		size_type width;
		size_type heigth;
		size_type depth;

		tensor_type tensor_data;

	};
}