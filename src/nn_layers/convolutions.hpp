#include "../tensor/Matrix.hpp"
#include "../tensor/Tensor.hpp"


namespace /*think up a name*/ {

	enum class edge_type {
		none,
		zeros,
		same,
		mirror
	};
	
	struct matrix_convolution
	{
		virtual auto operator(types::matrix matrix, types::matrix kernel, size_t depth, size_t x, size_t y);
	};

	struct matrix_convolution_no_edge : public matrix_convolution
	{
		auto operator(types::matrix matrix, types::matrix kernel, size_t depth, size_t x, size_t y)
		{
			//It is necessary to realize until the evening of Sunday (deadline = 19.11.17 / 22: 00)
		}
	};

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


	matrix_convolution convoution(edge_type conv_edge_type = edge_type::/*Choose your favorite type*/)
	{
		switch ( conv_edge_type ) {
			case edge_type::none:
				return matrix_convolution_no_edge();
			
			case edge_type::zeros:
				return matrix_convolution_zeros();

			case edge_type::same:
				return matrix_convolution_same();

			case edge_type::mirror:
				return matrix_convolution_mirror();

			default:
				return convoution(); // Here will be your favorite variant
		}
	}

}
