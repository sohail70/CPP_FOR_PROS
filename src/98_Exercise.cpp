/* PDF 97
Exercise #
Inherit public , protected , and private identifiers from a class using
constructor inheritance. The constructors inherited from the base class keep
their access level. The inherited class restricts them.
What does that mean for the inherited constructors?



*/


class Base{
    public:
        Base(int){};
};
class DerivePublic: public Base{
    using Base::Base;
};
class DeriveProtected: protected Base{
    using Base::Base;
};
class DerivePrivate: private Base{
    using Base::Base;
};
int main(){
    Base(1);
    DerivePublic(1);
    DeriveProtected(1);
    DerivePrivate(1);
}