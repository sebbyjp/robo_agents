// Copyright (c) 2023 Sebastian Peralta
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#pragma once
#include <vector>
#include <functional>
#include <memory>
#include "robo_agents/replay_buffer.hpp"


namespace robo
{
/**
 * @brief Responsible for generating actions from observations. Stores the history of actions.
 *
 * @tparam ActT
 * @tparam ObsT
 */
template<typename ActT, typename ObsT>
class Actor
{
public:
  typedef std::vector<ActT> ActionList;
  // Function that generates a list of actions from from some estimated observation.
  typedef  std::function<ActionList(std::shared_ptr<ObsT>)> ActFunc;
/**
 * @brief Construct a new Actor object
 *
 * @param act_func Function that generates a list of actions.
 * @param buffer_size
 */

  Actor(ActFunc act_func, size_t buffer_size = 10);

  /**
       * @brief Generates an action from the current observation. Stores the action in its history_ buffer.
       *
       * @param observation
       * @return std::vector<ActT>
       */
  ActionList act(std::shared_ptr<ObsT> observation);

  /**
   * @brief Get the history_ buffer object
   *
   * @return robo::ReplayBuffer<std::vector<ActT>>
   */
  ReplayBuffer<std::vector<ActT>> & history() {return history_;}

private:
  ActFunc act_func_;
  ReplayBuffer<std::vector<ActT>> history_;   // Stores action lists in chronological order.
};

// Implementation.
template<typename ActT, typename ObsT>
Actor<ActT, ObsT>::Actor(
  ActFunc act_func,
  size_t buffer_size)
: act_func_(act_func), history_(buffer_size)
{
}

template<typename ActT, typename ObsT>
std::vector<ActT> Actor<ActT, ObsT>::act(std::shared_ptr<ObsT> observation)
{
  ActionList actions = act_func_(observation);
  history_.add(std::make_unique<ActionList>(actions));
  return actions;
}

}  // namespace robo
