/*-PDF 74
Constant methods #

Explanation #

The const method, readAccount is defined on line 23. It simply returns
the value of balance .

The readWriteAccount object on line 19 allows balance attribute to be
modified through class methods. We can see an example of this on line
20.

The const object, readAccount , can only invoke the const readAccount
method. Using addAmount with it will throw an error. This is because
const objects can only call other const methods.


*/


#include<iostream>

class Account
{
public:
    double getBalance() const
    {
        return balance;
    }
    void addAmount(double amount)
    {
        balance+=amount;
    }
private:
    double balance{0.0};
};

int main()
{
    Account readWriteAccount;
    readWriteAccount.addAmount(50.0);
    std::cout<<readWriteAccount.getBalance()<<"\n";

    const Account readAccount;
    std::cout<<readAccount.getBalance()<<"\n";
}