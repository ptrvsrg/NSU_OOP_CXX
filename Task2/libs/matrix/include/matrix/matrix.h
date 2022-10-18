#ifndef TASK2_MATRIX_H
#define TASK2_MATRIX_H

#include <array>

#include "strategy_interface.h"

template<class T> using Trio = std::array<T, 3>;

class Matrix
{
public:
    Matrix() {};
    Matrix(const Matrix & src)
    {
        for (int i = 0; i < 8; ++i)
        {
            std::copy(src.data_[i].cbegin(),
                      src.data_[i].cend(),
                      data_[i].begin());
        }
    }

    int GetRow(Trio<Choice> choices);
    Trio<int> & operator[] (int index);
private:
    std::array<Trio<int>, 8> data_ =
    {{
        { 4, 4, 4, },
        { 3, 3, 9, },
        { 3, 9, 3, },
        { 0, 5, 5, },
        { 9, 3, 3, },
        { 5, 0, 5, },
        { 5, 5, 0, },
        { 1, 1, 1, }
    }};
};

#endif // TASK2_MATRIX_H
