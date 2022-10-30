#include "matrix.h"

LittleMatrixException::LittleMatrixException(const std::string & matrix_file)
    :   std::invalid_argument(matrix_file + " : Little matrix") {}

BigMatrixException::BigMatrixException(const std::string & matrix_file)
    :   std::invalid_argument(matrix_file + " : Big matrix") {}

Matrix::Matrix(const Matrix & src)
{
    for (int i = 0; i < 8; ++i)
    {
        std::copy(src.data_[i].cbegin(),
                  src.data_[i].cend(),
                  data_[i].begin());
    }
}

int Matrix::GetRowIndex(Trio<Choice> choices)
{
    int row = 0;
    for(Choice choice : choices)
    {
        row = (row << 1) + choice;
    }

    return row;
}

void Matrix::Update(const std::string & matrix_file)
{
    std::ifstream in_file(matrix_file,
                          std::ios::in);
    in_file.exceptions(std::ios::badbit | std::ios::failbit) ;

    int row = 0;
    std::array<Trio<int>, 8> buffer;
    while (!in_file.eof())
    {
        if (row == 8) throw BigMatrixException(matrix_file);

        in_file >> buffer[row][0]
                >> buffer[row][1]
                >> buffer[row][2];
        ++row;
    }

    if (row != 8) throw LittleMatrixException(matrix_file);

    data_ = std::move(buffer);
}

Trio<int> & Matrix::operator[](int index)
{
    return data_[index];
}
