#include "mocks/MockAccount.h"
#include <gtest/gtest.h>

TEST(AccountTest, Initialization) {
    Account account(1, 100);
    EXPECT_EQ(account.id(), 1);
    EXPECT_EQ(account.GetBalance(), 100);
    
    // Вместо проверки is_locked_ проверяем через публичные методы
    account.Lock();
    account.Unlock(); // Если не выбросилось исключение, значит изначально не было locked
}

TEST(AccountTest, LockUnlock) {
    Account account(1, 100);
    
    // Проверяем Lock через отсутствие исключения при первом вызове
    EXPECT_NO_THROW(account.Lock());
    
    // Проверяем повторный Lock
    EXPECT_THROW(account.Lock(), std::runtime_error);
    
    // Разблокируем
    account.Unlock();
    
    // Снова можем заблокировать
    EXPECT_NO_THROW(account.Lock());
}

TEST(AccountTest, ChangeBalance) {
    Account account(1, 100);
    
    // Нельзя изменить баланс без блокировки
    EXPECT_THROW(account.ChangeBalance(10), std::runtime_error);
    
    // Блокируем и меняем баланс
    account.Lock();
    account.ChangeBalance(50);
    EXPECT_EQ(account.GetBalance(), 150);
    
    // Уменьшаем баланс
    account.ChangeBalance(-70);
    EXPECT_EQ(account.GetBalance(), 80);
    
    // Разблокируем и проверяем, что нельзя изменить
    account.Unlock();
    EXPECT_THROW(account.ChangeBalance(10), std::runtime_error);
}
