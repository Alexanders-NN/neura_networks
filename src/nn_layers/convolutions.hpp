#include <functional>
#include <exception>

#include "../tensor/Matrix.hpp"
#include "../tensor/Tensor.hpp"



namespace layers {

    enum class edge_type {
        none,
        zeros,
        same,
        mirror
    };

    using matrix_convolution_f = std::function<types::matrix(types::matrix matrix, types::matrix kernel,
                                                             size_t origin_x, size_t origin_y)>;


    matrix_convolution_f matrix_convolution_no_edge =
            [](types::matrix matrix,
               types::matrix kernel,
               size_t origin_x = 0, size_t origin_y = 0) -> types::matrix
            {
                std::vector<double> rez_matrix;
                size_t new_heigth = matrix.get_heigth() - (kernel.get_heigth() + 1) / 2;
                size_t new_width = matrix.get_width() - (kernel.get_width() + 1) / 2;

                for (size_t h = 0; h < new_heigth; ++h)
                {
                    for (size_t w = 0; w < new_width; ++w)
                    {
                        int summ = 0;
                        for (size_t i = 0; i < kernel.get_heigth(); ++i)
                        {
                            for (size_t j = 0; j < kernel.get_width(); ++j)
                            {
                                summ += matrix(w + j, h + i) * kernel(j, i);
                            }
                        }
                        rez_matrix.push_back(summ);
                    }
                }

                return types::matrix( new_width, new_heigth, rez_matrix.begin(), rez_matrix.end() );
            };

    matrix_convolution_f matrix_convolution_same =
            [](types::matrix matrix,
               types::matrix kernel,
               size_t origin_x = 0, size_t origin_y = 0) -> types::matrix
            {
                std::vector<double> rez_matrix;
                for (size_t h = 0; h < matrix.get_heigth(); ++h)
                {
                    for (size_t w = 0; w < matrix.get_width(); ++w)
                    {
                        int summ = 0;
                        for (size_t i = 0; i < kernel.get_heigth(); ++i)
                        {
                            for (size_t j = 0; j < kernel.get_width(); ++j)
                            {
                                int new_x = w + j - origin_x;
                                int new_y = h + i - origin_y;
                                if (new_x >= 0)
                                {
                                    if ( new_x >= matrix.get_width() )
                                        new_x = matrix.get_width() - 1;
                                }
                                else
                                {
                                    new_x = 0;
                                }

                                if (new_y >= 0)
                                {
                                    if( new_y >= matrix.get_heigth() )
                                        new_y = matrix.get_heigth() - 1;
                                }
                                else
                                {
                                    new_y = 0;
                                }
                                summ += matrix(new_x, new_y) * kernel(j, i);
                            }
                        }
                        rez_matrix.push_back(summ);
                    }
                }
                return types::matrix( matrix.get_width(), matrix.get_heigth(), rez_matrix.begin(), rez_matrix.end() );
            };

    matrix_convolution_f matrix_convolution_mirror =
            [](types::matrix matrix,
               types::matrix kernel,
               size_t origin_x = 0, size_t origin_y = 0) -> types::matrix
            {
                std::vector<double> rez_matrix;
                for (size_t h = 0; h < matrix.get_heigth(); ++h)
                {
                    for (size_t w = 0; w < matrix.get_width(); ++w)
                    {
                        int summ = 0;
                        for (size_t i = 0; i < kernel.get_heigth(); ++i)
                        {
                            for (size_t j = 0; j < kernel.get_width(); ++j)
                            {
                                int new_x = w + j - origin_x;
                                int new_y = h + i - origin_y;
                                if (new_x >= 0)
                                {
                                    if ( new_x >= matrix.get_width() )
                                    {
                                        new_x *= -1;
                                        new_x += 2*(matrix.get_width() - 1);
                                    }
                                }
                                else
                                {
                                    new_x *= -1;
                                }

                                if (new_y >= 0)
                                {
                                    if( new_y >= matrix.get_heigth() )
                                    {
                                        new_y *= -1;
                                        new_y += 2*(matrix.get_width() - 1);
                                    }
                                }
                                else
                                {
                                    new_y *= -1;
                                }
                                summ += matrix(new_x, new_y) * kernel(j, i);
                            }
                        }
                        rez_matrix.push_back(summ);
                    }
                }
                return types::matrix( matrix.get_width(), matrix.get_heigth(), rez_matrix.begin(), rez_matrix.end() );
            };

    matrix_convolution_f matrix_convolution_zeros =
            [](types::matrix matrix,
               types::matrix kernel,
               size_t origin_x = 0, size_t origin_y = 0) -> types::matrix
            {
                std::vector<double> rez_matrix;
                for (size_t h = 0; h < matrix.get_heigth(); ++h)
                {
                    for (size_t w = 0; w < matrix.get_width(); ++w)
                    {
                        int summ = 0;
                        for (size_t i = 0; i < kernel.get_heigth(); ++i)
                        {
                            for (size_t j = 0; j < kernel.get_width(); ++j)
                            {
                                int new_x = w + j - origin_x;
                                int new_y = h + i - origin_y;
                                if( (new_x >= 0) && (new_x < matrix.get_width() -1) && (new_y >= 0) &&
                                    (new_y < matrix.get_heigth() - 1) )
                                {
                                    summ += matrix(new_x, new_y) * kernel(j, i);
                                }
                            }
                        }
                        rez_matrix.push_back(summ);
                    }
                }
                return types::matrix( matrix.get_width(), matrix.get_heigth(), rez_matrix.begin(), rez_matrix.end() );
            };


