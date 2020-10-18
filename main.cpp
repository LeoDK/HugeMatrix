#include "matrix.h"
#include <iostream>

int main ()
{
    Matrix m1 = Matrix(3,3);
    Matrix m2 = Matrix(3,3);
    // m1
    m1.set(0,0,1);
    m1.set(0,1,2);
    m1.set(0,2,3);
    m1.set(1,0,2);
    m1.set(1,1,3);
    m1.set(1,2,4);
    m1.set(2,0,3);
    m1.set(2,1,4);
    m1.set(2,2,5);
    // m2
    m2.set(0,0,1);
    m2.set(0,1,1);
    m2.set(0,2,1);
    m2.set(1,1,1);
    m2.set(2,2,1);
    m1.showStdOut();
    std::cout << std::endl;
    /*
    m2.showStdOut();
    std::cout << std::endl;
    (m1 + m2).showStdOut();
    std::cout << std::endl;
    (m1 - m2).showStdOut();
    std::cout << std::endl;
    (m1 * m2).showStdOut();
    std::cout << std::endl;
    (m2 * m1).showStdOut();
    std::cout << std::endl;
    */
    (m1.pow(4)).showStdOut();
    return 0;
}
