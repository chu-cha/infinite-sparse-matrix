#pragma once

#include <map>

template <typename T, T N>
class SparseMatrix {

    using ContainerType = std::map<std::pair<size_t, size_t>, T>;

public:
    class RowProxy {
    private:
        SparseMatrix& matrix;
        size_t row;

    public:
        RowProxy(SparseMatrix& matrix, size_t row) : matrix(matrix), row(row) {}

        class ElementProxy {
            SparseMatrix& matrix;
            size_t row, col;

        public:
            ElementProxy(SparseMatrix& matrix, size_t row, size_t col)
                : matrix(matrix), row(row), col(col) {
            }

            T operator=(const T& value) {
                matrix.set(row, col, value);
                return value;  // Возвращаем значение, а не прокси
            }

            // Неявное приведение к T (для auto val = m[1][1] не работает!!)
            operator T() const {
                return matrix.get(row, col);
            }
        };

        ElementProxy operator[](size_t col) {
            return ElementProxy(matrix, row, col);
        }
    };

    RowProxy operator[](size_t row) {
        return RowProxy(*this, row);
    }

    size_t size() const {
        return data.size();
    }

    // Итератор, возвращающий (x, y, value)
    class Iterator {
        using IterType = typename ContainerType::const_iterator;
        IterType it_;

    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = std::tuple<size_t, size_t, T>;
        using difference_type = std::ptrdiff_t;
        using pointer = value_type*;
        using reference = value_type&;

        explicit Iterator(IterType it) : it_(it) {}

        value_type operator*() const {
            return { it_->first.first, it_->first.second, it_->second };
        }

        Iterator& operator++() {
            ++it_;
            return *this;
        }

        bool operator!=(const Iterator& other) const {
            return it_ != other.it_;
        }
    };

    Iterator begin() const {
        return Iterator(data.begin());
    }

    Iterator end() const {
        return Iterator(data.end());
    }

private:
    ContainerType data;
    T default_value = N;

    T get(size_t row, size_t col) const {
        auto it = data.find({ row, col });
        return it != data.end() ? it->second : default_value;
    }

    void set(size_t row, size_t col, const T& value) {
        if (value != default_value) {
            data[{row, col}] = value;
        }
        else {
            data.erase({ row, col });
        }
    }
};
