#ifndef TASK2_MATRIX_H
#define TASK2_MATRIX_H

#include <array>

template<typename type, std::size_t row, std::size_t column>
using Matrix = std::array<std::array<type, column>, row>;

template<typename type, std::size_t row, std::size_t column>
void CopyMatrix(Matrix<type, row, column> & dest,
                Matrix<type, row, column> src);

#endif // TASK2_MATRIX_H
