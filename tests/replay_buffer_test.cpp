#include <gtest/gtest.h>
#include <robo_ml/robo_ml.hpp>
#include <chrono>

TEST(ReplayBufferTest, GetLastNotEnoughData) {
  auto replay_buffer = robo::ReplayBuffer<int>(3);

  replay_buffer.add(std::make_shared<int>(1));
  std::vector<robo::ReplayBuffer<int>::Entry> entries;
  ASSERT_EQ(replay_buffer.get_last(2, entries), robo::Status::NOT_ENOUGH_DATA);
}

TEST(ReplayBufferTest, GetIdMissStatus) {
  constexpr int kMaxSize = 3;
  auto replay_buffer = robo::ReplayBuffer<int>(kMaxSize);
  replay_buffer.add(std::make_shared<int>(1));
  replay_buffer.add(std::make_shared<int>(2));

  robo::ReplayBuffer<int>::Entry entry;
  ASSERT_EQ(replay_buffer.get(2, entry), robo::Status::MISS_TOO_EARLY);

  replay_buffer.add(std::make_shared<int>(3));
  ASSERT_EQ(replay_buffer.get(2, entry), robo::Status::OK);
  ASSERT_EQ(*entry.value, 3);

  replay_buffer.add(std::make_shared<int>(4));
  ASSERT_EQ(replay_buffer.get(0, entry), robo::Status::MISS_TOO_LATE);
}