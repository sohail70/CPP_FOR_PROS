/*
Raw string literals suppress the interpretation of a string
Raw string literals act as import helpers for path expressions and regular


*/
#include <iostream>
#include <string>
int main()
{
    
    std::string nat = "C:\temp\newFile.txt";
    std::cout << nat << std::endl;
    
    // including \t \n
    std::string raw1 = std::string(R"(C:\temp\newFile.txt)");
    std::cout << "\n" << raw1 << std::endl;
    
    // including \t \n and using delimiter
    std::string raw2 = std::string(R"TRENNER(C:\temp\newFile.txt)TRENNER");
    std::cout << "\n" << raw2 << std::endl;

    // raw string including "
    std::string raw3 = std::string(R"(a raw string including ")");
    std::cout << "\n" << raw3 << std::endl;
    std::cout << std::endl;
}