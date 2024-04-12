#include <iostream>
#include <stdexcept>

int func() noexcept(false) {
    try {
        throw std::runtime_error{"Error occurred"}; 
    }
    catch(...) {
        throw; // there is no specific throwing so that runtime_error exception will be catching below
    }
    return 1;
}

int func2() noexcept(false) {
    try {
        func();
    }
    catch(const std::runtime_error& re) {
        std::cout << "Error: " << re.what()<<"\n";
    }
    catch(...){
        std::cout << "Unknown reason...\n";
    }
    return 0;
}

int main(void)
{
    func2();
}