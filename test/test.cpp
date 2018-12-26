#include<iostream>
#include <string>
int main(){
    std::string x = "";

    for(int i = 0; i < 1; ++i)
        std::getline(std::cin, x);
    
    for(int i = 0; i < 1; ++i)
        std::cout << x << std::endl;

    return 0;
}
