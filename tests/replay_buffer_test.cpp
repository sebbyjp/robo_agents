#include <gtest/gtest.h>
#include <robo_ml/robo_ml.hpp>
#include <chrono>
// Demonstrate some basic assertions.
TEST(ReplayBufferTest, GetLastNOverflows) {

  auto replay_buffer = robo::ReplayBuffer<int>(3);
  replay_buffer.add(std::make_shared<int>(1), std::chrono::nanoseconds(0));
  std::vector<robo::ReplayBuffer<int>::Entry> entries;
  ASSERT_EQ(replay_buffer.get_last(2, entries), robo::Status::NOT_ENOUGH_DATA);
}