#include <gtest/gtest.h>
#include <robo_ml/robo_ml.hpp>
#include <chrono>
// Demonstrate some basic assertions.
TEST(ActorTest, Replay) {
  auto act_func = [](std::shared_ptr<int> state) -> std::shared_ptr<std::vector<int>> {
      return std::make_shared<std::vector<int>>(std::vector<int>{1, 2, 3});
    };
  auto actor = robo::Actor<int, int>(act_func, 2);
  auto actions = actor.act(std::make_shared<int>(1));

  typedef robo::ReplayBuffer<std::vector<int>>::Entry ActionEntry;
  auto last_actions = std::vector<ActionEntry>(2);
  ASSERT_EQ(actor.history().get_last(2, last_actions), robo::Status::OK);
}