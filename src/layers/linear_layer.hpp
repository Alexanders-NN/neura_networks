#pragma once

#include "layer.hpp"


namespace layers {

    template<class T>
    struct linear_layer_parameter
            : public layer_info
    {
        using value_type = T;
        using weights_type = math::matrix<value_type>;
        using bias_type = math::matrix<value_type>;


        template<class Weights, class Bias>
        linear_layer_parameter( Weights&& weights, Bias&& bias )
            : layer_info( types::linear )
            , _weights( std::forward<Weights>(weights) )
            , _bias( std::forward<Bias>(bias) )
        {}

        auto weights() const
            -> const weights_type&
        {
            return _weights;
        }

        auto bias() const
            -> const bias_type&
        {
            return _bias;
        }

        auto weights_bias() const
        {
            return std::make_pair( _weights, _bias );
        }

        weights_type _weights;
        bias_type    _bias;
    };


    template<class T>
    struct linear_layer
            : public basic_layer<T>
    {
        using value_type = T;
        using base_t = basic_layer<value_type>;
        using tensor_type = typename base_t::tensor_type;

        using parameter_type = linear_layer_parameter<value_type>;

        template<class... Args>
        linear_layer( Args&&... args )
            : base_t(
                types::linear,
                [this]( const tensor_type& tensor )
                {
                    auto [weights, bias] =
                            get<parameter_type>( this->parameter() ).weights_bias();

                    const auto& vector = tensor[0];
                    auto result = weights * vector + bias;
                    return tensor_type({ result });
                },
                parameter_type( std::forward<Args>(args)... )
            )
        {}
    };

    template<class T, class... Args>
    auto make_linear_layer( Args&&... args ) -> layer_ptr<T>
    {
        using layer_t = linear_layer<T>;
        auto param = linear_layer_parameter<T>( std::forward<Args>(args)... );
        return std::make_shared<layer_t>( std::move(param) );
    }
}
