#include "matrix.h"
#include <print>

int main() {
    Matrix m1{2, 2, 2.0f};
    Matrix m2{2, 2, 1.0f};

    m1 -= m2;

    Matrix m3 = m1 - m2;

    std::println("Matrix 3 = Matrix 1 - Matrix 2");
    Math::print(m3);

    std::println("Matrix 1");
    Math::print(m1);

    std::println("Matrix 1 at (0,0) = {}", m1[0, 0]);
    std::println("Matrix 3 at (0,0) = {}", m3[0, 0]);

    Vector v1{4, 3.0};
    Vector v2{4, 1.0};

    v1 -= v2;

    Math::print(v1);

    return 0;
}
