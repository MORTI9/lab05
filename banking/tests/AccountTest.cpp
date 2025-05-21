#include "mocks/MockAccount.h"
#include <gtest/gtest.h>

using ::testing::Return;
using ::testing::_;

TEST(AccountTest, Initialization) {
    MockAccount account(1, 100);
    
    // Устанавливаем ожидания для mock-методов
    EXPECT_CALL(account, GetBalance())
        .WillOnce(Return(100));
    
    EXPECT_EQ(account.id(), 1);
    EXPECT_EQ(account.GetBalance(), 100);
}

TEST(AccountTest, ChangeBalance) {
    MockAccount account(1, 100);
    
    // Последовательность ожидаемых вызовов
    ::testing::InSequence seq;
    EXPECT_CALL(account, Lock());
    EXPECT_CALL(account, ChangeBalance(50));
    EXPECT_CALL(account, GetBalance())
        .WillOnce(Return(150));
    EXPECT_CALL(account, Unlock());
    
    account.Lock();
    account.ChangeBalance(50);
    EXPECT_EQ(account.GetBalance(), 150);
    account.Unlock();
}
