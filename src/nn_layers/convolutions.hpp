#include 		<functional>

#include "../tensor/Matrix.hpp"
#include "../tensor/Tensor.hpp"



namespace layers {

	enum class edge_type {
		none,
		zeros,
		same,
		mirror
	};
	
	using matrix_convolution_f = std::function<types::matrix::value_type(types::matrix matrix, types::matrix kernel,
																		 size_t x, size_t y)>;


	matrix_convolution_f matrix_convolution_no_edge = 
			[](types::matrix matrix, 
				types::matrix kernel, 
				size_t x, size_t y) -> types::matrix::value_type
			{
				int summ = 0;
				for (size_t i = 0; i < kernel.heigth(); ++i)
				{
					for (size_t j = 0; j < kernel.width(); ++j)
					{
						int new_x = x+ j;
						int new_y = y + i;
						if ( new_x - origin_x < 0 )
							new_x = 0;
						if ( new_y - origin_y < 0 )
							new_y = 0;
						summ += matrix[new_y][new_x] * kernel[i][j];
					}
				}
				return summ;
			};

	matrix_convolution_f matrix_convolution_same = 
			[](types::matrix matrix,
			   types::matrix kernel,
			   size_t x, size_t y,
			   size_t origin_x = 0, size_t origin_y = 0) -> types::matrix::value_type
			{
				int summ = 0;
				for (size_t i = 0; i < kernel.heigth(); ++i)
				{
					for (size_t j = 0; j < kernel.width(); ++j)
					{
						if ( (x + j - origin_x < 0) || (y + i - origin_y < 0) )
						{
							throw std::out_of_range("Error! Invalid index!")
						}
						summ += matrix[y + i][x + j] * kernel[i][y];
					}
				}
				return summ;
			};

	matrix_convolution_f matrix_convolution_mirror = 
			[](types::matrix matrix, 
				types::matrix kernel, 
				size_t x, size_t y) -> types::matrix::value_type
			{
				int summ = 0;
				for (size_t i = 0; i < kernel.heigth(); ++i)
				{
					for (size_t j = 0; j < kernel.width(); ++j)
					{
						int new_x = x+ j;
						int new_y = y + i;
						if ( new_x - origin_x < 0 )
							new_x *= -1;
						if ( new_y - origin_y < 0 )
							new_y *= -1;
						summ += matrix[new_y][new_x] * kernel[i][j];
					}
				}
				return summ;
			};

	matrix_convolution_f matrix_convolution_zeros = 
			[](types::matrix matrix,
			   types::matrix kernel,
			   size_t x, size_t y,
			   size_t origin_x = 0, size_t origin_y = 0) -> types::matrix::value_type
			{
				int summ = 0;
				for (size_t i = 0; i < kernel.heigth(); ++i)
				{
					for (size_t j = 0; j < kernel.width(); ++j)
					{
						if ( (x + j - origin_x >= 0) && (y + i - origin_y >= 0) )
						{
							summ += matrix[y + i][x + j] * kernel[i][y];
						}
					}
				}
				return summ;
			};

	
	/*
	struct matrix_convolution_same : public matrix_convolution
	{
		auto operator(types::matrix matrix, types::matrix kernel, size_t depth, size_t x, size_t y)
		{
			//It is necessary to realize until the evening of Sunday (deadline = 19.11.17 / 22: 00)
		}
	};

	struct matrix_convolution_mirror : public matrix_convolution
	{
		auto operator(types::matrix matrix, types::matrix kernel, size_t depth, size_t x, size_t y)
		{
			//It is necessary to realize until the evening of Sunday (deadline = 19.11.17 / 22: 00)
		}
	};

	struct matrix_convolution_zeros : public matrix_convolution
	{
		auto operator(types::matrix matrix, types::matrix kernel, size_t depth, size_t x, size_t y)
		{
			//It is necessary to realize until the evening of Sunday (deadline = 19.11.17 / 22: 00)
		}
	};
	*/


	matrix_convolution_f convolution(edge_type conv_edge_type = edge_type::m irror)
	{
		switch ( conv_edge_type  ) {
			case edge_type::none:
				return matrix_convolution_no_edge();
			
			case edge_type::zeros:
				return matrix_convolution_zeros();

			case edge_type::same:
				return matrix_convolution_same();

			case edge_type::mirror:
				return matrix_convolution_mirror();

			default:
				return convolution(); // Here will be your favorite variant
		}
	}

}
