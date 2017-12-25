compiler    := g++-7
std_version := -std=c++17
flags       := $(std_version) -Wall


TestDir := tests
TensorTestDir := $(TestDir)/tensor
LayerTestDir := $(TestDir)/layers
ModelTestDir := $(TestDir)/models




clear:
	rm *.o *.test.out *.out

all_tests: tensor_tests \
		   layers_tests \
		   models_tests

#----------------tensor-block---------------------------------------------------
tensor_tests: _matrix_test _tensor_test

_matrix_test:
	$(compiler) $(flags) $(TensorTestDir)/matrix.cpp -o matrix.test.out
	./matrix.test.out

_tensor_test:
	$(compiler) $(flags) $(TensorTestDir)/tensor.cpp -o tensor.test.out
	./tensor.test.out
#---------------[tensor-block]--------------------------------------------------


#----------------layers-block---------------------------------------------------
layers_tests: _types \
			  _function_layer_test \
			  _linear_layer_test

_types:
	$(compiler) $(flags) $(LayerTestDir)/types.cpp -o types.test.out
	./types.test.out

_linear_layer_test:
	$(compiler) $(flags) $(LayerTestDir)/liner_layer.cpp -o liner_layer.test.out
	./liner_layer.test.out

_function_layer_test:
	$(compiler) $(flags) $(LayerTestDir)/function_layer.cpp -o \
			function_layer.test.out
	./function_layer.test.out
#---------------[layers-block]--------------------------------------------------

#----------------models-block---------------------------------------------------
models_tests: _sequence_test

_sequence_test:
	$(compiler) $(flags) $(ModelTestDir)/sequence.cpp -o sequence.test.out
	./sequence.test.out

#---------------[models-block]--------------------------------------------------
