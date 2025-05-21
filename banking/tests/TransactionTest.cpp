#include "mocks/MockAccount.h"
#include "Transaction.h"  // Добавлен include для Transaction
#include <gtest/gtest.h>

using ::testing::Return;
using ::testing::_;

TEST(TransactionTest, MakeSuccessScenario) {
    MockAccount from(1, 200);
    MockAccount to(2, 50);
    Transaction transaction;
    
    // Ожидания для from
    EXPECT_CALL(from, id()).WillRepeatedly(Return(1));
    EXPECT_CALL(from, Lock()).Times(1);
    EXPECT_CALL(from, GetBalance())
        .Times(2)
        .WillOnce(Return(200))
        .WillOnce(Return(200));
    EXPECT_CALL(from, ChangeBalance(-101)).Times(1);
    EXPECT_CALL(from, Unlock()).Times(1);
    
    // Ожидания для to
    EXPECT_CALL(to, id()).WillRepeatedly(Return(2));
    EXPECT_CALL(to, Lock()).Times(1);
    EXPECT_CALL(to, GetBalance())
        .Times(2)
        .WillOnce(Return(50))
        .WillOnce(Return(150));
    EXPECT_CALL(to, ChangeBalance(100)).Times(1);
    EXPECT_CALL(to, Unlock()).Times(1);
    
    EXPECT_TRUE(transaction.Make(from, to, 100));
}
