#include "matrix.h"
#include <print>

Matrix::Matrix() : nrows_(0), ncols_(0), size_(0), data_(std::make_unique<f32[]>(0)) {}

Matrix::Matrix(usize nrows, usize ncols)
    : nrows_(nrows), ncols_(ncols), size_(nrows * ncols), data_(std::make_unique<f32[]>(nrows * ncols)) {}

// TODO: Check performance between std::make_unique and std::make_unique_for_overwrite
Matrix::Matrix(usize nrows, usize ncols, float fillVal)
    : nrows_(nrows), ncols_(ncols), size_(nrows * ncols), data_(std::make_unique<f32[]>(nrows * ncols)) {
    std::fill(data_.get(), data_.get() + size_, fillVal);
}

Vector::Vector() : size_(0), data_(Matrix()) {}
Vector::Vector(usize nele) : size_(nele), data_(Matrix(nele, 1)) {}
Vector::Vector(usize nele, f32 fillVal) : size_(nele), data_(Matrix(nele, 1, fillVal)) {}

void Math::print(const Matrix &in) {
    auto nrows = in.rows();
    auto ncols = in.cols();
    for (usize r{0}; r < nrows; r++) {
        std::print("| ");
        for (usize c{0}; c < ncols; c++) std::print("{} ", in[r, c]);
        std::println("|");
    }
}

void Math::print(const Vector &in) {
    auto nele = in.size();
    std::print("| ");
    for (usize i{0}; i < nele; i++) std::print("{} ", in[i]);
    std::println("|");
}
