#include <gtest/gtest.h>
#include <robo_ml/robo_ml.hpp>

namespace robo {
TEST(ActorTest, History) {
  auto act_func = [](std::shared_ptr<int> state) -> std::vector<int> {
      return std::vector<int>{1, 2, 3};
    };
  auto actor = Actor<int, int>(act_func, 2);
  auto actions = actor.act(std::make_shared<int>(1));

  typedef ReplayBuffer<std::vector<int>>::Entry ActionEntry;
  ActionEntry last_action_list;
  ASSERT_EQ(actor.history().get(0, last_action_list), Status::OK);
  ASSERT_EQ(last_action_list.value->at(0), 1);
  ASSERT_EQ(last_action_list.value->at(1), 2);
  ASSERT_EQ(last_action_list.value->at(2), 3);
}
} // namespace robo