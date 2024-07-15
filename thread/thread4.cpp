//condition variable example
//create 10 threads and each one will run print_id function to show its thread index
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>

using namespace std;

class condVar {
    std::mutex mx;
    std::condition_variable cv;
    bool flag;
    int numOfThrads;
    std::vector<std::thread> threads;
    vector<int> resultforId;
public:
    condVar(int num): numOfThrads {num} {
        flag = false;
        resultforId.reserve(num);
    }

    void start_threads() {
        threads.reserve(numOfThrads);

        for (int i = 0; i < numOfThrads; ++i) {
            threads.emplace_back(&condVar::saveThreadId, this, i);
        }
    }

    void saveThreadId(int id)
    {
        unique_lock<mutex> lock(mx); // RAII mechaniscm for lock and unlock 
        cv.wait(lock, [this]{return flag;});
        resultforId.emplace_back(id);

    }

    void go() {
        std::unique_lock<std::mutex> lock(mx);
        flag = true; //condition variable is changed here
        cv.notify_all();
    }

    //wait for all thread finish its job
    void join_threads() {
        for (auto& th : threads) {
            if (th.joinable()) {
                th.join();
            }
        }
    }

    const std::vector<int>& get_results() const {
        return resultforId;
    }


};

// int main()
// {
//     condVar condition_variable(10);
//     condition_variable.start_threads();
//     condition_variable.go();
//     //all thread join
//     condition_variable.join_threads();
//     const auto result = condition_variable.get_results();

//     for(auto id: result) {
//         std::cout<<"thread id is = "<<id<<"\n";
//     }

//     return 0;
// }