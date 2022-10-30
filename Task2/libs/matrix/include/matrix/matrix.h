#ifndef TASK2_MATRIX_H
#define TASK2_MATRIX_H

#include <array>
#include <fstream>

#include "strategy_interface.h"

template <class T> using Trio = std::array<T, 3>;

class LittleMatrixException : std::invalid_argument
{
public:
    LittleMatrixException(const std::string & matrix_file);
};

class BigMatrixException : std::invalid_argument
{
public:
    BigMatrixException(const std::string & matrix_file);
};

class Matrix
{
public:
    Matrix() {};
    Matrix(const Matrix & src);

    int GetRowIndex(Trio<Choice> choices);
    void Update(const std::string & matrix_file);
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
