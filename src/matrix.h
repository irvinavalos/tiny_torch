#ifndef MATRIX_H
#define MATRIX_H

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
    Matrix();
    Matrix(usize nrows, usize ncols);
    // TODO: Check performance between std::make_unique and std::make_unique_for_overwrite
    Matrix(usize nrows, usize ncols, float fillVal);

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

    constexpr Matrix &operator-=(const Matrix &other) {
        // TODO: Implement error checking for matrices of different rows / columns
        std::span<f32> spanSelf(this->data_.get(), size_);
        std::span<f32> spanOther(other.data_.get(), other.size_);

        for (auto [refSelf, refOther] : std::views::zip(spanSelf, spanOther)) refSelf -= refOther;

        return *this;
    }

    constexpr Matrix operator-(const Matrix &other) {
        Matrix ret(this->nrows_, this->ncols_);
        std::memcpy(ret.data_.get(), this->data_.get(), size_ * sizeof(f32));
        ret -= other;
        return ret;
    }

    // TODO: Handle out of range errors
    constexpr f32 &operator[](usize i, usize j) { return *(data_.get() + (ncols_ * i + j)); }
    constexpr const f32 &operator[](usize i, usize j) const { return *(data_.get() + (ncols_ * i + j)); }

  private:
    usize nrows_;
    usize ncols_;

    usize size_;

    f32p data_;
};

class Vector {
  public:
    Vector();
    Vector(usize nele);
    Vector(usize nele, f32 fillVal);

    constexpr usize size() const { return size_; }

    constexpr Vector &operator+=(const Vector &other) {
        // TODO: Implement error checking for matrices of different rows / columns
        this->data_ += other.data_;
        return *this;
    }

    constexpr Vector &operator-=(const Vector &other) {
        // TODO: Implement error checking for matrices of different rows / columns
        this->data_ -= other.data_;
        return *this;
    }

    constexpr f32 &operator[](usize i) { return data_[i, 0]; }
    constexpr const f32 &operator[](usize i) const { return data_[i, 0]; }

  private:
    usize size_;
    Matrix data_;
};

namespace Math {
void print(const Matrix &in);
void print(const Vector &in);
}; // namespace Math

#endif // MATRIX_H
