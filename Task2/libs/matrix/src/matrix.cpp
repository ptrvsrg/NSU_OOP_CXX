#include "matrix.h"

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
    if (!in_file.is_open()) throw std::invalid_argument(matrix_file + " : File opening error");

    int row = 0;
    std::array<Trio<int>, 8> buffer;
    while (!in_file.eof())
    {
        if (row == 8) throw std::invalid_argument(matrix_file + " : Wrong matrix");

        in_file >> buffer[row][0]
                >> buffer[row][1]
                >> buffer[row][2];
        ++row;
    }

    if (row != 8) throw std::invalid_argument(matrix_file + " : Wrong matrix");

    data_ = std::move(buffer);
}

Trio<int> & Matrix::operator[](int index)
{
    return data_[index];
}
