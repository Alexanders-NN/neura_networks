compiler    := g++
std_version := -std=c++14
flags       := $(std_version) -Wall

RED='\033[0;31m'         #  ${RED}
GREEN='\033[0;32m'      #  ${GREEN}
WHITE='\e[0m'



matrix_tests:
	$(compiler) $(flags) matrix.cpp -o matrix.test.out
	./matrix.test.out

tensor_tests:
	$(compiler) $(flags) tensor.cpp -o tensor.test.out
	./tensor.test.out

clear:
	rm *.o *.test.out *.out