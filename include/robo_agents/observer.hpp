// Copyright (c) 2023 Sebastian Peralta
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#pragma once
#include <functional>
namespace robo
{
/**
 * @brief Observer is responsible for creating an observation from a set of sources.
 *        It stores a buffer of observations.
 *
 * @tparam ObsT
 * @tparam SrcTs
 */
template<typename ObsT, typename ... SrcTs>
class Observer
{
public:
  typedef std::function<std::shared_ptr<ObsT>(std::unique_ptr<SrcTs>...)> ObsFromSrcsFunc;

  Observer(ObsFromSrcsFunc obs_from_srcs_function, size_t buffer_size = 10)
  : obs_from_srcs_function_(obs_from_srcs_function), history_(buffer_size)
  {
  }

  /**
   * @brief Generates an observation from the current state. Stores the observation in its history_ buffer.
   *
   * @param srcs
   * @return std::unique_ptr<ObsT>
   */
  std::shared_ptr<ObsT> observe(std::unique_ptr<SrcTs>... srcs)
  {
    std::shared_ptr<ObsT> obs = obs_from_srcs_function_(std::move(srcs) ...);
    history_.add(obs);
    return obs;
  }
  ReplayBuffer<ObsT> & history() {return history_;}

private:
  ObsFromSrcsFunc obs_from_srcs_function_;
  ReplayBuffer<ObsT> history_;   // Stores observations in chronological order.
};
}  // namespace robo