    /*
    using matrix_convolution_f = std::function<types::matrix::value_type(types::matrix matrix, types::matrix kernel,
                                                                         size_t x, size_t y,
                                                                         size_t origin_x, size_t origin_y)>;


    matrix_convolution_f matrix_convolution_no_edge =
            [](types::matrix matrix,
               types::matrix kernel,
               size_t x, size_t y,
               size_t origin_x = 0, size_t origin_y = 0) -> types::matrix::value_type
            {
                int summ = 0;
                for (size_t i = 0; i < kernel.heigth(); ++i)
                {
                    for (size_t j = 0; j < kernel.width(); ++j)
                    {
                        int new_x = x + j - origin_x;
                        int new_y = y + i - origin_y;
                        if ( (new_x < 0) || (new_y < 0) )
                        {
                            throw std::out_of_range("Error! Invalid index!");
                        }
                        summ += matrix(new_x, new_y) * kernel(j, i);
                    }
                }
                return summ;
            };

    matrix_convolution_f matrix_convolution_same =
            [](types::matrix matrix,
               types::matrix kernel,
               size_t x, size_t y,
               size_t origin_x = 0, size_t origin_y = 0) -> types::matrix::value_type
            {
                int summ = 0;
                for (size_t i = 0; i < kernel.heigth(); ++i)
                {
                    for (size_t j = 0; j < kernel.width(); ++j)
                    {
                        int new_x = x + j - origin_x;
                        int new_y = y + i - origin_y;
                        if ( new_x < 0 )
                            new_x = 0;
                        if ( new_y < 0 )
                            new_y = 0;
                        summ += matrix(new_x, new_y) * kernel(j, i);
                    }
                }
                return summ;
            };

    matrix_convolution_f matrix_convolution_mirror =
            [](types::matrix matrix,
               types::matrix kernel,
               size_t x, size_t y,
               size_t origin_x = 0, size_t origin_y = 0) -> types::matrix::value_type
            {
                int summ = 0;
                for (size_t i = 0; i < kernel.heigth(); ++i)
                {
                    for (size_t j = 0; j < kernel.width(); ++j)
                    {
                        int new_x = x + j - origin_x;
                        int new_y = y + i - origin_y;
                        if ( new_x < 0 )
                            new_x *= -1;
                        if ( new_y < 0 )
                            new_y *= -1;
                        summ += matrix(new_x, new_y) * kernel(j, i);
                    }
                }
                return summ;
            };

    matrix_convolution_f matrix_convolution_zeros =
            [](types::matrix matrix,
               types::matrix kernel,
               size_t x, size_t y,
               size_t origin_x = 0, size_t origin_y = 0) -> types::matrix::value_type
            {
                int summ = 0;
                for (size_t i = 0; i < kernel.heigth(); ++i)
                {
                    for (size_t j = 0; j < kernel.width(); ++j)
                    {
                        int new_x = x + j - origin_x;
                        int new_y = y + i - origin_y;
                        if ( (new_x >= 0) && (new_y >= 0) )
                        {
                            summ += matrix(new_x, new_y) * kernel(j, i);
                        }
                    }
                }
                return summ;
            };
    */

    /*
    struct matrix_convolution_same : public matrix_convolution
    {
        auto operator(types::matrix matrix, types::matrix kernel, size_t depth, size_t x, size_t y)
        {
            //It is necessary to realize until the evening of Sunday (deadline = 19.11.17 / 22: 00)
        }
    };

    struct matrix_convolution_mirror : public matrix_convolution
    {
        auto operator(types::matrix matrix, types::matrix kernel, size_t depth, size_t x, size_t y)
        {
            //It is necessary to realize until the evening of Sunday (deadline = 19.11.17 / 22: 00)
        }
    };

    struct matrix_convolution_zeros : public matrix_convolution
    {
        auto operator(types::matrix matrix, types::matrix kernel, size_t depth, size_t x, size_t y)
        {
            //It is necessary to realize until the evening of Sunday (deadline = 19.11.17 / 22: 00)
        }
    };
    */


    matrix_convolution_f convolution(edge_type conv_edge_type = edge_type::mirror)
    {
        switch ( conv_edge_type  ) {
            case edge_type::none:
                return matrix_convolution_no_edge();

            case edge_type::zeros:
                return matrix_convolution_zeros();

            case edge_type::same:
                return matrix_convolution_same();

            case edge_type::mirror:
                return matrix_convolution_mirror();

            default:
                return convolution(); // Here will be your favorite variant
        }
    }

    types::matrix convolution_tensor(types::tensor tensor, types::tensor kernel,
                                     edge_type conv_edge_type = edge_type::mirror)
    {
        if (tensor.get_depth() != kernel.get_depth())
        {
            throw std::logic_error ("The depth of the tensor and the depth of the kernal don`t coincide!");
        }
        matrix_convolution_f fun = convolution(conv_edge_type);
        types::matrix rez_matrix;
        size_t origin_x = (kernel.get_width() + 1) / 2;
        size_t oridin_y = (kernel.get_heigth() + 1) / 2;
        for (size_t d = 0; d < tensor.get_depth(); ++d)
        {
            rez_matrix += fun(tensor.data()[d], kernel.data()[d], origin_x, oridin_y);
        }
        return rez_matrix;
    }
}
