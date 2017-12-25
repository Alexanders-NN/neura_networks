#include <vector>

#include "../tensor.hpp"
#include "../layers.hpp"


namespace models {

    template< class T >
    class sequence
    {
    public:
        using value_type = T;
        using tensor_type = math::tensor<value_type>;
        using layer_ptr = layers::layer_ptr<value_type>;
        using layers_seq_t = std::vector<layer_ptr>;
        using pos_type = std::size_t;

    public:
        sequence() = default;
        sequence( const sequence& ) = default;
        sequence( sequence&& ) = default;

        sequence& operator=( const sequence& ) = default;
        sequence& operator=( sequence&& ) = default;


        template<class LayerPtr>
        pos_type add_layer( LayerPtr&& layer_pointer )
        {
            _layer_ptrs.push_back( layer_pointer );
            return _layer_ptrs.size() - 1;
        }

        tensor_type operator()( const tensor_type& tensor )
        {
            size_t seq_length = this->length();

            auto result = tensor;
            for( size_t i = 0; i < seq_length; ++i )
                result = _layer_ptrs[i]->run( result );

            return result;
        }

        const layers_seq_t& layer_ptrs() const
        {
            return _layer_ptrs;
        }

        const layer_ptr& operator[]( pos_type i ) const
        {
            return _layer_ptrs[i];
        }

        auto length() const
        {
            return _layer_ptrs.size();
        }

    protected:
        layers_seq_t _layer_ptrs;
    };

    template< class T >
    class learning_sequence
        : sequence<T>
    {
    public:
        using sequence_t = sequence<T>;
        using value_type = typename sequence_t::value_type;
        using tensor_type = typename sequence_t::tensor_type;
        using tensors_vector = std::vector<tensor_type>;

    public:

        template<class Sequence>
        learning_sequence( Sequence&& sequence )
            : sequence_t( std::forward<Sequence>(sequence) )
            , _results()
        {}

        tensor_type run( const tensor_type& tensor )
        {
            size_t seq_length = this->length();

            auto result = tensor;
            _input_tensor = result;
            for( size_t i = 0; i < seq_length; ++i ) {
                result = (*this)[i]->run( result );
                _results.push_back( result );
            }

            return result;
        }

    protected:
        tensors_vector _results;
        tensor_type _input_tensor;
        tensor_type _result_tensor;
    };

}
