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
        auto v =  vector_y(i, 1) - answers(i, 1);
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
    types::matrix<T> derivative( vector_y.height(), 1 );
    for (size_t i = 0; i < derivative.height(); ++i)
    {
        derivative(i, 1) = ( loss( vector_y(i, 1) + delta_y, answers(i, 1) ) -
                            loss( vector_y(i, 1), answers(i, 1) ) ) / delta_y;
    }
    return derivative;
}

template <class T>
types::matrix<T>& dE_dx (const types::matrix<T>& de_dy, const types::matrix<T>& w)
{
    types::matrix<T> derivative( de_dy.height(), 1 );
    for (size_t i = 0; i < derivative.height(); ++i)
    {
        T summ = 0;
        for (size_t j = 0; j < w.height(); ++j)
        {
            summ += de_dy(j, 1) * w(j, i);
        }
        de_dy.data().push_back(summ);
    }
    return derivative;
}

template <class T>
types::matrix<T>& dE_dw (const types::matrix<T>& de_dy, const types::matrix<T>& vector_x)
{
    types::matrix derivative( de_dy.height(), vector_x.height() );
    for (size_t i = 0; i < derivative.width(); ++i)
    {
        for (size_t j = 0; j < derivative.height(); ++j)
        {
            derivative(j, i)= de_dy(j, 1) * vector_x (i, 1);
        }
    }
}