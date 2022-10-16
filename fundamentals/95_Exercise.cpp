/* PDF 94
A class hierarchy is constructed to represent a set of hierarchically organized
concepts (only). Typically, base classes act as interfaces. There are two major
uses for hierarchies, often named implementation inheritance and interface
inheritance.

Read the class hierarchy rules in the given links:
! SOME VERY GOOD LINKS IN THE PDF. CHECK IT OUT.
! The explnation in core c++ guidlines may be hard so you can use this website : https://www.modernescpp.com/index.php/c-core-guidelines-class-hierarchies which explains the core guidlines better.

! Another good explanation: https://www.quantstart.com/articles/C-Virtual-Destructors-How-to-Avoid-Memory-Leaks/

! Best example is this: https://ladydebug.com/blog/2020/11/23/valgrind-testing-of-non-virtual-destructor/
*/

#include<iostream>
#include<string>
#include<memory>

class Goof{
    public:
        virtual void printName() const  = 0  ;
        ~Goof()  //! delete the virtual word and see the leak- derived destructor won't be called so string s destructor can't be called //but valrgind can't catch that - maybe its just undefined beahvior--> check: https://stackoverflow.com/questions/56792856/why-absence-of-a-virtual-destructor-doesnt-cause-a-memory-leak BUT ITHINK THIS IS A BETTER EXAMPLE:https://ladydebug.com/blog/2020/11/23/valgrind-testing-of-non-virtual-destructor/
        
        {
            std::cout<<"GOOf DESt"<<"\n";
        }
};

class Derived: public Goof{
    public:
        Derived(std::string name): s(name){};
        void printName() const override {
            std::cout<<s<<"\n";
        }
        ~Derived(){
            std::cout<<"Dervided deset"<<"\n";
        }
    private:
        std::string s;
};

int main()
{
    
        Goof* p {new Derived{"Here we go"}};
        
        p->printName();
    delete p;

    
    std::cout<<"asdas"<<"\n";
}
