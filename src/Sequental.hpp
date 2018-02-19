#include <bits/valarray_after.h>
#include "Matrix.hpp"
#include "layer.hpp"

template <class T>
class Sequental
{
public:
    using value_type = T;
    using size_type = size_t;

protected:
    std::vector<mlp_layer::layer> _layers;
    std::vector<types::matrix> vector_x;

public:
    mlp_layer::layer& add_layer();

    void trainig();

    void run();
};