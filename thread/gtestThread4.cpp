#include <gtest/gtest.h>
#include "thread4.cpp"
#include <algorithm>

using namespace std;


TEST(ConditionVariableTest, TestThreadExecutionOrder) {
    condVar coordinator(10);
    coordinator.start_threads();
    coordinator.go();
    coordinator.join_threads();
    const auto& results = coordinator.get_results();

    ASSERT_EQ(results.size(), 10);

    // Check if all thread ids are present
    std::vector<int> expected_ids{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::vector<int> sorted_results = results;
    std::sort(sorted_results.begin(), sorted_results.end());
    ASSERT_EQ(sorted_results, expected_ids);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}