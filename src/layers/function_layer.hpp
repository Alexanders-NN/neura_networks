#pragma once

#include <variant>
#include "layer.hpp"


namespace layers {

    template<class T>
    struct function_layer_parameter
            : public layer_info
    {
        using value_type = T;
        using simple_function_type = std::function<value_type(value_type)>;

        function_layer_parameter( simple_function_type simple_func )
            : layer_info( types::function )
            , _simple_func( simple_func )
        {}

        inline auto operator()( const value_type& value )
            -> value_type
        {
            return _simple_func( value );
        }

        simple_function_type _simple_func;
    };

    template<class T>
    struct function_layer
            : public basic_layer<T>
    {
        using value_type = T;
        using base_t = basic_layer<value_type>;
        using tensor_type = typename base_t::tensor_type;

        using parameter_type = function_layer_parameter<value_type>;

        template<class... Args>
        function_layer( Args&&... args )
            : base_t(
                types::function,
                [this]( const tensor_type& tensor )
                {
                    auto func = get<parameter_type>( this->parameter() );

                    return tensor_type(
                        tensor.rows_count(),
                        tensor.cols_count(),
                        tensor.depth(),
                        [&func, &tensor](auto r, auto c, auto d) -> value_type
                        {
                            return func( tensor( r, c, d ) );
                        }
                    );
                },
                parameter_type( std::forward<Args>(args)... )
              )
        {}
    };

    template<class T, class F>
    auto make_function_layer( F&& function ) -> layer_ptr<T>
    {
        using layer_t = function_layer<T>;
        auto param = function_layer_parameter<T>( std::forward<F>(function) );
        return std::make_shared<layer_t>( std::move(param) );
    }
}
