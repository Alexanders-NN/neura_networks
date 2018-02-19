#pragma once

#include "layer.hpp"
#include <ctime>

namespace layers{

    template <class T>
    struct dropout_parameter
        : public layer_info
    {
        using value_type = T;

        dropout_parameter( size_t perc )
                : layer_info( types ::dropout)
                , _percent( perc )
        {}

        double percent() const
        {
            return _percent;
        }

        size_t _percent;
    };


    template <class T>
    struct dropout_layer
        : public basic_layer<T>
    {
        using value_type = T;
        using base_t = basic_layer<value_type>;
        using tensor_types = typename base_t::tensor_type;

        using parameter_type = dropout_parameter<value_type>;

        template <class... Args>
        dropout_layer( Args&&... args )
                : base_t (
                types::dropout,
                [this]( const tensor_type& tensor )
                {
                    srand ( time(0) );
                    auto perc = get<parameter_type >( this->parameter() ).percent();

                    tensor_types new_tensor(
                            tensor.row_count,
                            tensor.cols_count,
                            tensor.deths,
                            0
                    );

                    for (auto d = 0; d < tensor.deths; ++d)
                    {
                        if ( rand() % 101 > perc )
                            new_tensor[d] = tensor[d];
                    }
                    return new_tensor;

                    /*
                    return tensor_types(
                        tensor.row_count(),
                        tensor.cols_count(),
                        tensor.deths(),
                        [perc, &tensor](auto r, auto c, auto d) -> value_type
                        {
                            if ( rand() % 101 <= perc)
                                return 0;
                            else
                                return tensor( r, c, d );
                        }
                    );
                    */
                },
                parameter_type( std::forward<Args>(args)... )
                )
        {}
    };

}