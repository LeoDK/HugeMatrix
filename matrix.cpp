#include "matrix.h"
#include <iostream>
#include <stdexcept>

Matrix::Matrix (int row_, int col_, const mpz_t** mat_)
       : row(row_), col(col_)
{
    allocSpace();
    for (int i=0; i<row; i++)
    {
        for (int j=0; j<col; j++)
        {
            mpz_set (mat[i][j], mat_[i][j]);
        }
    }
}

Matrix::Matrix (int row_, int col_)
       : row(row_), col(col_)
{
    allocSpace();
}

Matrix::~Matrix ()
{
    for (int i=0; i<row; i++)
    {
        for (int j=0; j<col; j++)
        {
            mpz_clear(mat[i][j]);
        }
        delete[] mat[i];
    }
    delete[] mat;
}

Matrix Matrix::operator+ (const Matrix& m) const
{
    if ( (col != m.col) || (row != m.row) )
    {
        throw std::runtime_error("Cannot add two matrix with different sizes");
    }
    Matrix ret = Matrix (row, col);
    for (int i=0; i<row; i++)
    {
        for (int j=0; j<col; j++)
        {
            mpz_add(ret.mat[i][j], mat[i][j], m.mat[i][j]);
        }
    }
    return ret;
}

Matrix Matrix::operator- () const
{
    Matrix ret = Matrix(row, col);
    for (int i=0; i<row; i++)
    {
        for (int j=0; j<col; j++)
        {
            mpz_neg(ret.mat[i][j], mat[i][j]);
        }
    }
    return ret;
}

Matrix Matrix::operator- (const Matrix& m) const
{
    return *this + (-m);
}

Matrix Matrix::operator* (const Matrix& m) const
{
    if (col != m.row)
        throw std::runtime_error("If doing m1 * m2, m1.col must be equal to m2.row");
    Matrix ret = Matrix (row, m.col);
    mpz_t tmp;
    mpz_init(tmp);
    for (int i=0; i<row; i++)
    {
        for (int j=0; j<m.col; j++)
        {
            for (int k=0; k<col; k++)
            {
                mpz_mul(tmp, mat[i][k], m.mat[k][j]);
                mpz_add(ret.mat[i][j], ret.mat[i][j], tmp);
            }
        }
    }
    mpz_clear(tmp);
    return ret;
}

void Matrix::operator+= (const Matrix& m)
{
    Matrix res = (*this) + m;
    copy(*this, res);
}

void Matrix::operator-= (const Matrix& m)
{
    Matrix res = (*this) - m;
    copy(*this, res);
}

void Matrix::operator*= (const Matrix& m)
{
    Matrix res = (*this) * m;
    copy(*this, res);
}

Matrix Matrix::pow (const unsigned int pow) const
{
    Matrix ret = Matrix::id(row, col);
    for (int k=0; k<pow; k++)
    {
        ret *= (*this);
    }
    return ret;
}

void Matrix::set (int i, int j, mpz_t val)
{
    mpz_set(mat[i][j], val);
}

void Matrix::set (int i, int j, int val)
{
    mpz_set_si(mat[i][j], val);
}

Matrix Matrix::id (int row, int col)
{
    Matrix ret = Matrix (row, col);
    for (int i=0; i<row; i++)
    {
        ret.set(i,i,1);
    }
    return ret;
}

void Matrix::copy (Matrix& m1, Matrix& m2) // "m1=m2"
{
    if ( (m1.col != m2.col) || (m1.row != m2.row) )
        throw std::runtime_error("Cannot copy matrix of different size");
    for (int i=0; i<m1.row; i++)
    {
        for (int j=0; j<m1.col; j++)
        {
            mpz_set(m1.mat[i][j], m2.mat[i][j]);
        }
    }
}

void Matrix::showStdOut ()
{
    for (int i=0; i<row; i++)
    {
        for (int j=0; j<col; j++)
        {
            std::cout << mpz_get_si(mat[i][j]) << " ";
        }
        std::cout << std::endl;
    }
}

void Matrix::allocSpace ()
{
    mat = new mpz_t*[row];
    for (int i=0; i<row; i++)
    {
        mat[i] = new mpz_t[col];
        for (int j=0; j<col; j++)
        {
            mpz_init(mat[i][j]);
            mpz_set_ui(mat[i][j], 0);
        }
    }
}
