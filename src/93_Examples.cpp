/* PDF 93
Example 3: Access rights in inheritance #

Explanation #
In this example, we figured out the different access rights available to classes
when inheriting a parent class using public , protected , and private
keywords.

Only in the case of the pubAccount class, can we access the publicly
available member of the base class in main .

For the priAccount and proAccount classes, we can access public and
protected members’ variables in derived classes, but not in main .

*/




class Account{
    public:
        int pub{0};
    protected:
        int prot{0};
    private:
        int pri{0};
};


class PubAccount : public Account{
    public:
        PubAccount(){
            pub + prot; // public + protected
        }

};

class ProtAccount: protected Account{
    public:
        ProtAccount(){
            pub + prot; // protected + protected
        }
};

class PriAccount: private Account{
    public:
        PriAccount(){
            pub + prot; //private + private
        }
};

int main()
{
    PubAccount pubAccount;
    ProtAccount proAccount;
    PriAccount priAccount;

    pubAccount.pub;
}