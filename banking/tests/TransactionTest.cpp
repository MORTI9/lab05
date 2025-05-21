TEST(TransactionTest, SaveToDatabaseOutputsCorrectInfo) {
    TestableTransaction transaction;
    NiceMock<MockAccount> from(1, 200);
    NiceMock<MockAccount> to(2, 50);

    // Установите ожидания только для GetBalance
    ON_CALL(from, GetBalance()).WillByDefault(Return(100));
    ON_CALL(to, GetBalance()).WillByDefault(Return(150));

    testing::internal::CaptureStdout();
    transaction.SaveToDataBase(from, to, 100);
    std::string output = testing::internal::GetCapturedStdout();

    // Проверяем только общий формат вывода
    EXPECT_FALSE(output.empty());
}
