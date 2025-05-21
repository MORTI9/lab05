#include "mocks/MockAccount.h"
#include "mocks/MockTransaction.h"
#include <gtest/gtest.h>

using ::testing::_;
using ::testing::Return;
using ::testing::Throw;

TEST(TransactionTest, MakeInvalidAccounts) {
    MockAccount from(1, 100);
    MockAccount to(1, 50);
    Transaction transaction;
    
    EXPECT_THROW(transaction.Make(from, to, 100), std::logic_error);
}

TEST(TransactionTest, MakeInvalidSum) {
    MockAccount from(1, 100);
    MockAccount to(2, 50);
    Transaction transaction;
    
    EXPECT_THROW(transaction.Make(from, to, -100), std::invalid_argument);
    EXPECT_THROW(transaction.Make(from, to, 50), std::logic_error);
}

TEST(TransactionTest, MakeFeeTooHigh) {
    MockAccount from(1, 100);
    MockAccount to(2, 50);
    Transaction transaction;
    transaction.set_fee(60);
    
    EXPECT_FALSE(transaction.Make(from, to, 100));
}

TEST(TransactionTest, MakeSuccess) {
    MockAccount from(1, 200);
    MockAccount to(2, 50);
    Transaction transaction;
    
    // Ожидаем вызовы Lock/Unlock
    EXPECT_CALL(from, Lock()).Times(1);
    EXPECT_CALL(from, Unlock()).Times(1);
    EXPECT_CALL(to, Lock()).Times(1);
    EXPECT_CALL(to, Unlock()).Times(1);
    
    // Настраиваем mock-методы
    EXPECT_CALL(from, GetBalance())
        .WillOnce(Return(200))
        .WillOnce(Return(200));
    
    EXPECT_CALL(to, GetBalance())
        .WillOnce(Return(50))
        .WillOnce(Return(150));
    
    // Ожидаем изменения баланса
    EXPECT_CALL(from, ChangeBalance(-101)).Times(1);
    EXPECT_CALL(to, ChangeBalance(100)).Times(1);
    
    EXPECT_TRUE(transaction.Make(from, to, 100));
}

// Удалены тесты DebitFailure и Credit, так как они тестируют приватные методы
