#include <gtest/gtest.h>
#include <strstream>
#include <tuple>
#include "print_tuple.h"

namespace
{
    struct USB_device
        {
        int vendor_ID_;
        int product_ID_;

        USB_device(int vendor_ID,
                   int product_ID)
            : vendor_ID_(vendor_ID),
              product_ID_(product_ID) {}
    };

    std::ostream & operator<<(std::ostream & os,
                             const USB_device & value)
     {
        os << "{ " << value.vendor_ID_ << ", " << value.product_ID_ << " }";
        return os;
    }
}

TEST(tests_print_tuple,
     simple_test)
{
    USB_device usb_device(0x046d,
                          0x0825);
    auto tuple = std::make_tuple(1, "dog", 1.426, usb_device);

    std::stringstream tuple_out;
    std::stringstream check;

    tuple_out << tuple;
    check << std::get<0>(tuple) << ", "
          << std::get<1>(tuple) << ", "
          << std::get<2>(tuple) << ", "
          << std::get<3>(tuple);

    EXPECT_EQ(tuple_out.str(),
              check.str());
}

int main(int argc,
         char ** argv)
{
    ::testing::InitGoogleTest(&argc,
                              argv);
    return RUN_ALL_TESTS();
}