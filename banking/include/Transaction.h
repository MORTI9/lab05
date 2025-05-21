#pragma once

class Account;

class Transaction {
 public:
  Transaction();
  virtual ~Transaction();

  bool Make(Account& from, Account& to, int sum);
  int fee() const { return fee_; }
  void set_fee(int fee) { fee_ = fee; }

 protected:  // Изменили с private на protected для тестирования
  virtual void Credit(Account& account, int sum);
  virtual bool Debit(Account& account, int sum);
  virtual void SaveToDataBase(Account& from, Account& to, int sum);

 private:
  int fee_;
};
