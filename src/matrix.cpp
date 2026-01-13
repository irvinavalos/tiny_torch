#include "matrix.h"
#include <print>

template <typename T> void print(const Matrix<T> &in) {
    auto nrows = in.rows();
    auto ncols = in.cols();

    for (std::size_t r{0}; r < nrows; r++) {
        std::print("| ");
        for (std::size_t c{0}; c < ncols; c++) std::print("{} ", in(r, c));
        std::println("|");
    }
}
