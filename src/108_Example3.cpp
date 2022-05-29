/* PDF 106

Example 3: final #
The given function causes a compilation error because the base method
is declared final .

Explanation #
The compiler performs its job neatly. It complains that the method h in the
class Base (line 2) is overridden by the method in class Derived (line 10). Of
course, it’s okay that the method h (line 13) in class Derived overloads f for
the parameter type double . This method g (line 15) in the class Derived is
quite interesting. The method overrides the method g (line 4) of the class
Base and declares the method final . Therefore, g cannot be overridden in
DerivedDerived (line 19).
! DerivedClass cannot be derived from FinalClass , because the BaseClass is
! final .
*/

class Base{
    virtual void h(int) final;

    virtual void g(long int);
};


class Derived: public Base{

    // ill-formed: base method declared final
    virtual void h(int);

    // well-formed: a new virtual function
    virtual void h(double);

    virtual void g(long int ) final;
};

class DerivedDerived: public Derived{
    virtual void g(long int);
};

struct FinalClass final{};
struct DerivedClass: FinalClass{};

int main()
{
    Base base;
    Derived derived;
    DerivedDerived derivedDerived;

    FinalClass finalClass;
    DerivedClass derivedClass;
}