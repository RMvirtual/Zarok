#include <string>
#include "gtest/gtest.h"

// Your test cases go here

TEST(HelloWorldTest, ShouldPass)
{
    std::string result {"Hello, World!"};
    std::string correctResult {"Hello, World!"};

    EXPECT_STREQ(result.c_str(), correctResult.c_str());
}


int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
