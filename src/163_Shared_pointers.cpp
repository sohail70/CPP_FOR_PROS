/* PDF 159
Next, we will go over shared pointers, which follow the principle of keeping a reference count to maintain the
count of its copies. The lesson below elaborates further.

WE'LL COVER THE FOLLOWING
• Introduction
• Methods
    • std::make_shared
    • std::shared_ptr from this
• Further information

Introduction #

! std::shared_ptr shares ownership of the resource. They have two handles: one
! for the resource, and one for the reference counter. By copying an
! std::shared_ptr , the reference count is increased by one. It is decreased by
! one if the std::shared_ptr goes out of scope. If the reference counter becomes
! the value 0, the C++ runtime automatically releases the resource, since there is
! no longer an std::shared_ptr referencing the resource. The release of the
! resource occurs exactly when the last std::shared_ptr goes out of scope. The
! C++ runtime guarantees that the call of the reference counter is an atomic
! operation. Due to this management, std::shared_ptr consumes more time
! and memory than a raw pointer or std::unique_ptr .
! Take a look at the image below to better visualize the concept---> pdf 159--> std::shared_ptr<int> shared2(shared1);
! Due to shared1 , shared2 is initialized. In the end, the reference count is 2 and
! both smart pointers have the same resource.



Methods #
! get --> Returns a pointer to the resource.
! get_deleter --> Returns the delete function.
! reset --> Resets the resource.
! swap -->Swaps the resources.
! unique --> Checks if the std::shared_ptr is the exclusive owner of the resource.
! use_count --> Returns the value of the reference counter.


std::make_shared #
! The helper function std::make_shared creates the resource and returns it in
! an std::shared_ptr . Use std::make_shared rather than directly creating an
! std::shared_ptr because std::make_shared is much faster. Additionally, such
! as in the case of std::make_unique , std::make_shared guarantees no memory
! leaks.

std::shared_ptr from this #
This unique technique, in which a class derives from a class template
having itself as a parameter, is called CRTP and stands for Curiously
Recurring Template Pattern.

Using the class std::enable_shared_from_this, we can create objects that return
an std::shared_ptr to themselves. To do so, we must publicly derive the class
from std::enable_shared_from_this . So the class ShareMe support the method
shared_from_this , and return std::shared_ptr :

// enableShared.cpp
#include <iostream>
#include <memory>
class ShareMe: public std::enable_shared_from_this<ShareMe>{
    public:
    std::shared_ptr<ShareMe> getShared(){
    return shared_from_this();
}
};
int main(){
    std::cout << std::endl;
    std::shared_ptr<ShareMe> shareMe(new ShareMe);
    std::shared_ptr<ShareMe> shareMe1= shareMe->getShared();
    {
    auto shareMe2(shareMe1);
    std::cout << "shareMe.use_count(): " << shareMe.use_count() << std::endl;}
    std::cout << "shareMe.use_count(): "
    << shareMe.use_count() << std::endl;
    shareMe1.reset();
    std::cout << "shareMe.use_count(): "
    << shareMe.use_count() << std::endl;
    std::cout << std::endl;
}


The smart pointer shareMe (line 17) is copied by shareMe1 (line 18) and
shareMe2 (line 20), and all of them
    reference the very same resource.
    increment and decrement the reference counter.
The call shareMe->getShared() in line 18 creates a new smart pointer.
getShared() (line 9) internally uses the function shared_from_this


from the internet:
see https://stackoverflow.com/questions/712279/what-is-the-usefulness-of-enable-shared-from-this
return shared_ptr<Y>(this); --> this is wrong ---> //! The shared pointer that this returned will have a different reference count from the "proper" one, and one of them will end up losing and holding a dangling reference when the object is deleted.

*/


#include<iostream>
#include<memory>

class ShareMe: public std::enable_shared_from_this<ShareMe> {
    public:
        std::shared_ptr<ShareMe> getShared()
        {
            return shared_from_this();
        }
};

int main()
{
    std::shared_ptr<ShareMe> shareMe{new ShareMe};
    std::shared_ptr<ShareMe> shareMe1 = shareMe->getShared();
    {
        auto shareMe2(shareMe1);
        std::cout<<"shareMe.use)count(): " <<shareMe.use_count()<<"\n";
    }

    std::cout<<"shareMe.use_count(): "<<shareMe.use_count()<<"\n";
    shareMe1.reset();

    std::cout<<"shareMe.use_count(): "<< shareMe.use_count()<<"\n";
}