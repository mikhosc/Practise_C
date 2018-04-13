#include <iostream>
#include "Time.hpp"

int main(int argc, const char * argv[])
{
    TIME a("Name_a", 1, 2, 3);
    TIME d("Name_d", 10, 0, 7);
    std::cout << a<<'\n';
    TIME b("NAME_b");
    std::cout<<b<<'\n';
    std::cout<<b+d+a+b<<'\n';
    b = a+d;
    std::cout<<b<<'\n';
    TIME f(a);
    std::cout<<b<<'\n';
    
    std::cout<<"----------------"<<std::endl;
    TIME c;
    std::cin >> c;
    std::cout << c<<'\n';
    
    if (c > a)
        std::cout<< c <<" greater than "<<a<<'\n';
    
    if (a == a)
        std::cout<< a <<" equal to "<<a<<'\n';
    
    return 0;
}
