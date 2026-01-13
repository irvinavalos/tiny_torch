#ifndef MATRIX_H
#define MATRIX_H

#include "storage.h"

#include <cstddef>
#include <ranges>
#include <span>

template <class T = Scalar> class Matrix : private Storage<T> {
  public:
    Matrix() : Storage<T>(), nrows_(0), ncols_(0) {}
    Matrix(std::size_t r, std::size_t c) : Storage<T>(r * c), nrows_(r), ncols_(c) {}
    Matrix(std::size_t r, std::size_t c, Scalar value) : Storage<T>(r * c), nrows_(r), ncols_(c) { this->fill(value); }

    inline std::size_t rows() const noexcept { return nrows_; }
    inline std::size_t cols() const noexcept { return ncols_; }

    inline Matrix &operator+=(const Matrix &other) {
        if (this->nrows_ != other.nrows_ || this->ncols_ != other.ncols_)
            throw std::length_error("Matrix shape mismatch");

        std::span<Scalar> spanSelf(this->data(), this->size());
        std::span<Scalar> spanOther(other.data(), other.size());

        for (auto [refSelf, refOther] : std::views::zip(spanSelf, spanOther)) refSelf += refOther;

        return *this;
    }

    inline Matrix operator+(const Matrix &other) {
        Matrix ret(nrows_, ncols_);
        ret.copy_from(*this);
        ret += other;
        return ret;
    }

    inline Matrix &operator-=(const Matrix &other) {
        if (this->nrows_ != other.nrows_ || this->ncols_ != other.ncols_)
            throw std::length_error("Matrix shape mismatch");

        std::span<Scalar> spanSelf(this->data(), this->size());
        std::span<Scalar> spanOther(other.data(), other.size());

        for (auto [refSelf, refOther] : std::views::zip(spanSelf, spanOther)) refSelf -= refOther;

        return *this;
    }

    inline Matrix operator-(const Matrix &other) {
        Matrix ret(nrows_, ncols_);
        ret.copy_from(*this);
        ret -= other;
        return ret;
    }

    inline T &operator()(std::size_t i, std::size_t j) {
        if (i >= nrows_ || j >= ncols_) throw std::out_of_range("Matrix::operator()");
        return this->data()[ncols_ * i + j];
    }

    inline const T &operator()(std::size_t i, std::size_t j) const {
        if (i >= nrows_ || j >= ncols_) throw std::out_of_range("Matrix::operator()");
        return this->data()[ncols_ * i + j];
    }

  private:
    std::size_t nrows_;
    std::size_t ncols_;
};

template <typename T> void print(const Matrix<T> &in);

#endif // MATRIX_H
