#include <gtest/gtest.h>
#include <robo_agents/robo_agents.hpp>
#include <chrono>

namespace robo {
TEST(ReplayBufferTest, GetLastNotEnoughData) {
  auto replay_buffer = ReplayBuffer<int>(3);

  replay_buffer.add(std::make_shared<int>(1));
  std::vector<ReplayBuffer<int>::Entry> entries;
  ASSERT_EQ(replay_buffer.get_last(2, entries), Status::NOT_ENOUGH_DATA);
}

TEST(ReplayBufferTest, GetIdMissStatus) {
  constexpr int kMaxSize = 3;
  auto replay_buffer = ReplayBuffer<int>(kMaxSize);
  replay_buffer.add(std::make_shared<int>(1));
  replay_buffer.add(std::make_shared<int>(2));

  ReplayBuffer<int>::Entry entry;
  ASSERT_EQ(replay_buffer.get(2, entry), Status::MISS_TOO_EARLY);

  replay_buffer.add(std::make_shared<int>(3));
  ASSERT_EQ(replay_buffer.get(2, entry), Status::OK);
  ASSERT_EQ(*entry.value, 3);

  replay_buffer.add(std::make_shared<int>(4));
  ASSERT_EQ(replay_buffer.get(0, entry), Status::MISS_TOO_LATE);
}
}  // namespace robo