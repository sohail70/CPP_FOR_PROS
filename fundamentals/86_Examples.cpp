/* PDF 88
Examples
Access rights for class members #

Explanation #
In lines 42 – 45, we have initialized an object of Account class, deposited
the amount 75.15 in the account, and withdrew 30.

We have called the getBalance() method in line 47, which returns the
balance left in the account. Note that this method is declared public .

By using the scope operator :: , we can access the variable publicly
declared in the class in line 48.
*/

#include<iostream>

class Account{
public:
    Account(double b): balance(b){
        ++Account::transactions;
    }

    void deposits(double amt)
    {
        balance = calcBalance(amt);
    }

    void withdraw(double amt)
    {
        balance = calcBalance(-amt);
    }

    double getBalance() const{
        return balance;
    }

    static int transactions;
private:
    double calcBalance(double amt)
    {
        ++Account::transactions;
        return balance +=amt;
    }
    double balance;
};
int Account::transactions = 0;



int main()
{
    Account acc(100.0);
    acc.deposits(50.0);
    acc.deposits(25.15);
    acc.withdraw(30);

    std::cout<<acc.getBalance()<<"\n";
    std::cout<<Account::transactions<<"\n";
}