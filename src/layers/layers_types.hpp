#pragma once

#include <variant>

namespace layers {

    enum class types {
        linear,      // y = Wx+b
        function,    // [[[ y ]]] = [[[ f(x) ]]] то
        convolution, // y = [ x*k1, x*k2, ... , x*kn ]
        pooling,     // y = pooling( x, rules )
        dropout,     // [[[ y ]]] = 0 | [[[ x ]]] : p | (1-p)
        custom,
    };

    class layer_info
    {
    public:
        layer_info( types layer_type )
                : _type( layer_type )
        {}

        auto who_am_i() const -> types
        {
            return _type;
        }

        auto type() const -> types
        {
            return _type;
        }

    protected:
        types _type;
    };

    template< class T >
    struct function_layer_parameter;


    template< class T >
    struct linear_layer_parameter;

    template <class T >
    struct dropout_parameter;

    /*
    template< class T >
    class convolution_layer_parameter;

    template< class T >
    class pooling_layer_parameter;
    */


    template< class T >
    struct union_parameter
            : layer_info
    {
        using union_t = std::variant<
                //empty_parameter
                function_layer_parameter<T>
                , linear_layer_parameter<T>
                , dropout_parameter<T>
        >;

        template< class Union >
        union_parameter( types type, Union&& u_parameter )
                : layer_info( type )
                , _param_union( std::forward<Union>(u_parameter) )
        {}

        union_t _param_union;
    };

    template<typename Type, class T>
    auto get( const union_parameter<T>& un )
    {
        return std::get<Type>( un._param_union );
    }

}
