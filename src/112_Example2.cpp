/* PDF 110
Example 2: Virtual multiple inheritance #

Explanation #

In the example above, we have created all the classes in the same way as
in example 1.

The only thing that we have changed is virtually inheriting the Account
class in the BankAccount and WireAccount classes.

By inheriting these classes virtually, we can now access the
checkAccount.getBalance() method of the Account class.



*/



#include<iostream>

class Account{
    public:
        Account(double amt):amount(amt){}

        double getBalance() const{
            return amount;            
        }

    private:
        double amount;

};

class BankAccount: virtual public Account{
    public:
        BankAccount(double amt): Account(amt){}
};

class WireAccount: virtual public Account{
        public:
            WireAccount(double amt): Account(amt){}
};

class CheckingAccount:  public BankAccount,  public WireAccount
{
    public:
        CheckingAccount(double amt): BankAccount(amt) , WireAccount(amt), Account(amt){} //! Account(amt) is added also
};


int main()
{
    CheckingAccount checkingAccount(100.0);
    std::cout<<checkingAccount.getBalance()<<"\n";
    
    std::cout<<checkingAccount.BankAccount::getBalance()<<"\n";
    std::cout<<checkingAccount.WireAccount::getBalance()<<"\n";
}