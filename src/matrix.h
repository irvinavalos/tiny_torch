#ifndef MATRIX_H
#define MATRIX_H

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <memory>
#include <ranges>
#include <span>

using usize = std::size_t;

using f32 = std::float_t;

using f32p = std::unique_ptr<f32[]>;

class Matrix {
  public:
    Matrix() : nrows_(0), ncols_(0), size_(0), data_(std::make_unique<f32[]>(0)) {}

    Matrix(usize nrows, usize ncols)
        : nrows_(nrows), ncols_(ncols), size_(nrows * ncols), data_(std::make_unique<f32[]>(nrows * ncols)) {}

    Matrix(usize nrows, usize ncols, float fillVal)
        : nrows_(nrows), ncols_(ncols), size_(nrows * ncols), data_(std::make_unique<f32[]>(nrows * ncols)) {
        std::fill(data_.get(), data_.get() + size_, fillVal);
    }

    constexpr usize rows() const { return nrows_; }
    constexpr usize cols() const { return ncols_; }
    constexpr usize size() const { return size_; }

    constexpr f32 at(usize i, usize j) const { return *(data_.get() + (ncols_ * i + j)); }

    Matrix &operator+=(const Matrix &src) {
        std::span<f32> spanSelf(this->data_.get(), size_);
        std::span<f32> spanSrc(src.data_.get(), size_);

        for (auto [refSelf, refSrc] : std::views::zip(spanSelf, spanSrc)) {
            refSelf += refSrc;
        }

        return *this;
    }

  private:
    usize nrows_;
    usize ncols_;

    usize size_;

    f32p data_;
};

void matPrint(const Matrix &m);

#endif // MATRIX_H
