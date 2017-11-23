#pragma once

#include <iostream>
#include <vector>
#include <exception>

#include "Matrix.hpp"


namespace types {

    template<class T>
    class tensor
    {
        using value_type = T;
        using size_type = size_t;
        using matrix_type = matrix;
        using tensor_type = std::vector<matrix_type>;

    public:
        tensor()
                : width(0)
                , heigth(0)
                , depth(0)
                , tensor_data()
        {}

        tensor(const std::vector<T> & pixels, size_type tensor_depth, size_type tensor_width, size_type tensor_heigth)//exeption?
                : width(tensor_width)
                , heigth(tensor_heigth)
                , depth(tensor_depth)
        {
            for (size_type i = 0; i < depth; ++i)
            {
                matrix_type new_matrix(width, heigth, pixels.begin() + i * width * heigth,
                                       pixels.begin() + (i + 1) * width * heigth);
                tensor_data.push_back(new_matrix);
            }
        }

        template<class It>
        tensor(It begin, It end, size_type tensor_depth, size_type tensor_width, size_type tensor_heigth)
                : width(tensor_width)
                , heigth(tensor_heigth)
                , depth(tensor_depth)
        {
            if(tensor_depth * tensor_width * tensor_heigth != end - begin)
            {
                depth = 0;
                width = 0;
                heigth = 0;
                throw std::logic_error("Error! Incorrect initialization tensor");
            }
            for (size_type i = 0; i < depth; ++i)
            {
                matrix_type new_matrix(width, heigth, begin + i * width * heigth,
                                       begin + (i + 1) * width * heigth);
                tensor_data.push_back(new_matrix);
            }
        }

        tensor(std::initializer_list<matrix_type>& matrixes)
        {
            depth = matrixes.size();
            width = matrixes.begin()->get_width();
            heigth = matrixes.begin()->get_heigth();
            for(auto & m : matrixes)
            {
                if( (m.get_heigth() != heigth) || (m.get_width() != width) )
                {
                    depth = 0;
                    width = 0;
                    heigth = 0;
                    tensor_data.clear();
                    throw std::logic_error("Error! Incorrect initialization tensor");
                }
                tensor_data.push_back(m);
            }
        }

        tensor(const tensor& obj)
                : depth (obj.depth)
                , width (obj.width)
                , heigth (obj.heigth)
                , tensor_data (obj.tensor_data)
        {}

        tensor(tensor&& obj)
        {
            std::swap(depth, obj.depth);
            std::swap(heigth, obj.heigth);
            std::swap(width, obj.width);
            std::swap(tensor_data, obj.tensor_data);
        }

        tensor& operator=(const tensor& obj)
        {
            if(this != &obj)
            {
                depth = obj.depth;
                width = obj.width;
                heigth = obj.heigth;
                tensor_data = obj.tensor_data;
            }
            return *this;
        }

        tensor& operator=(tensor&& obj)
        {
            if(this != &obj)
            {
                depth = obj.depth;
                width = obj.width;
                heigth = obj.heigth;
                tensor_data = obj.tensor_data;

                obj.depth = 0;
                obj.width = 0;
                obj.heigth = 0;
                obj.tensor_data.clear();
            }
            return *this;
        }


        const value_type& operator()(size_type tensor_depth, size_type x, size_type y) const
        {
            return tensor_data[tensor_depth][heigth * y + x];
        }

        value_type& operator()(size_type tensor_depth, size_type x, size_type y)
        {
            return static_cast<value_type&>( const_cast<const value_type&> (*this)(tensor_depth, x, y) );
        }

        size_type get_width() const
        {
            return width;
        }

        size_type get_heigth() const
        {
            return heigth;
        }

        size_type get_depth() const
        {
            return depth;
        }

        const tensor_type& data() const
        {
            return tensor_data;
        }

    protected:
        size_type width;
        size_type heigth;
        size_type depth;

        tensor_type tensor_data;

    };
}