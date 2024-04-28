#include <iostream>
#include <vector>
#include <thread>
#include <mutex>

using namespace std;

class Singleton {

    static Singleton *instance;
    static std::mutex s_mtx; // for multiple thread prevent race conditions

    // constructor and destructor must be inside private area
    Singleton(){
        std::cout<<"singleton constructor...\n";
    }

    ~Singleton(){
        std::cout<<"singleton destructor...\n";
    }
    //copy constructor and copt assignment are deleted due to creating one instance
    Singleton(const Singleton &) = delete;
    Singleton& operator=(const Singleton &) = delete;
public:
    // this func must be static due to the fact that we want just one Singleton instance
    static Singleton *get_instance()
    {
        std::lock_guard<mutex> my_lock(s_mtx); // mutex wrapper
        
        if(instance == nullptr) {
            instance = new Singleton;
        }

        return instance;
    }

    static void instance_destroy() {
        std::lock_guard<mutex> my_lock(s_mtx); // mutex wrapper

        if(instance != nullptr) {
            delete instance;
            instance = nullptr;
        }
    }
};

Singleton * Singleton::instance = nullptr;
std::mutex Singleton::s_mtx;

int main()
 {
    auto p = Singleton::get_instance();

    std::vector<thread> my_threads;

    for(int i = 0; i < 50; i ++) {
        my_threads.emplace_back(thread([](){ Singleton::get_instance(); }));
    }

    for(auto &r: my_threads) {
        if(r.joinable()) {
            r.join();
        }
    }

    return 0;
 }