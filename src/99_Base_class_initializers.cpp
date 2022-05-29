/* PDF 99
Base Class Initializers

! The base class initializer specifies the data that are given to the base class.
! They are directly provided in the constructor.

Example #

class Account{
    public:
        Account(double amount, std::string cur){};
};

class BankAccount: public Account{
    public:
        BankAccount(double r , std::string cur): Account(r, cur){}
...

! When a base class has no default constructor, the derived class must explicitly
! call a constructor. The base class initializer is typically used with class
! initializers.

Example #

struct Account{
    Account(double amount){};
};

struct BankAccount: Account{
    BankAccount(double r): Account(r) , cur("EUR"){}
private:
    std::string cur;
...

*/