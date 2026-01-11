#include "matrix.h"
#include <print>

int main() {
    Matrix m1{2, 2, 2.0f};
    Matrix m2{2, 2, 1.0f};

    m1 += m2;

    Matrix m3 = m1 + m1;

    std::println("Matrix 1 + Matrix 2");
    matPrint(m3);

    std::println("Matrix 1");
    matPrint(m1);

    return 0;
}
