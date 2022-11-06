#include <iostream>
#include <gtest/gtest.h>

TEST(TestName, Subtest_1) {
    ASSERT_TRUE(1 == 2);
    std::cout << "After assertion\n";
}

TEST(TestName, Subtest_2) {
    ASSERT_FALSE(1 == 2);
    std::cout << "After assertion\n";
}

TEST(TestName2, Subtest_1) {
    EXPECT_FALSE(1 == 2);
    std::cout << "After expection\n";
}

TEST(TestName2, Subtest_2) {
    EXPECT_TRUE(1 == 2);
    std::cout << "After expection\n";
}

TEST(TestName3, Subtest_1) {
    ASSERT_EQ(1, 2);
    std::cout << "After assertion\n";
}

TEST(TestName3, Subtest_2) {
    EXPECT_EQ(1, 1);
    std::cout << "After expect_eq\n";
}

int main(int argc, char** argv) {
    std::cout << "works!\n";

    testing::InitGoogleTest(&argc, argv);

    RUN_ALL_TESTS();

    // Success - всё норм
    // EXPECT - ожидается, но при неожидаемом нефатально
    // ASSERT - фатальная ошибка, выход из теста моментально

    return 0;
}