#include <gtest/gtest.h>
#include "matrix.h"

std::array<Trio<int>, 8> matrix_data_ =
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

struct OptionArgs
{
    std::string matrix_file_;
    enum ExceptionType
    {
        NO,
        STREAM_EXCEPTION_TYPE,
        BIG_MATRIX_EXCEPTION_TYPE,
        LITTLE_MATRIX_EXCEPTION_TYPE
    } exception_type_;

    OptionArgs(std::string matrix_file,
               ExceptionType exception_type)
    :   matrix_file_(std::move(matrix_file)),
        exception_type_(exception_type) {}
};

TEST(test_constructors,
     without_args)
{
    Matrix matrix;

    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            EXPECT_EQ(matrix_data_[i][j],
                      matrix[i][j]);
        }
    }
}

class MatrixUpdateTest : public ::testing::TestWithParam<OptionArgs> {};
INSTANTIATE_TEST_SUITE_P
(
    test_update,
    MatrixUpdateTest,
    ::testing::Values
        (
            OptionArgs("file/matrix.txt",
                       OptionArgs::NO),
            OptionArgs("file/wrong_matrix0.txt",
                       OptionArgs::STREAM_EXCEPTION_TYPE),
            OptionArgs("file/wrong_matrix1.txt",
                       OptionArgs::LITTLE_MATRIX_EXCEPTION_TYPE),
            OptionArgs("file/wrong_matrix2.txt",
                       OptionArgs::BIG_MATRIX_EXCEPTION_TYPE)
        )
);

TEST_P(MatrixUpdateTest,
       file_exceptions)
{
    OptionArgs params = GetParam();
    Matrix matrix;

    switch(params.exception_type_)
    {
        case OptionArgs::NO:
            matrix.Update(params.matrix_file_);
            for (int i = 0; i < 8; ++i)
            {
                for (int j = 0; j < 3; ++j)
                {
                    EXPECT_EQ(matrix[i][j],
                              1);
                }
            }
            break;
        case OptionArgs::STREAM_EXCEPTION_TYPE:
            EXPECT_THROW
            (
                {
                    matrix.Update(params.matrix_file_);
                },
                std::ios_base::failure
            );
            break;
        case OptionArgs::LITTLE_MATRIX_EXCEPTION_TYPE:
            EXPECT_THROW
            (
                {
                    matrix.Update(params.matrix_file_);
                },
                LittleMatrixException
            );
            break;
        case OptionArgs::BIG_MATRIX_EXCEPTION_TYPE:
            EXPECT_THROW
            (
                {
                    matrix.Update(params.matrix_file_);
                },
                BigMatrixException
            );
    }
}

int main(int argc,
         char** argv)
{
    ::testing::InitGoogleTest(&argc,
                              argv);
    return RUN_ALL_TESTS();
}