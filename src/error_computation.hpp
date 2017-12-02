#include "Matrix.hpp"
#include <exception>
#include <cmath>

template <class T>
T loss (const types::matrix<T>& vector_y, const types::matrix<T>& answers)
{
    if ( vector_y.width()!= answers.width() || vector_y.height() != answers.height() )
    {
        throw std::invalid_argument( "Matrix sizes mismatch" );
    }
    T loss = 0;
    for (size_t i = 0; i < vector_y.width(); ++i)
    {
        auto v =  vector_y(1, i) - answers(1, i);
        loss += pow(v, 2);
    }
    return loss / 2;
}

double loss(double y, double answers)
{
    return pow( (y - answers), 2 ) / 2;
}

template <class T>
types::matrix<T>& dE_dy (const types::matrix<T>& vector_y, const types::matrix<T>& answers, double delta_y)
{
    if ( vector_y.width()!= answers.width() || vector_y.height() != answers.height() )
    {
        throw std::invalid_argument( "Matrix sizes mismatch" );
    }
    types::matrix<T> derivative( 1, vector_y.width() );
    for (size_t i = 0; i < derivative.width(); ++i)
    {
        derivative(1, i) = ( loss( vector_y(1, i) + delta_y, answers(1, i) ) -
                            loss( vector_y(1, i), answers(1, i) ) ) / delta_y;
    }
    return derivative;
}

template <class T>
types::matrix<T>& dE_dx (const types::matrix<T>& de_dy, const types::matrix<T>& w)
{
    types::matrix<T> derivative( 1, de_dy.width() );
    for (size_t i = 0; i < derivative.width(); ++i)
    {
        T summ = 0;
        for (size_t j = 0; j < w.height(); ++j)
        {
            summ += de_dy(1, j) * w(j, i);
        }
        de_dy.data().push_back(summ);
    }
    return derivative;
}

template <class T>
types::matrix<T>& dE_dw (const types::matrix<T>& de_dy, const types::matrix<T>& vector_x)
{
    types::matrix derivative(vector_x.width(), de_dy.width());
    for (size_t i = 0; i < derivative.height(); ++i)
    {
        for (size_t j = 0; j < derivative.width(); ++j)
        {
            derivative(i, j)= de_dy(1, j) * vector_x (1, i);
        }
    }
}