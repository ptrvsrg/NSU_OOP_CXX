#include "matrix.h"

template<typename type, std::size_t row, std::size_t column>
void CopyMatrix(Matrix<type, row, column> & dest,
                Matrix<type, row, column> src)
{
    for (int i = 0; i < row; ++i)
    {
        std::copy(src[i].cbegin(), src[i].cend(), dest[i].begin());
    }
}