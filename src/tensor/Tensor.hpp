#pragma once
#include <iostream>
#include <vector>

template<class T>
class tensor
{
	using value_type = T;
	using size_type = size_t;
	using matrix_type = std::vector<value_type>;
	using tensor_type = std::vector<matrix_type>;

	size_type width;
	size_type heigth;
	size_type depth;
	tensor_type matrix;

public:
	tensor()
		: width(0)
		, heigth(0)
		, depth(0)
		, matrix()
	{}

	tensor(const std::vector<T> & pixels, value_type depth, value_type width, value_type heigth)
		: width(width)
		, heigth(heigth)
		, depth(depth)
	{
		for (size_type i = 0; i < depth; ++i)
		{
			matrix.push_back(std::vector<value_type>(pixels.begin() + i * width * heigth,
				pixels.begin() + (i + 1) * width * heigth));
		}
	}

	~tensor() = default;

	value_type& operator()(size_type depth, size_type x, size_type y)
	{
		return matrix[depth][heigth * y + x];
	}

	value_type operator()(size_type depth, size_type x, size_type y) const
	{
		return matrix[depth][heigth * y + x];
	}

	/*Tensor& make_tensor(const std::vector<T> & pixels, value_type depth, value_type width, value_type heigth) const
	{
		Tensor tensor;
		if (pixels.size() != depth * width * heigth)
			return Tensor();
		for (size_type i = 0; i < depth; ++i)
		{
			tensor.
		}
	}*/

	value_type get_width() const
	{
		return width;
	}

	value_type get_heigth() const
	{
		return heigth;
	}

	value_type get_depth() const
	{
		return depth;
	}

	tensor_type get_martix() const
	{
		return matrix;
	}

	//friend T convolution(const Tensor<T> & tensor, const Tensor<T> & core, size_t depth, size_t x, size_t y);
};

template<class T>
T convolution(const tensor<T> & tensor_t, const tensor<T> & core, size_t depth, size_t x, size_t y)
{
	T summ = 0;
	for (size_t k = 0; k < core.get_depth(); ++k)
	{
		for (size_t i = 0; i < core.get_heigth(); ++i)
		{
			for (size_t j = 0; j < core.get_width(); ++j)
			{
				summ += tensor_t(depth + k, x + j, y + i) * core(k, j, i);
			}
		}
	}
	return summ;
}