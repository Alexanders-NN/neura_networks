#include <bits/valarray_after.h>
#include "layer.hpp"


namespace mlp_layer
{
    template <class T>
    class linear
            : mlp_layer::layer {
    protected:
        types::matrix<T> _w;
        types::matrix<T> _b;

    public:
        using value_type = T;
        using size_type = size_t;

    public:

        linear() = default;

        linear(types::matrix w, types::matrix b)
                : _w( w )
                , _b( b )
        {}

        const types::matrix<value_type >& operator()(types::matrix<value_type >& vector_x) const
        {
            types::matrix vector_y(1, _w.width());
            vector_y = vector_x * _w + _b;
            return vector_y;
        }

        types::matrix<value_type >& operator() (types::matrix<value_type >& vector_x)
        {
            return const_cast<types::matrix&> ( const_cast<const linear&> (*this) (vector_x) );
        }
    };
}