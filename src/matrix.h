#ifndef MATRIX_H
#define MATRIX_H

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <cstring>
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

    // TODO: Check performance between std::make_unique and std::make_unique_for_overwrite
    Matrix(usize nrows, usize ncols, float fillVal)
        : nrows_(nrows), ncols_(ncols), size_(nrows * ncols), data_(std::make_unique<f32[]>(nrows * ncols)) {
        std::fill(data_.get(), data_.get() + size_, fillVal);
    }

    constexpr usize rows() const { return nrows_; }
    constexpr usize cols() const { return ncols_; }
    constexpr usize size() const { return size_; }

    constexpr Matrix &operator+=(const Matrix &other) {
        // TODO: Implement error checking for matrices of different rows / columns
        std::span<f32> spanSelf(this->data_.get(), size_);
        std::span<f32> spanOther(other.data_.get(), other.size_);

        for (auto [refSelf, refOther] : std::views::zip(spanSelf, spanOther)) refSelf += refOther;

        return *this;
    }

    constexpr Matrix operator+(const Matrix &other) {
        Matrix ret(this->nrows_, this->ncols_);
        std::memcpy(ret.data_.get(), this->data_.get(), size_ * sizeof(f32));
        ret += other;
        return ret;
    }

    constexpr f32 &operator[](usize i, usize j) { return *(data_.get() + (ncols_ * i + j)); }
    constexpr const f32 &operator[](usize i, usize j) const { return *(data_.get() + (ncols_ * i + j)); }

  private:
    usize nrows_;
    usize ncols_;

    usize size_;

    f32p data_;
};

void matPrint(const Matrix &m);

#endif // MATRIX_H
