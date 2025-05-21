include "Transaction.h"

#include <cassert>
#include <iostream>
#include <stdexcept>

#include "Account.h"

namespace {
// RAII
struct Guard {
  Guard(Account& account) : account_(&account) { account_->Lock(); }

  ~Guard() { account_->Unlock(); }

 private:
  Account* account_;
};
}  // namespace

Transaction::Transaction() : fee_(1) {}

Transaction::~Transaction() {}

bool Transaction::Make(Account& from, Account& to, int sum) {
  if (from.id() == to.id()) throw std::logic_error("invalid action");

  if (sum < 0) throw std::invalid_argument("sum can't be negative");

  if (sum < 100) throw std::logic_error("too small");

  if (fee_ * 2 > sum) return false;

  Guard guard_from(from);
  Guard guard_to(to);

  Credit(to, sum);

  bool success = Debit(to, sum + fee_);
  if (!success) to.ChangeBalance(-sum);

  SaveToDataBase(from, to, sum);
  return success;
}

