#include "mocks/MockAccount.h"
#include <gtest/gtest.h>

using ::testing::Return;
using ::testing::_;

TEST(AccountTest, Initialization) {
    MockAccount account(1, 100);
    
    EXPECT_CALL(account, id()).WillOnce(Return(1));
    EXPECT_CALL(account, GetBalance()).WillOnce(Return(100));
    
    EXPECT_EQ(account.id(), 1);
    EXPECT_EQ(account.GetBalance(), 100);
}

TEST(AccountTest, ChangeBalance) {
    MockAccount account(1, 100);
    
    // Устанавливаем ожидания в правильном порядке
    EXPECT_CALL(account, id()).WillOnce(Return(1));
    EXPECT_CALL(account, Lock()).Times(1);
    EXPECT_CALL(account, ChangeBalance(50)).Times(1);
    EXPECT_CALL(account, GetBalance()).WillOnce(Return(150));
    EXPECT_CALL(account, Unlock()).Times(1);
    
    account.Lock();
    account.ChangeBalance(50);
    EXPECT_EQ(account.GetBalance(), 150);
    account.Unlock();
}
