#include <gmp.h>

class Matrix
{
    public:
        Matrix (int row, int col);
        Matrix (int row, int col, const mpz_t** m);
        ~Matrix ();
        Matrix operator+ (const Matrix& m) const;
        Matrix operator- () const;
        Matrix operator- (const Matrix& m) const;
        Matrix operator* (const Matrix& m) const;
        void operator+= (const Matrix& m);
        void operator-= (const Matrix& m);
        void operator*= (const Matrix& m);
        Matrix pow (const unsigned int pow) const;
        void set (int i, int j, mpz_t val);
        void set (int i, int j, int val);
        static Matrix id (int row, int col);
        static void copy (Matrix& m1, Matrix& m2);
        void showStdOut ();
    private:
        int row, col;
        mpz_t** mat;
        void allocSpace();
};
