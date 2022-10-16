/* PDF 106
Example 2: Override #

Explanation #
When we compile the program, the compiler will complain a lot. The error
message is very specific.
The compiler complains in line 15 that the method func1 is not overriding a
method. The same holds true for func2 . It has the wrong parameter type.
Continuing with the method func3 , it complains that func3 has no const
qualifier. func4 has the wrong return type. Only the method f in line 27
correctly overrides the method f of its base class.
! final is the right tool for the job if a virtual method should not be
! overridden.

*/

class Base{
    void func1();
    virtual void func2(float);
    virtual void func3() const;
    virtual long func4(int);

    virtual void f();
};


class Derived: public Base{
    // ill-formed: no virtual method func1 exists
    virtual void func1() override;

    // ill-formed: bad type
    virtual void func2(double ) override;

    // ill-formed: const missing
    virtual void func3() override;

    // ill-formed: wrong return type
    virtual int func4(int) override;

    // well-formed: f override base::f
    virtual void f() override;
};

int main()
{
    Base base;
    Derived derived;
}