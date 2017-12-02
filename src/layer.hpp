#include "Matrix.hpp"

namespace mlp_layer
{
    template <class T>
    class layer
    {
        virtual const types::matrix<T>& operator() (types::matrix<T>&) const = 0;

        virtual types::matrix<T>& operator() (types::matrix<T>&) = 0;

        virtual layer& make_layer() = 0;
    };


}