#include <iostream>
#include <memory>

using namespace std;

template<typename T>
class my_smart_ptr {
 T *m_ptr;
public:
    my_smart_ptr(): m_ptr{nullptr} {
        cout<<"my_smart_ptr default c.tor is called...\n";
    }

    my_smart_ptr(T *ptr): m_ptr{ptr} 
    {
        cout<< "my_smart_ptr c.tor with ptr parameters "<< *m_ptr<<"\n";
    }
    //for exclusive ownership we need to delete copy c.tor and copy assignment operator
    my_smart_ptr(const my_smart_ptr& my_obj) = delete;
    my_smart_ptr& operator=(const my_smart_ptr& my_obj) = delete;

    my_smart_ptr(my_smart_ptr&& my_obj) //move c.tor
    {
        //transferring the ownership
        this->m_ptr = my_obj.m_ptr;
        my_obj.m_ptr = nullptr;

    }

    my_smart_ptr& operator=(my_smart_ptr&& my_obj) //move assignment
    {
        std::cout<<"my_smart_ptr calling the move assignment...\n";
        if(this->m_ptr != nullptr)
            delete this->m_ptr;
        //same behavior with move c.tor. transferring the ownership
        this->m_ptr = my_obj.m_ptr;
        my_obj.m_ptr = nullptr;

        return *this;
    }

    ~my_smart_ptr() {
        cout<<"~my_smart_ptr() is called...\n";
        if(this->m_ptr != nullptr)
            delete this->m_ptr;
    }

    T* operator->() 
    {
        return this->m_ptr;
    }

    T& operator*()
    {
        return *(this->m_ptr);
    }
};

class Myclass {
    int x;

public:
    Myclass() = default;
    Myclass(int a): x{a} 
    {
        std::cout<<"Myclass(int) x = "<< x<<"\n";
    }

    ~Myclass()
    {
        cout<<"~Myclass() is called..\n";
    }

    //this need for print Myclass parameter with operator<<
    friend std::ostream& operator<<(ostream& os,const Myclass &m)
    {
        return os<< m.x <<"\n";
    }
};

int main() {
    //create a smart pt for Myclass
    my_smart_ptr<Myclass> my_ptr1 = new Myclass{22};
    //my_smart_ptr<Myclass> my_ptr2 = std::move(my_ptr1);
    //my_smart_ptr<int> my_ptr3 {new int (25)};
    return 0;
}