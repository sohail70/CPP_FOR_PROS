/* PDF 74
constexpr methods #

Explanation #
The constexpr constructor, and the methods getAccountFees and
getAmount will be evaluated at compile time.

Since constexpr methods are implicitly const , we mention the const
keyword in the definitions as well.

Line 21 shows how the returned value of getAmount() can be stored in a
constexpr double .

As we can see in line 27, constexpr methods can also be called by non-
constexpr objects.

*/

#include<iostream>

class Account{
public:
    constexpr Account(int amou): amount(amou){}

    constexpr double getAmount() const{
        return amount;
    }
    constexpr double getAccountFees() const
    {
        return 0.5*getAmount();
    }

private:
    double amount;
};



int main()
{
    constexpr Account accConst(15);
    constexpr double amouConst = accConst.getAmount();
    std::cout<<amouConst<<"\n";
    std::cout<<accConst.getAccountFees()<<"\n";
    static_assert(amouConst==15);
    
    Account accDyn(15);
    double amouDyn = accDyn.getAmount();
    //static_assert(amouDyn==15);
    std::cout<<amouDyn<<"\n";
    std::cout<<accDyn.getAccountFees()<<"\n";
}