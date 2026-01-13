#ifndef STORAGE_H
#define STORAGE_H

#include <algorithm>
#include <cstring>
#include <memory>
#include <stdexcept>
#include <vector>

using Scalar = double;

class Storage {
  public:
    inline std::size_t size() const noexcept { return size_; }

    inline Scalar *data() noexcept { return buffer_.get(); }
    inline const Scalar *data() const noexcept { return buffer_.get(); }

    inline void fill(Scalar value) noexcept { std::fill_n(buffer_.get(), size_, value); }
    inline void zero() noexcept { fill(0.0); }

    inline void swap(Storage &other) noexcept {
        std::swap(buffer_, other.buffer_);
        std::swap(size_, other.size_);
    }

    inline void copy_from(const Storage &other) {
        if (size_ != other.size_) throw std::length_error{"Unequal lengths"};
        std::memcpy(buffer_.get(), other.buffer_.get(), size_ * sizeof(Scalar));
    }

    inline Scalar &operator[](std::size_t i) {
        if (i >= size_) throw std::out_of_range{"Storage::operator[]"};
        return buffer_[i];
    }

    inline const Scalar &operator[](std::size_t i) const {
        if (i >= size_) throw std::out_of_range{"Storage::operator[]"};
        return buffer_[i];
    }

  private:
    std::unique_ptr<Scalar[]> buffer_;
    std::size_t size_;

  protected:
    explicit Storage(std::size_t size) : buffer_(std::make_unique<Scalar[]>(size)), size_(size) {}

    explicit Storage(std::size_t size, std::vector<Scalar> data) : buffer_(std::move(data.data())), size_(size) {}

    explicit Storage(std::size_t size, Scalar *data) : buffer_(std::move(data)), size_(size) {}

    explicit Storage(std::size_t size, std::unique_ptr<Scalar[]> data) : buffer_(std::move(data)), size_(size) {}

    Storage() noexcept : buffer_(nullptr), size_(0) {}

    Storage(Storage &&other) noexcept = default;
    Storage &operator=(Storage &&other) noexcept = default;

    Storage(const Storage &) = delete;
    Storage &operator=(const Storage &) = delete;
};

#endif // STORAGE_H
