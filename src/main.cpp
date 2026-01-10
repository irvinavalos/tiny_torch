#include "matrix.h"

int main() {
    Matrix m1{2, 2, 2.0f};
    Matrix m2{2, 2, 1.0f};

    m1 += m2;

    matPrint(m1);

    return 0;
}
