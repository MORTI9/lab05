#include "mocks/MockAccount.h"
#include "mocks/MockTransaction.h"
#include <gtest/gtest.h>

using ::testing::_;
using ::testing::Return;
using ::testing::Throw;
using ::testing::NiceMock;

// Класс для тестирования protected методов
class TestableTransaction : public Transaction {
public:
    using Transaction::Credit;
    using Transaction::Debit;
    using Transaction::SaveToDataBase;
};

TEST(TransactionTest, MakeThrowsWhenAccountsSame) {
    NiceMock<MockAccount> from(1, 100);
    NiceMock<MockAccount> to(1, 50);
    Transaction transaction;

    EXPECT_THROW(transaction.Make(from, to, 100), std::logic_error);
}

TEST(TransactionTest, MakeThrowsWhenSumNegative) {
    NiceMock<MockAccount> from(1, 100);
    NiceMock<MockAccount> to(2, 50);
    Transaction transaction;

    EXPECT_THROW(transaction.Make(from, to, -100), std::invalid_argument);
}

TEST(TransactionTest, MakeThrowsWhenSumTooSmall) {
    NiceMock<MockAccount> from(1, 100);
    NiceMock<MockAccount> to(2, 50);
    Transaction transaction;

    EXPECT_THROW(transaction.Make(from, to, 50), std::logic_error);
}

TEST(TransactionTest, MakeReturnsFalseWhenFeeTooHigh) {
    NiceMock<MockAccount> from(1, 100);
    NiceMock<MockAccount> to(2, 50);
    Transaction transaction;
    transaction.set_fee(60);

    EXPECT_FALSE(transaction.Make(from, to, 100));
}

TEST(TransactionTest, MakeSuccessScenario) {
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

TEST(TransactionTest, CreditAddsToBalance) {
    TestableTransaction transaction;
    MockAccount account(1, 100);

    EXPECT_CALL(account, ChangeBalance(50)).Times(1);
    transaction.Credit(account, 50);
}

TEST(TransactionTest, DebitSuccessWhenEnoughBalance) {
    TestableTransaction transaction;
    MockAccount account(1, 100);

    EXPECT_CALL(account, GetBalance()).WillOnce(Return(100));
    EXPECT_CALL(account, ChangeBalance(-50)).Times(1);
    EXPECT_TRUE(transaction.Debit(account, 50));
}

TEST(TransactionTest, DebitFailsWhenNotEnoughBalance) {
    TestableTransaction transaction;
    MockAccount account(1, 50);

    EXPECT_CALL(account, GetBalance()).WillOnce(Return(50));
    EXPECT_FALSE(transaction.Debit(account, 100));
}

TEST(TransactionTest, SaveToDatabaseOutputsCorrectInfo) {
    TestableTransaction transaction;
    MockAccount from(1, 200);
    MockAccount to(2, 50);

    EXPECT_CALL(from, GetBalance()).WillOnce(Return(100));
    EXPECT_CALL(to, GetBalance()).WillOnce(Return(150));

    testing::internal::CaptureStdout();
    transaction.SaveToDataBase(from, to, 100);
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_TRUE(output.find("1 send to 2 $100") != std::string::npos);
    EXPECT_TRUE(output.find("Balance 1 is 100") != std::string::npos);
    EXPECT_TRUE(output.find("Balance 2 is 150") != std::string::npos);
}
}
