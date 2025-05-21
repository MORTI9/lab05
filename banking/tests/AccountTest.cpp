#include "mocks/MockAccount.h"
#include <gtest/gtest.h>

TEST(AccountTest, InitialBalance) {
    MockAccount account(1, 100);
    EXPECT_EQ(account.GetBalance(), 100);
    EXPECT_EQ(account.id(), 1);
}

TEST(AccountTest, ChangeBalance) {
    MockAccount account(1, 100);
    account.Lock();
    account.ChangeBalance(50);
    EXPECT_EQ(account.GetBalance(), 150);
}
