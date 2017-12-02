#include <bits/valarray_after.h>
#include "layer.hpp"
#include <functional>

namespace layer
{
    template <class T>
    class function
    {
    public:
        using value_type = T;
        using size_type = size_t;
        using no_linear_function = std::function<types::matrix(types::matrix& vector_x)>;

    protected:
        no_linear_function using_function;

    public:
        function() = default;

        function(no_linear_function func )
                : using_function( func )
        {}

        const types::matrix& operator() (types::matrix<value_type >& vector_x) const
        {
            return using_function(vector_x);
        }

        types::matrix& operator() (types::matrix<value_type>& vector_x)
        {
            return const_cast<types::matrix&>(const_cast<function> (*this) (vector_x) );
        }
    };
}