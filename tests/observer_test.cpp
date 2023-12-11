#include <gtest/gtest.h>
#include <robo_ml/robo_ml.hpp>

namespace robo
{
TEST(ObserverTest, History) {
    typedef std::unique_ptr<int> IntPtr;
    typedef std::unique_ptr<bool> BoolPtr;
  auto obs_from_srcs_func = [](IntPtr int_src, BoolPtr bool_src) -> std::shared_ptr<bool> {
      return std::make_shared<bool>(*int_src == 1 &&  *bool_src);
    };

  auto observer = Observer<bool, int, bool>(obs_from_srcs_func, 2);
  auto observation = observer.observe(std::make_unique<int>(1), std::make_unique<bool>(true));

 ReplayBuffer<bool>::Entry last_obs;
  ASSERT_EQ(observer.history().get(0, last_obs), robo::Status::OK);
  ASSERT_TRUE(*last_obs.value);
}
} // namespace robo
