#include "mocks/MockAccount.h"
#include "Transaction.h"
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
        .WillOnce(Return(200))
        .WillOnce(Return(200));
    EXPECT_CALL(from, ChangeBalance(_)).Times(1);  // Исправленный вызов
    EXPECT_CALL(from, Unlock()).Times(1);
    
    // Ожидания для to
    EXPECT_CALL(to, id()).WillRepeatedly(Return(2));
    EXPECT_CALL(to, Lock()).Times(1);
    EXPECT_CALL(to, GetBalance())
        .WillOnce(Return(50));
    EXPECT_CALL(to, ChangeBalance(_)).Times(1);  // Исправленный вызов
    EXPECT_CALL(to, Unlock()).Times(1);
    
    EXPECT_TRUE(transaction.Make(from, to, 100));
}
