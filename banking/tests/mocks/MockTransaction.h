#pragma once
#include "Transaction.h"
#include <gmock/gmock.h>

class MockTransaction : public Transaction {
public:
    MockTransaction() : Transaction() {}
    
    MOCK_METHOD(void, SaveToDataBase, (Account& from, Account& to, int sum), (override));
};
