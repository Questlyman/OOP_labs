#include <gtest/gtest.h>
#include "../include/lab1.h"

TEST(test_01, basic_test_set)
{
    ASSERT_EQ(lab1("getout"), 3);
}

TEST(test_02, basic_test_set)
{
    ASSERT_EQ(lab1("i am g/r/ay"), 4);
}

TEST(test_03, basic_test_set)
{
    ASSERT_EQ(lab1("      "), 0);
}

TEST(test_04, basic_test_set)
{
    ASSERT_FALSE(only_letters_input("    hey rrtaaaahi3445"));
    ASSERT_TRUE(only_letters_input("dslfjlkjs   dlfjkkjlkdsjfjkajkdlfahjkdrwoeiruqklmcnnmmzkjlifdsarrwer"));
    ASSERT_TRUE(only_letters_input("  dslfjlkjsdlfjkk"));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}