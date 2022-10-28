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
    bool exception_;
    std::string error_message_;

    OptionArgs(std::string matrix_file,
               bool exception,
               std::string error_message)
    :   matrix_file_(std::move(matrix_file)),
        exception_(exception),
        error_message_(std::move(error_message)) {}
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
            OptionArgs("/home/acer/NSU_OOP_CXX/Task2/libs/matrix/test/matrix.txt",
                       false,
                       ""),
            OptionArgs("/home/acer/NSU_OOP_CXX/Task2/libs/matrix/test/wrong_matrix0.txt",
                       true,
                       "/home/acer/NSU_OOP_CXX/Task2/libs/matrix/test/wrong_matrix0.txt : File opening error"),
            OptionArgs("/home/acer/NSU_OOP_CXX/Task2/libs/matrix/test/wrong_matrix1.txt",
                       true,
                       "/home/acer/NSU_OOP_CXX/Task2/libs/matrix/test/wrong_matrix1.txt : Wrong matrix"),
            OptionArgs("/home/acer/NSU_OOP_CXX/Task2/libs/matrix/test/wrong_matrix2.txt",
                       true,
                       "/home/acer/NSU_OOP_CXX/Task2/libs/matrix/test/wrong_matrix2.txt : Wrong matrix")
        )
);

TEST_P(MatrixUpdateTest,
       file_exceptions)
{
    OptionArgs params = GetParam();
    Matrix matrix;

    try
    {
        matrix.Update(params.matrix_file_);
        EXPECT_FALSE(params.exception_);

        for (int i = 0; i < 8; ++i)
        {
            for (int j = 0; j < 3; ++j)
            {
                EXPECT_EQ(matrix[i][j],
                          1);
            }
        }
    }
    catch (const std::invalid_argument & ex)
    {
        EXPECT_STREQ(ex.what(),
                     params.error_message_.c_str());
    }
}

int main(int argc,
         char** argv)
{
    ::testing::InitGoogleTest(&argc,
                              argv);
    return RUN_ALL_TESTS();
}