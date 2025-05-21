#include "mocks/MockAccount.h"
#include <gtest/gtest.h>

TEST(AccountTest, Initialization) {
    Account account(1, 100);
    EXPECT_EQ(account.id(), 1);
    EXPECT_EQ(account.GetBalance(), 100);
    EXPECT_FALSE(account.is_locked_);
}

TEST(AccountTest, LockUnlock) {
    Account account(1, 100);
    
    account.Lock();
    EXPECT_TRUE(account.is_locked_);
    
    EXPECT_THROW(account.Lock(), std::runtime_error);
    
    account.Unlock();
    EXPECT_FALSE(account.is_locked_);
}

TEST(AccountTest, ChangeBalance) {
    Account account(1, 100);
    
    EXPECT_THROW(account.ChangeBalance(10), std::runtime_error);
    
    account.Lock();
    account.ChangeBalance(50);
    EXPECT_EQ(account.GetBalance(), 150);
    
    account.ChangeBalance(-70);
    EXPECT_EQ(account.GetBalance(), 80);
    
    account.Unlock();
    EXPECT_THROW(account.ChangeBalance(10), std::runtime_error);
}
