#include<iostream>
#include<memory>

class A{
    public:
        A(double aa):a(aa){};
        void set_a(double aa) 
        {
            a = aa;   
        }

        double get_a() 
        {
            return a; 
        }

    private:
        double a;
};  



void func(A* pointer_to_a)
{
    pointer_to_a->set_a(10);
}



int main()
{
    auto shared = std::make_shared<A>(3.0);
    func(shared.get());
    std::cout<<shared.use_count()<<"\n";
    std::cout<<shared->get_a()<<"\n";
}