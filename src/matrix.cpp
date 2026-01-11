#include "matrix.h"
#include <print>

void matPrint(const Matrix &m) {
    auto nrows = m.rows();
    auto ncols = m.cols();

    for (usize r{0}; r < nrows; r++) {
        std::print("| ");
        for (usize c{0}; c < ncols; c++) std::print("{} ", m[r, c]);
        std::println("|");
    }
}
