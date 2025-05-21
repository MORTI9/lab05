#include "mocks/MockAccount.h"
#include "mocks/MockTransaction.h"
#include <gtest/gtest.h>

using ::testing::Return;
using ::testing::_;
using ::testing::NiceMock;

TEST(TransactionTest, MakeSuccessScenario) {
    NiceMock<MockAccount> from(1, 200);
    NiceMock<MockAccount> to(2, 50);
    Transaction transaction;
    
    // Точные ожидания вызовов
    EXPECT_CALL(from, Lock()).Times(1);
    EXPECT_CALL(from, Unlock()).Times(1);
    EXPECT_CALL(to, Lock()).Times(1);
    EXPECT_CALL(to, Unlock()).Times(1);
    
    // Ожидаем ровно 2 вызова GetBalance для каждого аккаунта
    EXPECT_CALL(from, GetBalance())
        .Times(2)
        .WillRepeatedly(Return(200));
    EXPECT_CALL(to, GetBalance())
        .Times(2)
        .WillRepeatedly(Return(50));
    
    EXPECT_CALL(from, ChangeBalance(-101)).Times(1);
    EXPECT_CALL(to, ChangeBalance(100)).Times(1);
    
    EXPECT_TRUE(transaction.Make(from, to, 100));
}
