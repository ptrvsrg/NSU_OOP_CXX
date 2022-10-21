#include "matrix.h"

int Matrix::GetRowIndex(Trio<Choice> choices)
{
    int row = 0;
    for(Choice choice : choices)
    {
        row = (row << 1) + choice;
    }

    return row;
}

void Matrix::Update(std::string matrix_file)
{
    std::ifstream in_file(matrix_file, std::ios::in);
    if (!in_file.is_open())
    {
        throw std::invalid_argument(matrix_file + " : File opening error");
    }

    int row = 0;
    while (!in_file.eof())
    {
        if (row == 8)
        {
            throw std::invalid_argument(matrix_file + " : Wrong matrix");
        }

        in_file >> data_[row][0] >> data_[row][1] >> data_[row][2];
        ++row;
    }

    if (row != 8)
    {
        throw std::invalid_argument(matrix_file + " : Wrong matrix");
    }
}

Trio<int> & Matrix::operator[](int index)
{
    return data_[index];
}
