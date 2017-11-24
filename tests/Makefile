compiler    := g++
std_version := -std=c++14
flags       := $(std_version) -Wall




tensor_tests:
	$(compiler) $(flags) tensor.cpp -o tensor.test.out
	./tensor.test.out

clear:
	rm *.o *.test.out *.out