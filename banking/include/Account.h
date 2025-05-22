#pragma once
class Account {
public:
    Account(int id, int balance);
    virtual ~Account();

    virtual int GetBalance() const;
    virtual void ChangeBalance(int diff);
    virtual void Lock();
    virtual void Unlock();
    
    // Делаем метод невиртуальным, так как он не должен переопределяться
    int id() const { return id_; }

protected:  // Делаем поля доступными для наследников
    int id_;
    int balance_;
    bool is_locked_;
};
