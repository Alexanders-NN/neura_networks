#pragma once

#include <functional>
#include <memory>

#include "../tensor.hpp"
#include "layers_types.hpp"


namespace layers {

    template<class T>
    class basic_layer
        : public layer_info
    {
    public:
        using value_type = T;
        using tensor_type = math::tensor<T>;
        using function_type = std::function<tensor_type(tensor_type)>;
        using union_parameter_t = union_parameter<value_type>;

        template<class UnionParam>
        basic_layer( types layer_type, function_type function, UnionParam&& param )
            : layer_info( layer_type )
            , _function( function )
            , _parameter( layer_type, std::forward<UnionParam>(param) )
        {}

        auto operator()( const tensor_type& tensor )
            -> tensor_type
        {
                return _function( tensor );
        }

        auto run( const tensor_type& tensor )
            -> tensor_type
        {
                return (*this)( tensor );
        }

        const union_parameter_t& parameter() const
        {
            return _parameter;
        }

    protected:
        function_type     _function;
        union_parameter_t _parameter;
    };

    template<class T>
    using layer_ptr = std::shared_ptr<basic_layer<T>>;
}
