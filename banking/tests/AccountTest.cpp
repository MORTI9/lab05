#include "mocks/MockAccount.h"
#include <gtest/gtest.h>

TEST(AccountTest, Initialization) {
    MockAccount account(1, 100);
    EXPECT_EQ(account.id(), 1);
    EXPECT_EQ(account.GetBalance(), 100);
}

TEST(AccountTest, ChangeBalance) {
    MockAccount account(1, 100);
    account.Lock();
    account.ChangeBalance(50);
    EXPECT_EQ(account.GetBalance(), 150);
}
