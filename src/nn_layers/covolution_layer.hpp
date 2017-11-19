#pragma once

#include <iostream>
#include <vector>

#include "Tensor.hpp"

class convolution_layer
{
	using value_type = std::vector<Tensor<double>>;
	using size_type = size_t;

	value_type layer;
	size_type namber;

public:
	convolution_layer();

	convolution_layer(value_type tensors);

	~convolution_layer();

	Tensor<double>& operator()(Tensor<double>&);
};