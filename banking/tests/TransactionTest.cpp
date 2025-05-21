#include "mocks/MockAccount.h"
#include "mocks/MockTransaction.h"
#include <gtest/gtest.h>

using ::testing::_;
using ::testing::Return;
using ::testing::NiceMock;

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

    EXPECT_CALL(from, Lock()).Times(1);
    EXPECT_CALL(from, Unlock()).Times(1);
    EXPECT_CALL(to, Lock()).Times(1);
    EXPECT_CALL(to, Unlock()).Times(1);

    EXPECT_CALL(from, GetBalance())
        .WillOnce(Return(200))
        .WillOnce(Return(200));
    
    EXPECT_CALL(to, GetBalance())
        .WillOnce(Return(50))
        .WillOnce(Return(150));

    EXPECT_CALL(from, ChangeBalance(-101)).Times(1);
    EXPECT_CALL(to, ChangeBalance(100)).Times(1);

    EXPECT_TRUE(transaction.Make(from, to, 100));
}

TEST(TransactionTest, CreditTest) {
    TestableTransaction transaction;
    MockAccount account(1, 100);

    EXPECT_CALL(account, ChangeBalance(50)).Times(1);
    transaction.Credit(account, 50);
}

TEST(TransactionTest, DebitTest) {
    TestableTransaction transaction;
    MockAccount account(1, 100);

    EXPECT_CALL(account, GetBalance()).WillOnce(Return(100));
    EXPECT_CALL
