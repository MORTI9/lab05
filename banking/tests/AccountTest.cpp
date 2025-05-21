#include "mocks/MockAccount.h"
#include <gtest/gtest.h>

TEST(AccountTest, Initialization) {
    MockAccount account(1, 100);
    EXPECT_EQ(account.id(), 1);
    EXPECT_EQ(account.GetBalance(), 100);
}

TEST(AccountTest, LockUnlock) {
    MockAccount account(1, 100);
    
    EXPECT_NO_THROW(account.Lock());
    EXPECT_THROW(account.Lock(), std::runtime_error);
    account.Unlock();
    EXPECT_NO_THROW(account.Lock());
}

TEST(AccountTest, ChangeBalance) {
    MockAccount account(1, 100);
    
    EXPECT_THROW(account.ChangeBalance(10), std::runtime_error);
    account.Lock();
    account.ChangeBalance(50);
    EXPECT_EQ(account.GetBalance(), 150);
    account.Unlock();
}
