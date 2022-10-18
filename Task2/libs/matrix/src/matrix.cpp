#include "matrix.h"

int Matrix::GetRow(Trio<Choice> choices)
{
    int row = 0;
    for(Choice choice : choices)
    {
        row = (row << 1) + choice;
    }

    return row;
}

Trio<int> & Matrix::operator[](int index)
{
    return data_[index];
}
