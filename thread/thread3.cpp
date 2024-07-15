//std::atomic template class is used for ensuring thread safety mechanism
//without the need for explicit locks (such as mutexes).
//Atomic operations are crucial in multithreading environments 
//to avoid data races and ensure data consistency.
#include <iostream>
#include <thread>
#include <vector>
#include <atomic>

std::atomic<int> counter(0); // Atomic counter

void incrementCounter(int iterations) {
    for (int i = 0; i < iterations; ++i) {
        ++counter; // Atomic increment
    }
}

int main() {
    const int numThreads = 10;
    const int iterations = 1000;

    // Create a vector of threads
    //vectors hold all threads
    std::vector<std::thread> threads;

    // Start multiple threads to increment the counter
    for (int i = 0; i < numThreads; ++i) {
        threads.push_back(std::thread(incrementCounter, iterations));
    }

    // Join all threads
    for (auto& thread : threads) {
        thread.join();
    }

    // Print the final value of the counter
    std::cout << "Final counter value: " << counter << "\n";

    return 0;
}
