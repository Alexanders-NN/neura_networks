#include "Matrix.hpp"
#include <vector>

namespace mlp_layer
{
    template <class T>
    class layer
    {
        virtual const types::matrix<T>& operator() (types::matrix<T>&) const = 0;

        virtual types::matrix<T>& operator() (types::matrix<T>&) = 0;

        virtual layer& make_layer() = 0;
    };

    template <class T>
    types::matrix<T> make_vector(const std::vector<T>& data)
    {
        return types::matrix(1, data.size(), data.begin(), data.end());
    }
}