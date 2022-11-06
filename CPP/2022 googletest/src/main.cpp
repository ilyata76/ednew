#include <iostream>
#include <sstream>
#include <gtest/gtest.h>

// ТЕСТОВЫЙ СЛУЧАЙ с наборот тестовых данных TEST_P

struct BankAccount {
    int balance;

    BankAccount() 
        : balance{ 0 } {}

    explicit BankAccount(const int balance) 
        : balance{ balance } {}

    void deposit(int amount) {
        balance += amount;
    }

    bool withdraw(int amount) {
        if (amount <= balance) {
            balance -= amount;
            return true;
        }
        return false;
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

// создадим структуру состояния


struct account_state {
    int initial_balance;
    int withdraw_amount;
    int final_balance;
    bool success;
};

struct WithdrawAccountTest : BankAccountTest, testing::WithParamInterface<account_state> {
    WithdrawAccountTest() {
        account->balance = GetParam().initial_balance;
    }
};

TEST_P(WithdrawAccountTest, FinalBalance) {
    auto as = GetParam();
    auto success = account->withdraw(as.withdraw_amount);
    EXPECT_EQ(as.final_balance, account->balance);
    EXPECT_EQ(as.success, success);
}

// теперь создадим тестовый случай
INSTANTIATE_TEST_CASE_P(Default, WithdrawAccountTest, testing::Values(account_state{ 100, 50, 50, true }, account_state{ 100, 200, 100, false }));

int main(int argc, char** argv) {
    std::cout << "works!\n";

    testing::InitGoogleTest(&argc, argv);

    RUN_ALL_TESTS();

    return 0;
}
