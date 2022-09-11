/* PDF 168
In this lesson, we will discuss the rules regarding passing smart pointers.

WE'LL COVER THE FOLLOWING
• The Six Rules
• R.32
• R.33
• R.34, R.35, and R.36
• R.37
• Further information


! Passing smart pointers is an important topic that is seldom addressed. This
! chapter ends with the C++ core guidelines since they have six rules for passing
! std::shared_ptr and std::unique_ptr .

The Six Rules #

The following six rules violate the important DRY (don’t repeat yourself)
principle for software development. In the end, we only have six rules, which
makes life as a software developer a lot easier. Here are the rules:


! 1. R.32: Take a unique_ptr<widget> parameter to express that a function
! assumes ownership of a widget.

! 2. R.33: Take a unique_ptr<widget>& parameter to express that a function
! reseats the widget.

! 3. R.34: Take a shared_ptr<widget> parameter to express that a function is
! part owner.

! 4. R.35: Take a shared_ptr<widget>& parameter to express that a function
! might reseat the shared pointer.

! 5. R.36: Take a const shared_ptr<widget>& parameter to express that it mightretain a reference count to the object.

! 6. R.37: Do not pass a pointer or reference obtained from an aliased smart
! pointer.



R.32 #
If a function should take ownership of a Widget, take the
std::unique_ptr<Widget> by copy. The consequence is that the caller has to
move the std::unique_ptr<Widget> to make the code run.

#include<memory>
#include<utility>

struct Widget{
    Widget(int){}
};

void sink(std::unique_ptr<Widget> uniqPtr){
    // do sth with uniqPtr
}

int main()
{
    auto uniqPtr = std::make_unique<Widget>(1998);

    sink(std::move(uniqPtr)); //(1)
    sink(uniqPtr);            //(2) ERROR
}


! The call in line 15 is fine but the call line 16 breaks because we cannot copy an
! std::unique_ptr . If the function only wants to use the Widget , it should take
! its parameter by pointer or by reference. A pointer can be a null pointer, but a
! reference cannot.
void useWidget(Widget* wid);
void useWidget(Widget& wid);


R.33 #
! Sometimes a function wants to reseat a Widget . In this case, pass thestd::unique_ptr<Widget> by a non-const reference.

#include<memory>
#include<utility>

struct Widget{
    Widget(int){}
};

void reseat(std::unique_ptr<Widget>& uniqPtr){
    uniqPtr.reset(new Widget{2003}); // (0)
    // do sth with uniqPtr
}


int main()
{
    auto uniqPtr = std::make_unique<Widget>(1998);

    reseat(std::move(uniqPtr));     //(1) Error
    reseat(uniqPtr);                //(2)
}


! Now, the call in line 16 fails because we cannot bind an rvalue to a non-const
! lvalue reference. This will not hold for the copy in line 17. An lvalue can be
! bound to an lvalue reference. The call in line 9 will not only construct a new
! Widget(2003) , but it will also destruct the old Widget(1998) .
! The next three rules of std::shared_ptr repeat each other, so we will only
! discuss one.

R.34, R.35, and R.36 #

Here are the three function signatures that we have to address.

void share(std::shared_ptr<Widget> shaWid);
void reseat(std::shard_ptr<Widget>& shadWid);
void mayShare(const std::shared_ptr<Widget>& shaWid);

We will take a look at each function signature in isolation, but what does this
mean from the function perspective? Let’s find out!

! void share(std::shared_ptr shaWid):For the lifetime of the function
! body, this method is a shared owner of the Widget . At the start of the
! function body, we will increase the reference counter; at the end of thefunction, we will decrease the reference counter; therefore, the Widget
! will stay alive, as long as we use it.

! void reseat(std::shared_ptr& shaWid): This function isn’t a shared
! owner of the Widget because we will not change the reference counter.
! We have not guaranteed that the Widget will stay alive during the
! execution of the function, but we can reseat the resource. A non-const
! lvalue reference is more like borrowing the resource with the ability to
! reseat it.

! void mayShare(const std::shared_ptr& shaWid): This function only
! borrows the resource. Neither can we extend the lifetime of the resource
! nor can we reseat the resource. To be honest, we should use a pointer
! ( Widget* ) or a reference ( Widget& ) as a parameter instead, because there
! is no added value in using an std::shared_ptr .

void oldFunc(Widget* wid){
    // do sth wit wid
}

void shared(std::shared_ptr<Widget>& shaPtr){ // (2)

        oldFunc(*shaPtr);                     // (3)

        // do sth hwith shaPtr
}

auto globalShared = std::make_shared<Widget>(2011) // (1)

....

shared(globShared);



! In line 13, globShared is a globally shared pointer. The function shared takes
! its argument by reference in line 5. Therefore, the reference counter of
! shaPtr will not be increased and the function shared will not extend the
! lifetime of Widget(2011) . The issue begins on line 7. oldFunc accepts a pointer
! to the Widget ; therefore, oldFunc has no guarantee that the Widget will stay
! alive during its execution. oldFunc only borrows the Widget .The solution is quite simple. We must ensure that the reference count of
! globShared is increased before the call to the function oldFunc , meaning that
! we must make a copy of std::shared_ptr :

! method1) Pass the std::shared_ptr by copy to the function shared :

void shared(std::shred_ptr<Widget> shaPtr){
    oldFunc(*shaPtr);
    // do sth with shaPtr
}

! method2) Make a copy of the shaPtr in the function shared :

void shared(std::shared_ptr<Widget>& shaPtr){
    auto keepAlive = shaPtr;
    oldFunc(*shaPtr);
    // do sth with keepAlive or shaPtr
}

! The same reasoning also applies to std::unique_ptr , but there isn’t a simple
! solution since we cannot copy an std::unique_ptr . Rather, we can clone the
! std::unique_ptr and make a new std::unique_ptr .



*/