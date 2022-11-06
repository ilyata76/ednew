#include <iostream>
#include <sstream>
#include <gtest/gtest.h>

// использование одних данных для разных тестов - TEST_F - тест для целого класса

struct BankAccount {
    int balance;

    BankAccount() 
        : balance{ 0 } {}

    explicit BankAccount(const int balance) 
        : balance{ balance } {}

    void deposit(int amount) {
        balance += amount;
    }

};

struct BankAccountTest : testing::Test {
    BankAccount* account;

    BankAccountTest() 
        : account{ new BankAccount } {}

    ~BankAccountTest() {
        delete account;
    }

};

TEST_F( BankAccountTest, 
        BankAccountStartsEmpty ) {
    EXPECT_EQ(0, account->balance);
}

TEST_F( BankAccountTest, 
        CanDepositMoney ) {
    account->deposit(100);
    EXPECT_EQ(100, account->balance);
}

TEST_F( BankAccountTest,
        BankAccountEmpty ) {
    EXPECT_EQ(0, account->balance);
}

int main(int argc, char** argv) {
    std::cout << "works!\n";

    testing::InitGoogleTest(&argc, argv);

    RUN_ALL_TESTS();

    return 0;
}
